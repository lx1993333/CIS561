#C++ (bison, re-flex) version of project 4, Type checker

************ Not final version, still working on it ****************

build instructions: 
* Make sure the path lead to include/reflex was added in the enviroment. (for C++, use 'export CPLUS_INCLUDE_PATH="$CPLUS_INCLUDE_PATH:/usr/local/include"')
* Use cmake to build and link files. Then use "Makefile" to build the program. (In shell environment(like terminal), run "make")

After building, run "./parser <the_path_to_your_input.txt>" to see the outputs. The output should be of hierarchy of scopes of source code and variables with their types, or an Error message. 
