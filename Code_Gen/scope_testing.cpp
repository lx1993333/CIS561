#include <iostream>
#include <typeinfo>
#include "Scope.h"
using namespace std;
int main(int argc, char *argv[]) {
	Scope* s1= new Scope();
	s1->add_to_scope("hello","world");
	Scope* s2 = new Scope();
	s2->add_to_scope("b","int");
	
	s1->add_sub_scope(s2);

	s1->print_sub_scope();
	
	//cout<<s3->search_in_scope("b")<<endl;
	
	int k = 1;
	
	
	
}