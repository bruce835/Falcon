reset
g++ -std=gnu++2b -g -o falcon src/functions.cpp src/lexer.cpp src/parser.cpp src/compiler.cpp
find . -name "*.o" -type f -delete
rm main
./falcon examples/main.flcn
