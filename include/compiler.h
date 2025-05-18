#ifndef COMPILER_H
#define COMPILER_H

#include <vector>
#include <string>
#include <fstream>
#include "../include/lexer.h"
#include "libraries/functions.hpp"

class compiler {
  public:

  std::vector<std::string> toAssembly_print(std::vector<parameter>& params, std::ofstream& writeAsm);
  void toAssembly_function(func& newFunc);
  void asmClear();
};
#endif
