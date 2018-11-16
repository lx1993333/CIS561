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
		
		void delete_in_table(std::string s){
			std::vector<std::pair<std::string,std::string> >:: iterator it;
			for (it = content.begin(); it != content.end();it++){
				if (it->first == s){
					content.erase(it);
					break; 
				}
			}
		}
		
		bool hierarchy_search(std::string s, std::string target){
			std::vector<std::pair<std::string,std::string> >:: iterator it;
			if (s == target){
				return true;
			}
			for (it = content.begin(); it != content.end();it++){
				if (s != search_in_table(s)){
					return hierarchy_search(search_in_table(s), target);
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
		
		void add_to_scope(std::string s1, std::string s2){
			std::pair<std::string, std::string> p = make_pair(s1,s2);
			//override the existing type in table
//			if (table->search_in_table(s1) != "Type_Check_Error"){
//				table->delete_in_table(s1);
//			}
			if (table->search_in_table(s1) != "Type_Check_Error" && table->search_in_table(s1) != s2){
				std::cout<< "Type_Check_Error: The type of "<<s1<<" is not consistent with its previous definition!"<<std::endl;
				exit(1);
			}
			if (table->search_in_table(s1) == s2){
				return;
			}
			table->content.push_back(p);
		}
		
		
		void add_to_class_table(std::string s1, std::string s2){
			std::pair<std::string, std::string> p = make_pair(s1,s2);
			//override the existing type in table
//			if (table->search_in_table(s1) != "Type_Check_Error"){
//				table->delete_in_table(s1);
//			}
			if (class_table->search_in_table(s1) != "Type_Check_Error" && class_table->search_in_table(s1) != s2){
				std::cout<< "Type_Check_Error: The type of "<<s1<<" is not consistent with its previous definition!"<<std::endl;
				exit(1);
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
	
};

