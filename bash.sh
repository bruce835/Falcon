reset
g++ -std=gnu++2b -g -o falcon src/lexer.cpp src/parser.cpp src/compiler.cpp
sudo ./falcon examples/main.flcn -f
