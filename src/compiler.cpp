#include <iostream>
#include <fstream>
#include <vector>
#include "../include/compiler.h"
#include "../include/lexer.h"

void toAssembly(const std::vector<Token>& tokens) {
  std::cout << "\nCompiling\n";
  std::fstream asmFile("asm/example.asm", std::iostream::out);

  if (!asmFile) {
    std::cout << "bruh";
  }

  asmFile << "section .data\n";
  for (const Token& token : tokens) {
    if (token.type == "String") {
      asmFile << "  msg db \"" << token.value << "\", 0xA\n";
      asmFile << "  msg_len equ $ - msg\n\n";
    }
  }

  asmFile <<"section .text\n";
  asmFile << "global _start\n\n";
  asmFile << "_start:\n";

  for (const Token& token : tokens) {
    if (token.type == "Keyword") {
      if (token.value == "print") {
        asmFile << "  mov rax, 1\n";    // syscall number (sys_write)
        asmFile << "  mov rdi, 1\n";    // file descriptor (stdout)
        asmFile << "  mov rsi, msg\n";  // pointer to message
        asmFile << "  mov rdx, msg_len\n"; // message length
        asmFile << "  syscall\n\n";
      }
    }
  }
  
      asmFile << "  mov rax, 60\n";  // syscall number (sys_exit)
    asmFile << "  xor rdi, rdi\n"; // Exit status 0
    asmFile << "  syscall\n";
  
  asmFile.close();
  exit(0);
}
