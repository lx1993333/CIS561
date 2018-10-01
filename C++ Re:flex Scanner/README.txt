reflex Scanner.l
c++ -Ireflex/include -o Scanner lex.yy.cpp reflex/lib/libreflex.a
./Scanner input_test.txt
