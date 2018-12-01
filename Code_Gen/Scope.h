#include <iostream>
#include <vector>
#include <string>


class Var_table{
	public:
		std::vector<std::pair<std::string,std::string> > content;	
		Var_table(){}
		
		void print_table(){
			std::vector<std::pair<std::string,std::string> >::iterator it;
			for (it = content.begin(); it != content.end() ; it++){
				std::cout<< it->first << ": " << it->second <<std::endl;
			}
		}
		
		std::string search_in_table(std::string s){
			std::vector<std::pair<std::string,std::string> >:: iterator it;
			for (it = content.begin(); it != content.end();it++){
				if (it->first == s){
					return it->second;
				}
			}
			return "Type_Check_Error";
		}
		
		std::pair<std::string,std::string>* get_content(std::string s){
			std::vector<std::pair<std::string,std::string> >:: iterator it;
			for (it = content.begin(); it != content.end();it++){
				if (it->first == s){
					return &(*it);
				}
			}
			
			std::pair<std::string,std::string> p = make_pair("Type_Check_Error","Type_Check_Error");
			std::pair<std::string,std::string>* res = &p;
			return res;
		}

		
		void delete_in_table(std::string s){
			std::vector<std::pair<std::string,std::string> >:: iterator it;
			for (it = content.begin(); it != content.end();it++){
				if (it->first == s){
					content.erase(it);
					break; 
				}
			}
		}
		
//		std::string hierarchy_search(std::string s, std::string target){
//			
////	std::vector<std::pair<std::string,std::string> >:: iterator it;		
////			if (s == target){
////				return s;
////			}
////			
////			for (it = content.begin(); it != content.end();it++){
////				if (s != search_in_table(s)){
////					return hierarchy_search(search_in_table(s), target);
////				}
////				else{
////					if(s == target){
////						return s;
////					}
////					return "hierarchy_search failed";
////				}
////			}
////			return "hierarchy_search failed";
//		}
		
		bool hierarchy_check(std::string s, std::string target){
			std::vector<std::pair<std::string,std::string> >:: iterator it;
			if (s == target){
				return true;
			}
			for (it = content.begin(); it != content.end();it++){
				if (s != search_in_table(s)){
					return hierarchy_check(search_in_table(s), target);
				}
				else{
					if(s == target){
						return true;
					}
					return false;
				}
			}
			return false;
		}
		
};


class Scope{
	public:
		Scope *previous_scope;
		std::vector<Scope*> next_scope;
		Var_table* table;
		Var_table* class_table;
		std::string scope_name;
		Scope(Scope *pre_scope,std::string name){
			previous_scope = pre_scope;
			table = new Var_table();
			scope_name = name;
			class_table = new Var_table();
		}
		Scope(std::string name){
			previous_scope = NULL;
			table = new Var_table();
			scope_name = name;
			class_table = new Var_table();
		}	
		
		void print_scope(){
			table->print_table();
		}
		
		void print_sub_scope(){
			std::vector<Scope*>:: iterator it;
			print_scope();
			int counter = 0;
			for (it = next_scope.begin(); it != next_scope.end();it++){ 
				std::cout<<"{ \n"<<(*it)->scope_name<<": "<<std::endl;
				if ((*it)->scope_name == "Class"){
					std::cout<<"---Class Method Table---"<<": { \n";
					(*it)->class_table->print_table();
					std::cout<<" }"<<std::endl;
				}
				(*it)->print_sub_scope();
				std::cout<<" }"<<std::endl;
				counter+=1;
			}
		}
		
		std::string search_in_scope(std::string s){
			std::string res = table->search_in_table(s);
			if (res == "Type_Check_Error"){
				Scope *pre_scope = previous_scope;
				while (pre_scope){
					res = previous_scope->table->search_in_table(s);
					if (res != "Type_Check_Error"){
						return res;
					}
					pre_scope = pre_scope->previous_scope;
				}
			}
			return res;
		}
		
		Scope* search_in_sub_scope(std::string s){
			std::vector<Scope*>::iterator it;
			for(it = next_scope.begin(); it != next_scope.end();it++){
				std::string res = (*it)->table->search_in_table(s);
				if (res != "Type_Check_Error"){
					return (*it);
				}
			}
			std::cout<< "Type_Check_Error, "<<s<<" can't be found in all sub_scopes of "<<scope_name<<std::endl;
			exit(1);
		}

		
		Scope* find_sub_scope(std::string s){
			std::vector<Scope*>::iterator it;
			for(it = next_scope.begin(); it != next_scope.end();it++){
				//cout<<(*it)->scope_name<<endl;
				if ((*it)->scope_name == s){
					return (*it);
				}
			}
			std::cout<< "find_sub_scope_Error, "<<s<<" can't be found in all sub_scopes of "<<scope_name<<std::endl;
			exit(1);
		}
		
	
		void add_to_scope(std::string s1, std::string s2){
			std::pair<std::string, std::string> p = make_pair(s1,s2);
			//override the existing type in table
//			if (table->search_in_table(s1) != "Type_Check_Error"){
//				table->delete_in_table(s1);
//			}
			if (table->search_in_table(s1) != "Type_Check_Error" && table->search_in_table(s1) != s2){
				if(!class_table->hierarchy_check(table->search_in_table(s1),s2)){
					std::cout<< "Type_Check_Error: The type of "<<s1<<" is not consistent with its previous definition!"<<std::endl;
					exit(1);
				}
				else{
					table->delete_in_table(s1);
				}
			}
			if (table->search_in_table(s1) == s2){
				return;
			}
			table->content.push_back(p);
		}
		
		
		void add_to_class_scope(std::string s1, std::string s2){
			std::pair<std::string, std::string> p = make_pair(s1,s2);
			//override the existing type in table
//			if (table->search_in_table(s1) != "Type_Check_Error"){
//				table->delete_in_table(s1);
//			}
			if (table->search_in_table(s1) != "Type_Check_Error" && table->search_in_table(s1) != s2){
				table->delete_in_table(s1);
			}
			if (table->search_in_table(s1) == s2){
				return;
			}
			table->content.push_back(p);
		}
		
		
		void add_to_class_Method_table(std::string s1, std::string s2){
			std::pair<std::string, std::string> p = make_pair(s1,s2);
			//override the existing type in table
//			if (table->search_in_table(s1) != "Type_Check_Error"){
//				table->delete_in_table(s1);
//			}
			if (class_table->search_in_table(s1) != "Type_Check_Error" && class_table->search_in_table(s1) != s2){
				class_table->delete_in_table(s1);
			}
			if (class_table->search_in_table(s1) == s2){
				return;
			}
			class_table->content.push_back(p);
		}

		
		
		void add_to_class_table(std::string s1, std::string s2){
			std::pair<std::string, std::string> p = make_pair(s1,s2);
			//override the existing type in table
//			if (table->search_in_table(s1) != "Type_Check_Error"){
//				table->delete_in_table(s1);
//			}
			if (class_table->search_in_table(s1) != "Type_Check_Error" && class_table->search_in_table(s1) != s2){
				if(!class_table->hierarchy_check(table->search_in_table(s1),s2)){
					std::cout<< "Type_Check_Error: The type of "<<s1<<" is not consistent with its previous definition!"<<std::endl;
					exit(1);
				}
			}
			if (class_table->search_in_table(s1) == s2){
				return;
			}
			class_table->content.push_back(p);
		}
		
		void add_sub_scope(Scope* scopes){
			next_scope.push_back(scopes);
		}
		
		void ckeck_table(){
			std::vector<std::pair<std::string,std::string> >:: iterator it;
			for (it = table->content.begin(); it != table->content.end();it++){
				if ((*it).second == "Nothing"){
					std::cout<< "Failed to init "<<(*it).first<<" inside "<< scope_name <<std::endl;
					exit(1);
				}
			}
		}
		
		
		std::string find_lca(std::string type1, std::string type2){
			Scope* searching_scope = previous_scope;
			while(searching_scope && searching_scope->scope_name != "Global"){
				searching_scope = searching_scope->previous_scope;
			}
			Var_table* searching_table = searching_scope->class_table;
			
			std::vector<std::string> type1_hierarchy;  			std::vector<std::string> type2_hierarchy;
			
			string search_type = type1;
			while (search_type != "Obj"){   //put all type1's hierarchy type into a vector.
				type1_hierarchy.push_back(search_type);
				search_type = searching_table->search_in_table(search_type);
			}
			type1_hierarchy.push_back("Obj");
			
			search_type = type2;
			while (search_type != "Obj"){   //put all type2's hierarchy type into a vector.
				type2_hierarchy.push_back(search_type);
				search_type = searching_table->search_in_table(search_type);
			}
			type2_hierarchy.push_back("Obj");
			
			
			std::vector<std::string>:: iterator it1;
			std::vector<std::string>:: iterator it2;
			for (it1 = type1_hierarchy.begin(); it1 != type1_hierarchy.end();it1++){     //find if there is an overlap between type1 ans 2's hierarchy types, if there is , that overlaped type is the LCA.
				for (it2 = type2_hierarchy.begin(); it2 != type2_hierarchy.end();it2++){
					if ((*it1) == (*it2)){
						return (*it1);
					}
				}
			}
			
			return  "Obj";    // at least both scope has type "Obj" as LCA.
		}
		
	
		bool scope_comnpare(Scope* other){
			std::vector<std::pair<std::string,std::string> >:: iterator it;
			for (it = table->content.begin(); it != table->content.end();it++){
				if (other->table->search_in_table((*it).first) != "Type_Check_Error"){  //if we can find there is a var with same name in other scope
					string res = find_lca((*it).second,other->table->search_in_table((*it).first)); //found least common ancestor
					(*it).second = res;
					(*(other->table->get_content((*it).first))).second = res;
				}
			}
			return true;
		}
};

