#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../include/compiler.h"
#include "../include/lexer.h"
#include <fstream>
#include <iostream>

  bool usingWindows = false;
  bool usingMacOS = false;  
  bool usingLinux = false;  

  std::string writeCode;
  std::string exitCode;

  std::vector<std::string> data;

  int litStringCount = 0;

  int checkSyscode() {
      #if defined(_WIN32) || defined(_WIN64)
        usiongWindows = true;
      #elif defined(__APPLE__) && defined(__MACH__)
        usingMacOS = true;
      #elif defined(__linux__)
        usingLinux = true;
      #endif

        
      if(usingMacOS) {
        writeCode = "0x2000004";
        exitCode = "0x2000001";
      }

      else if (usingLinux) {
        writeCode = "1";
        exitCode = "60";
      }
      return 0;
  }
    
  void compiler::asmClear() {
    checkSyscode();
    std::ofstream asmFile("asm/example.asm", std::iostream::trunc); 
    asmFile << "section .text\n";
    asmFile << "  global _start\n";
    asmFile << "\n_start:\n";
    asmFile << "  call main";
    asmFile << "\n\n  mov rax, " << exitCode << "\n";
    asmFile << "  xor rdi, rdi\n";
    asmFile << "  syscall\n";
    asmFile.close();
  }

  std::vector<std::string> toAssembly_print(std::vector<parameter>& params, std::ofstream& writeAsm) {
    for (auto& param : params) {
      if (param.type != "String"){
        std::cerr << "Expected 'String', found'" << param.type << "'.\n";
      }
      
      else { 
        writeAsm << " lea rsi, [rel+litString_" + std::to_string(litStringCount) + "]";
        writeAsm << "\n mov rdx, " + std::to_string(param.value.size()) + "\n";
        writeAsm << " mov rdi, 1\n";
        writeAsm << " mov rax, " << writeCode << "\n";
        writeAsm << " syscall\n";
        data.push_back("litString_" + std::to_string(litStringCount) + ": db \"" + param.value + "\", 0");
        litStringCount++;
      }
    }
   return data; 
  }

  std::vector<std::string> processInstruction(instruction& instr, std::ofstream& writeAsm, func& newFunc) {
    if (instr.keyword == "print") {
      data = (toAssembly_print(instr.parameters, writeAsm));
    }

    else if (instr.keyword == "return") {

    if(newFunc.returnType == "int") {
      writeAsm << " mov rax, ";
     if (newFunc.returnValues.empty()) {
       writeAsm << "0";
     } 
     
     else {
       writeAsm << *newFunc.returnValues.begin();
       newFunc.returnValues.erase(newFunc.returnValues.begin());
     }
     writeAsm << "\n";
    }

      writeAsm << " pop rbp\n";
      writeAsm << " ret\n";       
    }
    return data;
  }

  void compiler::toAssembly_function(func& newFunc) {
    std::ofstream writeAsm("asm/example.asm", std::iostream::app);
    writeAsm << "\n" << newFunc.identifier << ":\n";

    writeAsm << " push rbp\n";
    writeAsm << " mov rbp, rsp\n";
  
    for(instruction& instr : newFunc.instructions) {
      data = processInstruction(instr, writeAsm, newFunc);
    }

    if(newFunc.returnType == "int") {
      writeAsm << " mov rax, ";
     if (newFunc.returnValues.empty()) {
       writeAsm << "0";
     } 
     
     else {
       writeAsm << *newFunc.returnValues.begin();
       newFunc.returnValues.erase(newFunc.returnValues.begin());
     }
     writeAsm << "\n";
    }

    writeAsm << " pop rbp\n";
    writeAsm << " ret\n";

    for (std::string& line : data) {
      writeAsm << line << "\n";
    }

    data.clear();
    writeAsm.close();
    return;
  }
