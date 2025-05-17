reset
g++ -std=gnu++2b -g -Wall -I/home/robin/lexy/include -o falcon src/lexer.cpp src/parser.cpp src/compiler.cpp
sudo ./falcon examples/main.flcn
