%top{
	#include <cstdio>
	#include <iostream>
	#include <iomanip>
	using namespace std;
%}

%class{
	string res;
 public:
	void print() {
		cout << res << endl;
	}
%}


%option unicode


word    (\w|\h\w)+
dquo   ["]{word}["]
quo   [']{word}[']
new_line \n



%%


{dquo} {string s_l = text(); s_l.erase(0,1).erase(s_l.end()-1,s_l.end()); res += "&ldquo "+s_l+" &rdquo";}
{quo} {string s_s = text(); s_s.erase(0,1).erase(s_s.end()-1,s_s.end()); res += "&lquo "+s_s+" &rquo";}
{new_line} res += '\n';
.   res += text();

%%

int main(int argc, char **argv) {
	FILE *fd = stdin;
	if (argc < 2){
		cout<<"please input a txt file as argument from command line! 'Usage: $./Scanner input_test.txt' "<<endl;
		exit(EXIT_FAILURE);
	}
	if ((fd = fopen(argv[1], "r")) == NULL){
		cout<<"open input txt file failed!"<<endl;
		exit(EXIT_FAILURE);

	}
	// create a lexer that consumes a file or reads stdin
	Lexer lexer(fd);
	lexer.lex();
	// display the results
	//lexer.results();
	lexer.print();
	if (fd != stdin)
		fclose(fd);
	return 0;
}