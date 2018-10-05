# scanner-cxx
C++ (bison, re-flex) version of project 1, scanner (aka lexer)

build instructions:
    just use given "Makefile" to build the program. (In shell environment(like terminal), run "make")

After building, run "./lexer <the_path_to_your_input.txt>" to see the outputs. 
The outputs of this pragrom should be somethink like:

CLASS	(258)	@1.1-2.0

BadBreaks   IDENT	(273)	@2.0-5

(	(40)	@2.6-14

x           IDENT	(273)	@2.15

 Int           TYPECASE	(266)	@2.16
 
)	(41)	@2.17-21

it will print out the value of the Token, its Token type and its position in original input code.
