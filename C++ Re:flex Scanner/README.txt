Basically, what this scanner does is it replacing all paired double quotation/single quotation marks with &ldquo;, &rdquo;, &lquo;, or &rquo (left and right double quotes and left and right single quotes), and leaving the rest content same. 

build instructions:
    1.Install Re/flex Lib for C++.
    2.In shell environment(like terminal), run "reflex Scanner.l"
    3.In shell environment(like terminal), run "c++ -Ireflex/include -o Scanner lex.yy.cpp reflex/lib/libreflex.a"
    4.bulding should finished.

After building, run "./Scanner <your_input.txt>" to see the result. Could use input_test.txt provided in this repo as test file.

