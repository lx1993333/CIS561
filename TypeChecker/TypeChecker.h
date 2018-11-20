#include <iostream>
#include "Scope.h"
#include "ASTNode.h"

using namespace std;



string Method_RExpr_handler(AST::ASTNode* input,Scope* current_scope){   //when position == "left" evaluate it as address, position == "left" evaluate it as value; 
	if (input->return_type() == "Ident"){
		AST::Ident* inputs = static_cast<AST::Ident*> (input);
		if (inputs->text_ == "this"){
			return inputs->text_;
		}
		else{
			return current_scope->search_in_scope(inputs->text_);
		}
	}
	else if (input->return_type() == "IntConst"){
			return "Int";
	}
	else if (input->return_type() == "StringConst"){
			return "String";
	}
	else if (input->return_type() == "Dot"){
		AST::Dot* inputs = static_cast<AST::Dot*> (input);
		string left_exp = Method_RExpr_handler(&(inputs->rexpr_),current_scope);
		Scope* searching_scp = current_scope;

		if (searching_scp->scope_name == "Global"){
			searching_scp = searching_scp->search_in_sub_scope(left_exp);
		}
		else{
			while(searching_scp && searching_scp->scope_name != "Class"){
				searching_scp = searching_scp->previous_scope;  //the previous_scope of 'this' is the class scope
			}
		}
		
		return Method_RExpr_handler(&(inputs->ident_),searching_scp);
		
	}
	else if (input->return_type() == "BinOp"){
		AST::BinOp* inputs = static_cast<AST::BinOp*> (input);
		if (Method_RExpr_handler(&(inputs->left_),current_scope) == Method_RExpr_handler(&(inputs->right_),current_scope)){
			return Method_RExpr_handler(&(inputs->left_),current_scope);
		}
	}
	return "Type_Check_Error";		
	
}




string Method_call_handler(AST::ASTNode* input,Scope* current_scope,string position){    //"left"->return name of the function, "right"->return type of the function.
	
	AST::Method_call* inputs = static_cast<AST::Method_call*> (input);
	string method_name = inputs->name_.text_;
	AST::Block* arg_block = static_cast<AST::Block*> (&(inputs->inputs_args_));
	vector<AST::ASTNode*>:: iterator it;
	
	int input_index = 0;
	Scope* searching_scp;
	Scope* global_scp = current_scope;

	
	while (global_scp->scope_name != "Global" && global_scp){
		global_scp = global_scp->previous_scope;
	}  // Go to global_scp

	
	for (it = arg_block->stmts_.begin();it != arg_block->stmts_.end();it++){
		//evaluate the type of input.
		string input_type;
		
		if ((*it)->return_type() == "Method_call"){
			input_type = Method_call_handler((*it),current_scope,"right");
		}
		else{
			input_type = Method_RExpr_handler((*it),current_scope);
		}
				
		if (current_scope->scope_name == "Class"){     //if current_scope is Class, that means we are searching for a class method. Thus need to go inside twice. 
			searching_scp = current_scope->next_scope[0]->next_scope[0];
		}
				
		else{
			
			searching_scp = global_scp->search_in_sub_scope(method_name)->next_scope[0];  //finding the function's block scope 
		} 			
		if(searching_scp->table->content.size()!= arg_block->stmts_.size()){
			std::cout<<"Type Check Error: The number of inputs of function "<< method_name << "() is not correct!"<<endl;
			exit(1);
		}
		
		if(searching_scp->table->content[input_index].second != input_type){         //first check if the type of input_type is same with the name in searching_scp
			if(!(global_scp->class_table->hierarchy_check(input_type,searching_scp->table->content[input_index].second))){ //check if there is a hierachy relation.
				std::cout<<"Method_call Type Error from "<< method_name << "() inside "<< current_scope->scope_name << " Scope. The inputs type don't match! "<<std::endl;
				exit(1);
			}
		}
		input_index +=1;

	}
	
	searching_scp = current_scope;
	
	if (searching_scp->scope_name == "Global"){
		searching_scp = searching_scp->search_in_sub_scope(method_name);
	}
	else{
		while(searching_scp && searching_scp->scope_name != "Global"){
			searching_scp = searching_scp->previous_scope;  //the previous_scope of 'this' is class scope
		}
		searching_scp = searching_scp->next_scope[0]; // set searching_scp to Class scope
	}
	
	if (searching_scp->search_in_scope(method_name) == "Type_Check_Error" && method_name != "Obj" ){   // Obj() is fine, sine it is a built-in function
		std::cout<<"Method_call Type Error at: "<< method_name <<std::endl;
		exit(1);
	}
//	if (current_scope->scope_name == "Class_Block"){              //if there is an method call inside Class scope, it must be a type eval.
//		return current_scope->search_in_scope(method_name);
//	}

	if (position == "right"){    
		        //if there is an method call inside Class scope, it must be a type eval.
			if(method_name == "Obj"){ // Obj() returns an Obj
				return "Obj";
			}
			else{
				return searching_scp->search_in_scope(method_name);
			}
	}
	else{
		return method_name;
	}
}


string RExpr_handler(AST::ASTNode* input,Scope* current_scope, string position){   //when position == "left" evaluate it as address, position == "left" evaluate it as value; 
	if (input->return_type() == "Ident"){
		AST::Ident* inputs = static_cast<AST::Ident*> (input);
		if (inputs->text_ == "this"){
			return inputs->text_;
		}
		else{
//			cout<<inputs->text_<<endl;
//			cout<<current_scope->scope_name<<endl;
			return current_scope->search_in_scope(inputs->text_);
		}
	}
	else if (input->return_type() == "IntConst"){
			return "Int";
	}
	else if (input->return_type() == "StringConst"){
			return "String";
	}
	else if (input->return_type() == "Method_call"){
			return  Method_call_handler(input,current_scope,position);
	}
	else if (input->return_type() == "Dot"){
		AST::Dot* inputs = static_cast<AST::Dot*> (input);
		string left_exp = RExpr_handler(&(inputs->rexpr_),current_scope,"left");
		Scope* searching_scp = current_scope;

//		if (left_exp == "this"){
//			while(current_scope &&current_scope->scope_name != "Class_Block"){
//				current_scope = current_scope->previous_scope;  //the previous_scope of 'this' is the class scope
//			}
//			
//			searching_scp = current_scope;
//		}
//		else{
//			searching_scp = current_scope->search_in_sub_scope(left_exp);  //otherwise search for the 'left_exp' class scope  
//		}
		if (searching_scp->scope_name == "Global"){
			searching_scp = searching_scp->search_in_sub_scope(left_exp);
		}
		else{
			while(searching_scp && searching_scp->scope_name != "Global"){
				searching_scp = searching_scp->previous_scope;  //the previous_scope of 'this' is the class scope
			}
			searching_scp = searching_scp->next_scope[0];  //set searching_scp to Class scope
		}
		
		return RExpr_handler(&(inputs->ident_),searching_scp,"right");
		
	}
	else if (input->return_type() == "BinOp"){
		AST::BinOp* inputs = static_cast<AST::BinOp*> (input);
		if (RExpr_handler(&(inputs->left_),current_scope,"right") == RExpr_handler(&(inputs->right_),current_scope,"right")){
			return  RExpr_handler(&(inputs->left_),current_scope,"right");
		}
	}
	
	else if (input->return_type() == "Logic_BinOp"){
			AST::BinOp* inputs = static_cast<AST::BinOp*> (input);
//			cout<<RExpr_handler(&(inputs->left_),current_scope,"right")<<endl;
//			cout<<RExpr_handler(&(inputs->right_),current_scope,"right");
			if (RExpr_handler(&(inputs->left_),current_scope,"right") == RExpr_handler(&(inputs->right_),current_scope,"right") | (RExpr_handler(&(inputs->left_),current_scope,"right") == "String") | (RExpr_handler(&(inputs->left_),current_scope,"right") == "Int")){
				return  "Bool";
			}
		}
	
	return "Type_Check_Error";		
	
}


//string RExpr_handler(AST::ASTNode* input,Scope* current_scope){
//	if (input->return_type() == "Ident"){
//			AST::Ident* inputs = static_cast<AST::Ident*> (input);
//			return inputs->text_;	
//	}
//	return "Type_Check_Error";
//}




string Ident_handler(AST::ASTNode* input, Scope* current_scope){
	AST::Ident* inputs = static_cast<AST::Ident*> (input);
	return current_scope->search_in_scope(inputs->text_);
}


string LExpr_handler(AST::LExpr* input,Scope* current_scope){
	
	if (input->return_type() == "Dot"){
		AST::Dot* inputs = static_cast<AST::Dot*> (input);
		return RExpr_handler(inputs,current_scope,"left");
	}
	
	if (input->return_type() == "Ident"){
		AST::Ident* inputs = static_cast<AST::Ident*> (input);
		return inputs->text_;	
	}
	return "Type_Check_Error";
}



pair<string,string> Assign_handler(AST::ASTNode* input,Scope* current_scope){
	AST::Assign* inputs = static_cast<AST::Assign*> (input);
	pair<string,string> res;
	
	if (inputs->lexpr_.return_type() == "Dot"){
		AST::Dot* dot = static_cast<AST::Dot*> (&(inputs->lexpr_));
		string dot_rexpr = RExpr_handler(&(dot->rexpr_),current_scope,"left");
		if (dot_rexpr == "this"){
			if (dot->ident_.return_type() == "Ident"){
				AST::Ident* dot_ident = static_cast<AST::Ident*> (&(dot->ident_));
				string dot_ident_str = dot_ident->text_;
				Scope* class_scp = current_scope;
				
				while(class_scp && class_scp->scope_name != "Class"){
					class_scp = class_scp->previous_scope;  //the previous_scope of 'this' is the class scope
				}			
				res = make_pair(dot_ident_str, RExpr_handler(&(inputs->rexpr_),current_scope,"right"));
				class_scp->add_to_scope(res.first, res.second);	
				
	
//					if (LExpr_handler(&(inputs->lexpr_),current_scope) != RExpr_handler(&(inputs->rexpr_),current_scope,"right")){
//						std::cout<<"Assign Type Error at: "<< dot_rexpr << "inside scope: "<<current_scope->scope_name<< std::endl;
//						exit(1);
//					}
					
				return make_pair("None","None");	
			}
		}
		else{
			std::cout<<"Assign Type Error at: "<< dot_rexpr <<std::endl;
			exit(1);
		}	
	}
//	string l = LExpr_handler(&(inputs->lexpr_),current_scope);
//	string r =  RExpr_handler(&(inputs->rexpr_),current_scope,"right");
	res = make_pair(LExpr_handler(&(inputs->lexpr_),current_scope), RExpr_handler(&(inputs->rexpr_),current_scope,"right"));
	if (res.second == "Type_Check_Error"){
		std::cout<<"Type Error at: "<< res.first <<std::endl;
		exit(1);
	}
	return res;
}


pair<string,string> Return_handler(AST::ASTNode* input, Scope* current_scope,string func_name){
	pair<string,string> res;
	AST::Return_opt* inputs = static_cast<AST::Return_opt*> (input);
	string ret_type = RExpr_handler(&(inputs->stmt_),current_scope,"right");
	
	Scope* searchine_scope = current_scope;
	
	while(searchine_scope &&searchine_scope->scope_name != "Class"){
			searchine_scope = searchine_scope->previous_scope;  //the previous_scope of 'this' is the class scope
	}
	
//	Scope* class_scope = current_scope->previous_scope->previous_scope;  //go to the Class scope
	//cout<<"return type == "<< searchine_scope->search_in_scope(func_name)<<endl;
	if (ret_type != searchine_scope->search_in_scope(func_name)){
		std::cout<<"Return Type Error of function: "<< func_name <<std::endl;
		exit(1);
	}
	res = make_pair("None", "None"); 
	
	return res;
}



pair<string,string> If_stmt_handler_switcher(AST::ASTNode* input, Scope* current_scope,string func_name){
	pair<string,string> res;
	if (input->return_type() == "Assign"){
		res = Assign_handler(input,current_scope);
	}
	
	if (input->return_type() == "Return_opt"){
			res = Return_handler(input,current_scope,func_name);
		}


//	if (input->return_type() == "Method_call"){
//		res = Method_call_handler(input,current_scope);
//	}
	return res;
}


Scope* If_block_traversal(AST::ASTNode *root,Scope* pre_scope,string name,string func_name){
	AST::Block* inputs = static_cast<AST::Block*> (root);
	Scope* s1= new Scope(pre_scope,name+"_Block");
	pre_scope->next_scope.push_back(s1);
	//add input argus into block's scope.
	std::vector<AST::ASTNode*>::iterator it;
	for (it = inputs->stmts_.begin();it != inputs->stmts_.end();it++){
			AST::Statement* its = static_cast<AST::Statement*> (*it);
			pair<string,string> res = If_stmt_handler_switcher(&(its->stmt_),s1,func_name);
			if (res.first != "None"){
				s1->add_to_scope(res.first, res.second);
			}
		}
	return s1;
	
}

pair<string,string> If_handler(AST::ASTNode* input,Scope* current_scope,string func_name){
	AST::If* inputs = static_cast<AST::If*> (input);
	if (RExpr_handler(&(inputs->cond_),current_scope, "right") != "Bool"){
		std::cout<<"If condition Type Error"<<std::endl;
		exit(1);
	}

	Scope* true_block_scope = If_block_traversal(&(inputs->truepart_),current_scope,"True",func_name);
	Scope* false_block_scope = If_block_traversal(&(inputs->falsepart_),current_scope,"False",func_name);
	
	true_block_scope->scope_comnpare(false_block_scope);
		
	
	return make_pair("None", "None");
}


pair<string,string> While_stmt_handler_switcher(AST::ASTNode* input, Scope* current_scope,string func_name){
	pair<string,string> res;
	if (input->return_type() == "Assign"){
		res = Assign_handler(input,current_scope);
	}
	
	if(input->return_type() == "If"){
		res = If_handler(input,current_scope,func_name);
	}
	
	if(input->return_type() == "Return_opt"){
			res = Return_handler(input,current_scope,func_name);
		}
	
//	if (input->return_type() == "Method_call"){
//		res = Method_call_handler(input,current_scope);
//	}
	return res;
}


void While_block_traversal(AST::ASTNode *root,Scope* pre_scope,string func_name){
	AST::Block* inputs = static_cast<AST::Block*> (root);
	Scope* s1= new Scope(pre_scope,"While_Block");
	pre_scope->next_scope.push_back(s1);
	//add input argus into block's scope.
	std::vector<AST::ASTNode*>::iterator it;
	for (it = inputs->stmts_.begin();it != inputs->stmts_.end();it++){
			AST::Statement* its = static_cast<AST::Statement*> (*it);
			pair<string,string> res = While_stmt_handler_switcher(&(its->stmt_),s1,func_name);
			if (res.first != "None"){
				s1->add_to_scope(res.first, res.second);
			}
		}
}



pair<string,string> While_handler(AST::ASTNode* input,Scope* current_scope,string func_name){
	AST::While* inputs = static_cast<AST::While*> (input);
	if(RExpr_handler(&(inputs->cond_),current_scope,"right") != "Bool"){
		std::cout<<"While Condition Type_Check_Error"<<std::endl;
		exit(1);
	}
	While_block_traversal(&(inputs->block_),current_scope,func_name);
	return make_pair("None", "None");
	
}


pair<string,string> Method_handler(AST::ASTNode* input,Scope* current_scope){
	Scope* s1= new Scope(current_scope,"Method");
	current_scope->add_sub_scope(s1);
	
	AST::Method* inputs = static_cast<AST::Method*> (input);
	pair<string,string> res;
	current_scope->previous_scope->add_to_class_scope(inputs->name_.text_, inputs->type_.text_);

	
	AST::Block* block = static_cast<AST::Block*> (&(inputs->blocks_));
	AST::ASTNode* argus = &(inputs->inputs_args_);
	AST::Actuals* actuals = static_cast<AST::Actuals*> (argus);
	
	//add input argus into block's scope.
	std::vector<AST::ASTNode*>::iterator it;
	for (it = actuals->argus_.begin();it != actuals->argus_.end();it++){
		AST::Argus* arg = static_cast<AST::Argus*> (*it);
		s1->add_to_scope(arg->var_name_.text_,arg->var_type_.text_);
	} 
	
	Scope* s2= new Scope(s1,"Method_Block");
	s1->add_sub_scope(s2);
	
	for (it = block->stmts_.begin();it != block->stmts_.end();it++){
			AST::Statement* its = static_cast<AST::Statement*> (*it);
			if (its->stmt_.return_type() == "Assign"){
					res = Assign_handler(&(its->stmt_),s2);
			}
			
			else if (its->stmt_.return_type() == "Return_opt"){
					res = Return_handler(&(its->stmt_),s2,inputs->name_.text_);
			}
			
			else if (its->stmt_.return_type() == "While"){
					res = While_handler(&(its->stmt_),s2,inputs->name_.text_);
			}
			
			else if (its->stmt_.return_type() == "If"){
					res = If_handler(&(its->stmt_),s2,inputs->name_.text_);
			}
			

			if (res.second == "Type_Check_Error"){
					std::cout<<"Type Error at: "<< res.first <<std::endl;
					exit(1);
			}
			if (res.first != "None"){
				s2->add_to_scope(res.first, res.second);
			}
	}	
	//add input argus into class's sub scope//
//	AST::ASTNode* argus = &(inputs->inputs_args_);
//	AST::Actuals* actuals = static_cast<AST::Actuals*> (argus);
//	s1 = block_traversal(&(inputs->blocks_),s1,actuals); ////////need to fix
	res = make_pair("None", "None");
	return res;
}




pair<string,string> node_handler_switcher(AST::ASTNode* input, Scope* current_scope,string func_name){
	pair<string,string> res;
	if (input->return_type() == "Assign"){
		res = Assign_handler(input,current_scope);
	}
	
	else if (input->return_type() == "Method"){
		res = Method_handler(input,current_scope);
	}
	
	else if (input->return_type() == "If"){
			res = If_handler(input,current_scope,func_name);
		}
	else if (input->return_type() == "While"){
			res = While_handler(input,current_scope,func_name);
	}
	

//	if (input->return_type() == "Method_call"){
//		res = Method_call_handler(input,current_scope);
//	}
	return res;
}



void block_traversal(AST::ASTNode *root,Scope* pre_scope,AST::Actuals* actuals,string func_name){
	AST::Block* inputs = static_cast<AST::Block*> (root);
	Scope* s1= new Scope(pre_scope,"Class_Block");
	pre_scope->next_scope.push_back(s1);
	//add input argus into block's scope.
	std::vector<AST::ASTNode*>::iterator it;
	for (it = actuals->argus_.begin();it != actuals->argus_.end();it++){
		AST::Argus* arg = static_cast<AST::Argus*> (*it);
		s1->add_to_scope(arg->var_name_.text_,arg->var_type_.text_);
	} 
	
	for (it = inputs->stmts_.begin();it != inputs->stmts_.end();it++){
			AST::Statement* its = static_cast<AST::Statement*> (*it);
			pair<string,string> res = node_handler_switcher(&(its->stmt_),s1,func_name);
			if (res.first != "None"){
				s1->add_to_scope(res.first, res.second);
			}
		}
}


void class_traversal(AST::Class *inputs,Scope* pre_scope,string extends){
	Scope* s1= new Scope(pre_scope,"Class");
	pre_scope->next_scope.push_back(s1);
	
	if (extends != "Nothing" && extends != "Obj" && extends != "Int" && extends != "String"){
		Scope* super_scope = pre_scope->search_in_sub_scope(extends);
		vector<std::pair<std::string,std::string> >::iterator it;
		Var_table t = *(super_scope->table);
		for (it = t.content.begin(); it != t.content.end();it++){
			s1->table->content.push_back((*it));
		}
		
	}
	//add input argus into class's sub scope//
	AST::ASTNode* argus = &(inputs->inputs_args_);
	AST::Actuals* actuals = static_cast<AST::Actuals*> (argus);
	string func_name = inputs->name_.text_;
	
	//add class name itself into class scope//
	s1->add_to_scope(inputs->name_.text_,inputs->name_.text_);
	
	//s1->add_to_scope(root->extends_,"class_extends");  //need to fix
	block_traversal(&(inputs->blocks_),s1,actuals,func_name);
	
}


void classes_traversal(AST::ASTNode *root){
	AST::Classes* inputs = static_cast<AST::Classes*> (root);
	vector<AST::ASTNode*>::iterator it;
	Scope* s1= new Scope("Global");
	
	//set up some pre-defined type into class_table
	s1->class_table->content.push_back(make_pair("Obj","Obj"));
	s1->class_table->content.push_back(make_pair("String","Obj"));
	s1->class_table->content.push_back(make_pair("Int","Obj"));
	
	//set up some pre-defined type into Global scope
	s1->add_to_scope("True", "Bool");
	s1->add_to_scope("False", "Bool");
		
	for (it = inputs->clazzs_.begin();it != inputs->clazzs_.end();it++){
		if ((*it)->return_type() == "Class"){
			AST::Class* its = static_cast<AST::Class*> (*it);
			s1->add_to_scope(its->name_.text_,its->name_.text_);
			if(its->extends_.text_ == "Nothing"){
				s1->add_to_class_table(its->name_.text_,"Obj");
				
			}
			else{
				if(s1->class_table->search_in_table(its->extends_.text_) != "Type_Check_Error"){
					s1->add_to_class_table(its->name_.text_,its->extends_.text_);
				}
				else{
					std::cout<< "Type_Check_Error, the super class " << its->extends_.text_<<" of "<<its->name_.text_<<" can't be found in Class_table. "<<std::endl;
					exit(1);
				}
				
			}			
			class_traversal(its,s1,its->extends_.text_);
		}
		if ((*it)->return_type() == "Statement"){
			AST::Statement* its = static_cast<AST::Statement*> (*it);
			pair<string,string> res = node_handler_switcher(&(its->stmt_),s1,"Global");
			s1->add_to_scope(res.first, res.second);
		}
	}
	cout<<"\n------Class_table in Global scope-----\n"<<endl;
	s1->class_table->print_table();
	cout<<"--------------------------------------"<<endl;
	s1->print_sub_scope();
}

//string Plus_handler(AST::ASTNode* input,Scope* current_scope){
//	AST::Plus* inputs = static_cast<AST::Plus*> (input);
//	if (type_check(inputs->left_,current_scope) == type_check(inputs->right_,current_scope)){
//		return type_check(inputs->left_,current_scope);
//	}
//	return "Type_Check_Error";
//}

string Int_handler(){
	return "Int";
}



//string type_check(AST::ASTNode* input, Scope* current_scope){
//	string res;
//	if (input->node_name_ == "Plus"){res = Plus_handler(input,current_scope);}
//	else if (input->node_name_ == "IntConst"){res = Int_handler();}
//	else if (input->node_name_ == "Ident"){res = Ident_handler(input,current_scope);}
//	
//			
//	return res;
//}

