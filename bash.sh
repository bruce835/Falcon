reset
g++ -std=gnu++2b -g -o falcon src/lexer/tokenProcessor.cpp src/functions.cpp src/lexer/lexer_main.cpp src/parser.cpp src/compiler.cpp
find . -name "*.o" -type f -delete
find . -name "*.asm" -type f -delete
rm main
./falcon examples/main.flcn
