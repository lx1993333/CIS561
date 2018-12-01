#C++ (bison, re-flex) version of project 5, Code Generator

************ Not final version, still working on it ****************
Right now this generator supports Quack language with:
    1.Class object initialization.
    2.Variables initialization.
    2.Controll flow(if statement/while loop).
    3.Dynamic dispathing.
    4.Class method call.
    5.Part of class inheritance.
    6.Class method overriding. 
It don't support:
    1. Type case.
    2. Class member inheritance.


build instructions: 
* Make sure the path lead to include/reflex was added in the enviroment. (for C++, use 'export CPLUS_INCLUDE_PATH="$CPLUS_INCLUDE_PATH:/usr/local/include"')
* Use cmake to build and link files. Then use "Makefile" to build the program. (In shell environment(like terminal), run "make")

After building, run "./parser <the_path_to_your_input.txt>" to see the outputs. The output should be a C file called "C_output.c". This file shoueld be compiled with "-std=c11". 
