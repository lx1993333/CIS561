#include <iostream>
#include <fstream>
#include "ASTNode.h"
#include "TypeChecker.h"


using namespace std;
int TMP_COUNT = 0;
int BOOL_TMP_COUNT = 0;


string fresh_temp(){
	string temp_name = "tmp_"+std::to_string(TMP_COUNT);
	TMP_COUNT++;
	return temp_name;
} 

string fresh_bool_temp(string type){
	string temp_name = type+std::to_string(BOOL_TMP_COUNT);
	BOOL_TMP_COUNT++;
	return temp_name;
} 

string l_eval(AST::LExpr* input,string* pgm, Scope* searching_scope){
	if (input->return_type() == "Ident"){
		AST::Ident* inputs = static_cast<AST::Ident*> (input);
		
		string type = searching_scope->search_in_scope(inputs->text_ );
		if (type == "Type_Check_Error"){
			cout<<"l_eval Type_Check_Error at: "<< inputs->text_ <<endl;
			exit(1);
		}
		
		type = "obj_"+ type;
		(*pgm) += type+" " + inputs->text_ + ";\n";
		return inputs->text_;
	}
	
	if (input->return_type() == "Dot"){
		AST::Dot* inputs = static_cast<AST::Dot*> (input);
		if (inputs->rexpr_.return_type()=="Ident"){
			AST::Ident* r_id = static_cast<AST::Ident*> (&(inputs->rexpr_));
			if (r_id->text_ == "this"){
				if (searching_scope->previous_scope->scope_name == "Class"){ //then it is in constructor
					AST::Ident* id = static_cast<AST::Ident*> (&(inputs->ident_));
					return "new_thing->"+id->text_;
				}
				else{
					AST::Ident* id = static_cast<AST::Ident*> (&(inputs->ident_));
					return "this->"+id->text_;
				}
			}
		}
	}
	
	return "l_eval error";
}

pair<string,string> r_eval(AST::ASTNode* input, string* pgm,Scope* searching_scope){
	string type = "Obj";
	string tmp = fresh_temp();
	bool if_constructor = false;
	if (input->return_type() == "Ident"){
		AST::Ident* inputs = static_cast<AST::Ident*> (input);
		if(inputs->text_ == "this"){
			//go to class scope
			Scope* class_scope = searching_scope;
			while (class_scope->scope_name != "Class"){
				class_scope = class_scope->previous_scope;
			}
			type = class_scope->table->content[0].first;
			(*pgm) += "obj_"+ type + " " +tmp + " = "+ inputs->text_ + ";\n";
		}
		else{
//			cout<<searching_scope->scope_name<<endl;
//			cout<<inputs->text_<<endl;
			type = searching_scope->search_in_scope(inputs->text_);
			if (type == "Type_Check_Error"){
				cout<<"r_eval Type_Check_Error at: "<< inputs->text_ <<endl;
				exit(1);
			}
			(*pgm) += "obj_"+ type + " " +tmp + " = "+ inputs->text_ + ";\n";
		}
	}
	
	if (input->return_type() == "IntConst"){
		AST::IntConst* inputs = static_cast<AST::IntConst*> (input);
		type = "Int";
		(*pgm)  += "obj_"+type +" "+ tmp + " = "+ "int_literal("+std::to_string(inputs->value_) + ");\n";
	}
	
	if (input->return_type() == "StringConst"){
			AST::StringConst* inputs = static_cast<AST::StringConst*> (input);
			type = "String";
			(*pgm)  += "obj_"+type +" "+ tmp + " = "+ "str_literal(\""+inputs->text_ + "\");\n";
		}
	
	if (input->return_type() == "BinOp"){
		AST::BinOp* inputs = static_cast<AST::BinOp*> (input);
		string first = r_eval(&(inputs->left_),pgm,searching_scope).first;
		string second = r_eval(&(inputs->right_),pgm,searching_scope).first;
		string clazz_tmp = fresh_temp();
//		cout<<searching_scope->scope_name<<endl;
		type = r_eval(&(inputs->left_),pgm,searching_scope).second;
//		cout<<type<<endl;
		(*pgm) += "obj_"+type +" "+ tmp + " = "+ first + "->clazz->" + inputs->BinOp_name() + '('+ first +','+ second + ')'+";\n";
	}
	
	if (input->return_type() == "Dot"){
		AST::Dot* inputs = static_cast<AST::Dot*> (input);
		pair<string,string> r_str = r_eval(&(inputs->rexpr_),pgm,searching_scope);
		string caller_type = r_str.second;
		string caller_name = r_str.first;
		Scope* global_scope = searching_scope;
		while (global_scope->scope_name != "Global"){
			global_scope = global_scope->previous_scope;
		}
		Scope* clazz_scope = global_scope->search_in_sub_scope(r_str.second);
		
		AST::Ident* dot_id = static_cast<AST::Ident*> (&(inputs->ident_));
		type = clazz_scope->search_in_scope(dot_id->text_);
		(*pgm)  += "obj_"+type +" "+ tmp + " = "+r_str.first+ "->" + dot_id->text_+";\n";
	}
	
	if(input->return_type() == "Method_call"){
		AST:: Method_call* inputs = static_cast<AST::Method_call*> (input);
		string method_name = inputs->name_.text_;
		string input_arg = "";
		string caller_type = "Obj";
		string caller_name = "";
		
		//handle types
		if (inputs->caller_.return_type() == "Ident"){
			AST::Ident* caller_id = static_cast<AST::Ident*> (&(inputs->caller_));
			if (caller_id->text_ != "Nothing"){
				pair<string,string> res = r_eval(&(inputs->caller_),pgm,searching_scope);
				caller_name = res.first;
				input_arg +=  caller_name;
				caller_type = res.second;
			}
			else{ //constructor
				caller_name = "this";
				method_name = "constructor";
				if_constructor = true;
			}
		}
		else{
			pair<string,string> res = r_eval(&(inputs->caller_),pgm,searching_scope);
			caller_name = res.first;
			input_arg +=  caller_name;
			caller_type = res.second;
		}
		
		Scope* method_scope = searching_scope;
		if(caller_type != "Obj" && caller_type != "Int" && caller_type != "String"){
			method_scope = searching_scope->search_in_sub_scope(caller_type);
		}
		
		string method_type = method_scope->class_table->search_in_table(inputs->name_.text_);
		
		
		//handle inputs
		AST:: Block* arg_block = static_cast<AST::Block*> (&(inputs->inputs_args_));
		vector<AST::ASTNode*>::iterator it;
		for(it = arg_block->stmts_.begin();it != arg_block->stmts_.end();it++){
			if((*it)->return_type()=="Ident"){
				AST::Ident* id = static_cast<AST::Ident*> (*it);
				input_arg += ","+id->text_;
				
			}
			else if((*it)->return_type()=="IntConst"){
				AST::IntConst* num = static_cast<AST::IntConst*> (*it);
				input_arg += ",int_literal("+ to_string(num->value_)+ ")";
			}
			
			else if((*it)->return_type()=="StringConst"){
				AST::StringConst* str = static_cast<AST::StringConst*> (*it);
				input_arg += ",str_literal(\""+str->text_ + "\")";
				
			}
			else{
				input_arg += ","+r_eval((*it),pgm,searching_scope).first;
			}

		}
		
		if (searching_scope->search_in_scope(inputs->name_.text_) != "Type_Check_Error"){//if we can find the method name in Global scope, it must be a constructor!
			return make_pair("new_"+inputs->name_.text_+"("+input_arg.erase(0,1)+")",method_type);
		}
		
		if (if_constructor){
			input_arg.erase(0,1);
		}
		
		return make_pair(caller_name+"->clazz->"+method_name+"("+input_arg+")",method_type);
	}
	
	else if (input->return_type() == "Logic_BinOp"){
		AST::BinOp* inputs = static_cast<AST::BinOp*> (input);
		string left = r_eval(&(inputs->left_), pgm,searching_scope).first;
		string right = r_eval(&(inputs->right_), pgm,searching_scope).first;
		(*pgm) += "obj_Boolean "+tmp+"="+left+"->clazz->"+inputs->BinOp_name()+"("+left+","+right+");\n";
		type = "Boolean";
	}
	
	
	return make_pair(tmp,type);
}


void Dot_handler(AST::ASTNode* input,string* pgm, Scope* searching_scope){
	string tmp = fresh_temp();
	AST::Dot* inputs = static_cast<AST::Dot*> (input);
	string left = "";

	left = r_eval(&(inputs->rexpr_),pgm,searching_scope).first;
	string ident = r_eval(&(inputs->ident_),pgm,searching_scope).first;

	(*pgm) += "("+ left + ")->clazz->"+ ident + ";\n";
	

	
}

void Assign_handler(AST::ASTNode* input,string* pgm, Scope* searching_scope){
	AST::Assign* inputs = static_cast<AST::Assign*> (input);
	string loc = l_eval(&(inputs->lexpr_),pgm,searching_scope);
	string val = r_eval(&(inputs->rexpr_),pgm,searching_scope).first;
//	if (inputs->rexpr_.return_type() == "Method"){
//		string val = r_eval(&(inputs->rexpr_),pgm,searching_scope).first;
//	}
//	else{
//				if (loc != "l_eval error"){
//				(*pgm) += loc + " = &" + val + ";\n";
//			} 
			
	if (loc != "l_eval error"){
		(*pgm) += loc + " = " + val + ";\n";
	}

}


void Return_handler(AST::ASTNode* input,string* pgm, Scope* searching_scope){
	AST::Return_opt* inputs = static_cast<AST::Return_opt*> (input);
	(*pgm) += "return "+r_eval(&(inputs->stmt_),pgm,searching_scope).first+";\n";
}


void If_handler(AST::ASTNode* input,string* pgm, Scope* searching_scope){
	AST::If* inputs = static_cast<AST::If*> (input);
	string condition = r_eval(&(inputs->cond_), pgm, searching_scope).first;
	
	string true_label = fresh_bool_temp("true");
	string true_else = fresh_bool_temp("else");
	string false_label = fresh_bool_temp("false");
	string endif_label = fresh_bool_temp("endif");
	
	
	(*pgm) += "if( lit_true == "+condition+") { goto "+ true_label+";}\ngoto "+ false_label+";\n";
	(*pgm) += true_label+":\n{\n";
	
	//handle true part
	if (inputs->truepart_.stmts_.size() != 0){
		vector<AST::ASTNode*>::iterator its;
		
		for (its = inputs->truepart_.stmts_.begin();its != inputs->truepart_.stmts_.end();its++){
			AST::Statement* stm = static_cast<AST::Statement*> (*its);
			if (stm->stmt_.return_type() == "Assign"){
				Assign_handler(&(stm->stmt_),pgm,searching_scope->next_scope[0]); //method_scope->next_scope[0] is the method_block scope
			}
			
			if (stm->stmt_.return_type() == "Dot"){
				Dot_handler(&(stm->stmt_),pgm,searching_scope->next_scope[0]);
			}
			
			if (stm->stmt_.return_type() == "Method_call"){
				(*pgm) += r_eval(&(stm->stmt_),pgm,searching_scope->next_scope[0]).first+";\n";
			}
			
			if (stm->stmt_.return_type() == "Return_opt"){
				Return_handler(&(stm->stmt_),pgm,searching_scope->next_scope[0]);				
			}
		}	
	}
	else{
			(*pgm) += ";\n";
		}
	(*pgm) += "goto "+endif_label+";\n";
	(*pgm) += "}\n";
	
	//handle false part
	(*pgm) += false_label+":\n{\n";
	if (inputs->falsepart_.stmts_.size() != 0){
		vector<AST::ASTNode*>::iterator its;
		
		for (its = inputs->falsepart_.stmts_.begin();its != inputs->falsepart_.stmts_.end();its++){
			AST::Statement* stm = static_cast<AST::Statement*> (*its);
			if (stm->stmt_.return_type() == "Assign"){
				Assign_handler(&(stm->stmt_),pgm,searching_scope->next_scope[0]); //method_scope->next_scope[0] is the method_block scope
			}
			
			if (stm->stmt_.return_type() == "Dot"){
				Dot_handler(&(stm->stmt_),pgm,searching_scope->next_scope[0]);
			}
			
			if (stm->stmt_.return_type() == "Method_call"){
				(*pgm) += r_eval(&(stm->stmt_),pgm,searching_scope->next_scope[0]).first+";\n";
			}
			
			if (stm->stmt_.return_type() == "Return_opt"){
				Return_handler(&(stm->stmt_),pgm,searching_scope->next_scope[0]);				
			}
		}	
	}
	else{
		(*pgm) += ";\n";
	}
	(*pgm) += "}\n";
	//handle endif part
	(*pgm) += endif_label+": ;\n";
}


void While_handler(AST::ASTNode* input,string* pgm, Scope* searching_scope){
	AST::While* inputs = static_cast<AST::While*> (input);
	
	string startWhile_label = fresh_bool_temp("startWhile");
	string true_label = fresh_bool_temp("true");
	string endWhile_label = fresh_bool_temp("endWhile");
	
	(*pgm) += startWhile_label+": ;\n";
	
	string condition = r_eval(&(inputs->cond_), pgm, searching_scope).first;
	(*pgm) += "if( lit_true == "+condition+") { goto "+ true_label+";}\ngoto "+ endWhile_label+";\n";
	(*pgm) += true_label+":\n{\n";
	
	//handle true part
		if (inputs->block_.stmts_.size() != 0){
			vector<AST::ASTNode*>::iterator its;
			
			for (its = inputs->block_.stmts_.begin();its != inputs->block_.stmts_.end();its++){
				AST::Statement* stm = static_cast<AST::Statement*> (*its);
				if (stm->stmt_.return_type() == "Assign"){
					Assign_handler(&(stm->stmt_),pgm,searching_scope->next_scope[0]); //method_scope->next_scope[0] is the method_block scope
				}
				
				if (stm->stmt_.return_type() == "Dot"){
					Dot_handler(&(stm->stmt_),pgm,searching_scope->next_scope[0]);
				}
				
				if (stm->stmt_.return_type() == "Method_call"){
					(*pgm) += r_eval(&(stm->stmt_),pgm,searching_scope->next_scope[0]).first+";\n";
				}
				
				if (stm->stmt_.return_type() == "Return_opt"){
					Return_handler(&(stm->stmt_),pgm,searching_scope->next_scope[0]);				
				}
			}	
		}
		else{
				(*pgm) += ";\n";
		}
		
		(*pgm) += "goto "+startWhile_label+";\n";
		(*pgm) += "}\n";
		(*pgm) += endWhile_label+": ;\n";
		
	
}


void Method_handler(AST::ASTNode* input,string* pgm, Scope* method_scope,string class_name){
	AST::Method* inputs = static_cast<AST::Method*> (input);
	string return_type = inputs->type_.text_;
	string input_arg = "obj_"+class_name+" this";
	
	//handle inputs
	std::vector<std::pair<std::string,std::string> >:: iterator it;
	for (it = method_scope->table->content.begin();it != method_scope->table->content.end();it++){
		if ((*it).first != inputs->name_.text_){
			if (it+1 != method_scope->table->content.end()){
				input_arg += ", obj_"+(*it).second+" "+(*it).first;
			}
			else{
				input_arg += ", obj_"+(*it).second+" "+(*it).first;
			}
		}	
	}
	
	if (return_type == "Nothing"){
		return_type = "void";
	}
	else{
		return_type = "obj_"+return_type;
	}
	(*pgm) += return_type+" "+class_name+"_method_"+inputs->name_.text_+"("+input_arg+"){\n";
	AST::Block* method_block = static_cast<AST::Block*> (&(inputs->blocks_));
	
	
	//handle method body
	vector<AST::ASTNode*>::iterator its;
	for (its = method_block->stmts_.begin();its != method_block->stmts_.end();its++){
			AST::Statement* stm = static_cast<AST::Statement*> (*its);
			if (stm->stmt_.return_type() == "Assign"){
				Assign_handler(&(stm->stmt_),pgm,method_scope->next_scope[0]); //method_scope->next_scope[0] is the method_block scope
			}
			
			if (stm->stmt_.return_type() == "Dot"){
				Dot_handler(&(stm->stmt_),pgm,method_scope->next_scope[0]);
			}
			
			if (stm->stmt_.return_type() == "Method_call"){
				(*pgm) += r_eval(&(stm->stmt_),pgm,method_scope->next_scope[0]).first+";\n";
			}
			
			if (stm->stmt_.return_type() == "Return_opt"){
				Return_handler(&(stm->stmt_),pgm,method_scope->next_scope[0]);				
			}
			
			if (stm->stmt_.return_type() == "If"){
				If_handler(&(stm->stmt_),pgm,method_scope->next_scope[0]);
			}
			
			if (stm->stmt_.return_type() == "While"){
				While_handler(&(stm->stmt_),pgm,method_scope->next_scope[0]);
			}

	}
	
	(*pgm) += "}\n";
}



void node_handler_switcher(AST::ASTNode* input, string* pgm, Scope* scope, string current_scope_name,string class_name){
	Scope* searching_scope = scope;
	if(current_scope_name!= "Global"){
		
	}
	if (input->return_type() == "Assign"){
		Assign_handler(input,pgm,searching_scope);
	}
	
	if (input->return_type() == "Dot"){
		Dot_handler(input,pgm,searching_scope);
	}
	
	if (input->return_type() == "Method_call"){
		(*pgm) += r_eval(input,pgm,searching_scope).first+";\n";
	}
	
	if (input->return_type() == "Method"){
		AST::Method* inputs = static_cast<AST::Method*> (input);
		Scope* method_scope = searching_scope->next_scope[0]->find_sub_scope(inputs->name_.text_+"_Method");
		Method_handler(input,pgm,method_scope,class_name);
	}

	if (input->return_type() == "If"){
		If_handler(input,pgm,searching_scope);
	}
	
	if (input->return_type() == "While"){
			While_handler(input,pgm,searching_scope);
		}
	
}


void Class_Block_handler(AST::ASTNode* input, string* pgm,Scope* scope, string current_scope_name,string class_name){
	AST::Block* inputs = static_cast<AST::Block*> (input);
	vector<AST::ASTNode*>::iterator it;
	for (it = inputs->stmts_.begin();it != inputs->stmts_.end();it++){
		if ((*it)->return_type() == "Statement"){
			AST::Statement* its = static_cast<AST::Statement*> (*it);
			if(its->stmt_.return_type() == "Assign"){  //handle the Assign first during first traversal 
				node_handler_switcher(&(its->stmt_),pgm,scope->next_scope[0],"Class",class_name);
			}
		}
	}
	//----------------constructor finished here-------------------------------//
	(*pgm) +="return new_thing;\n}\n";
	
	//----------------gen code for method_STRING()-------------------------------//
		(*pgm) += "obj_String "+class_name+"_method_STRING("+"obj_"+class_name+" this) {\n";
		string return_str = "Object of type: "+class_name;
		(*pgm) += "return str_literal(\""+return_str+"\");\n";
		(*pgm) +="}\n";
	
	
	for (it = inputs->stmts_.begin();it != inputs->stmts_.end();it++){
			if ((*it)->return_type() == "Statement"){
				AST::Statement* its = static_cast<AST::Statement*> (*it);
				if(its->stmt_.return_type() != "Assign"){  //handle the Assign first during first traversal 
					node_handler_switcher(&(its->stmt_),pgm,scope,"Class",class_name);
				}
			}
		}
}

void Class_handler(AST::ASTNode* input, string* pgm,Scope* scope, string current_scope_name){
	AST::Class* inputs = static_cast<AST::Class*> (input);
	Scope* class_scope = scope->search_in_sub_scope(inputs->name_.text_);
	(*pgm) += "struct class_"+inputs->name_.text_+"_struct;\n";
	(*pgm) += "typedef struct class_"+ inputs->name_.text_ + "_struct* class_"+ inputs->name_.text_+";\n";
	
	//------------------------------------build obj_CLASS_struct--------------------------//
	(*pgm) += "typedef struct obj_"+inputs->name_.text_+"_struct {\n";
	std::vector<std::pair<std::string,std::string> >:: iterator it;
	for (it = class_scope->table->content.begin();it != class_scope->table->content.end();it++){
		if ((*it).first == inputs->name_.text_){
			(*pgm) += "class_"+(*it).first+ " clazz;\n";
		}
		else{
			(*pgm) += "obj_"+(*it).second + " "+(*it).first+";\n";
		}
	}
	(*pgm) += "} *obj_"+inputs->name_.text_+";\n";
	
		
	//------------------------------------//build class_CLASS_struct-------------------------//
	(*pgm) += "struct class_"+inputs->name_.text_+"_struct {\n";
	
	
	//--------------------built-in functions---------------------------//
	//constructor function
	(*pgm) += "obj_"+ inputs->name_.text_+ " (*constructor) ("; 
	int counter = 1;
	std::vector<AST::ASTNode*>::iterator arg_it;
	AST::Actuals* args = static_cast<AST::Actuals*> (&(inputs->inputs_args_));
	for (arg_it = args->argus_.begin();arg_it!= args->argus_.end();arg_it++){
		AST::Argus* ag = static_cast<AST::Argus*> (*arg_it);
		if(counter < args->argus_.size()){
			(*pgm) += "obj_"+ag->var_type_.text_+", ";
		}
		else{
			(*pgm) += "obj_"+ag->var_type_.text_;
		}
		counter++;

	}
	
//	class_scope->table->print_table();
//	for (it = class_scope->table->content.begin();it != class_scope->table->content.end();it++){
//		if ((*it).first != inputs->name_.text_){
//			if (counter == class_scope->table->content.size()-1){
//				(*pgm) += "obj_"+(*it).second;
//			}
//			else{
//				(*pgm) += ",obj_"+(*it).second;
//			}
//			counter++;
//		}
//	}
	(*pgm) +=");\n";
	//STRING function
	(*pgm) += "obj_String (*STRING) (obj_"+inputs->name_.text_+");\n";
	//PRINT function
	(*pgm) +="obj_Obj (*PRINT) (obj_Obj);\n";
//	//EQUALS function
//	(*pgm) +="obj_Boolean (*EQUALS) (obj_Obj, obj_Obj);\n";
	
	//--------------------introduced functions---------------------------//
	for (it = class_scope->class_table->content.begin();it != class_scope->class_table->content.end();it++){
		(*pgm) += "obj_"+(*it).second+ " (*"+(*it).first+") (";
		Scope* method_scope = class_scope->next_scope[0]->find_sub_scope((*it).first+"_Method");
		std::vector<std::pair<std::string,std::string> >:: iterator tmp_it;
		(*pgm) += "obj_"+inputs->name_.text_;
		for (tmp_it = method_scope->table->content.begin();tmp_it != method_scope->table->content.end();tmp_it++){
			(*pgm) += ", obj_"+(*tmp_it).second;
		}
		(*pgm) +=");\n";
	}
	
	(*pgm) += "};\nextern class_"+inputs->name_.text_+" the_class_"+inputs->name_.text_+";\n";
	
	//----------------gen code for actual constructor-------------------------------//
	(*pgm) += "obj_"+inputs->name_.text_+" new_"+ inputs->name_.text_+"(";  
	//heandle the inputs
//	for (it = class_scope->table->content.begin();it != class_scope->table->content.end();it++){
//			if ((*it).first != inputs->name_.text_){
//				if (it+1 != class_scope->table->content.end()){
//					(*pgm) += "obj_"+(*it).second+" "+(*it).first+", ";
//				}
//				else{
//					(*pgm) += "obj_"+(*it).second+" "+(*it).first;
//				}
//			}	
//	}
	counter = 1;
	for (arg_it = args->argus_.begin();arg_it!= args->argus_.end();arg_it++){
		AST::Argus* ag = static_cast<AST::Argus*> (*arg_it);
		if(counter < args->argus_.size()){
			(*pgm) += "obj_"+ag->var_type_.text_+" "+ ag->var_name_.text_+", ";
		}
		else{
			(*pgm) += "obj_"+ag->var_type_.text_+" "+ ag->var_name_.text_;
		}
		counter++;
	}
	(*pgm) +="){\n";
	
	(*pgm) += "obj_"+inputs->name_.text_+" new_thing = (obj_"+inputs->name_.text_+") malloc(sizeof(struct obj_"+inputs->name_.text_+"_struct));\n";
	(*pgm) += "new_thing->clazz = the_class_"+inputs->name_.text_+";\n";
	
	
	//handle class body//
	Class_Block_handler(&(inputs->blocks_), pgm, class_scope, "Class",inputs->name_.text_);
	
	
	
	//----------------link method struct to method table-------------------------------//
	(*pgm) += "struct class_"+inputs->name_.text_+"_struct the_class_"+inputs->name_.text_+"_struct={\n";
	(*pgm) += "new_"+ inputs->name_.text_; //constructor
	(*pgm) += ", \n"+inputs->name_.text_+"_method_STRING";
	(*pgm) += ",\nObj_method_PRINT";
	
	for (it = class_scope->class_table->content.begin();it != class_scope->class_table->content.end();it++){
		(*pgm) += ", \n"+inputs->name_.text_+"_method_"+(*it).first;
	}
	(*pgm) +="\n};\n";
	(*pgm) +="class_"+inputs->name_.text_+" the_class_"+inputs->name_.text_+" = &the_class_"+inputs->name_.text_+"_struct;\n";
}



void code_gen(AST::ASTNode *root, Scope* scope){
	AST::Classes* inputs = static_cast<AST::Classes*> (root);
	vector<AST::ASTNode*>::iterator it;
	string pgm = "#include <stdio.h>\n#include <stdlib.h>\n#include \"Builtins.h\"\nvoid quackmain();\nint main(int argc, char** argv) {\nquackmain();\n}\n";
	
	//first we scan for classes
	for (it = inputs->clazzs_.begin();it != inputs->clazzs_.end();it++){
		if((*it)->return_type() == "Class"){
			Class_handler((*it),&pgm,scope,"Class");
		}	
	} 
	
	pgm += "void quackmain() {\n";
	//now we scan for statments
	for (it = inputs->clazzs_.begin();it != inputs->clazzs_.end();it++){
		if ((*it)->return_type() == "Statement"){
			AST::Statement* its = static_cast<AST::Statement*> (*it);
			node_handler_switcher(&(its->stmt_),&pgm,scope,"Global","Global");
		}
	}
	pgm += "}\n";
	std::cout<<pgm<<std::endl;
	
	ofstream myfile;
	myfile.open ("C_output.c");
	myfile << pgm;
	myfile.close();
}