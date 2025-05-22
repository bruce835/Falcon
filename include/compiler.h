#ifndef COMPILER_H
#define COMPILER_H

#include <vector>
#include <string>
#include <fstream>
#include "lexer_main.h"
#include "libraries/abstractions.hpp"

extern bool usingMacos;
extern bool usingLinux;
class compiler {
  public:

  std::vector<std::string> toAssembly_print(std::vector<parameter>& params, std::ofstream& writeAsm);
  void toAssembly_function(func& newFunc);
  void asmClear();
};
#endif
