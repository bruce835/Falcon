reset
g++ -std=c++17 -g -Iinclude -o falcon src/lexer/tokenProcessor.cpp src/functions.cpp src/lexer/lexer_main.cpp src/parser/parser_main.cpp src/compiler.cpp
find . -name "*.o" -type f -delete
find . -name "*.asm" -type f -delete
rm main
./falcon examples/main.flcn
