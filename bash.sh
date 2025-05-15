reset
g++ -std=c++23 -g -Wall -I/home/robin/lexy/include -o falcon src/lexer.cpp src/parser.cpp src/compiler.cpp
./falcon examples/main.flcn
