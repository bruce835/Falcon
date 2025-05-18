#ifndef ABSTRACTIONS_HPP
#define ABSTRACTIONS_HPP
#include <string>
#include <vector>

struct parameter {
  std::string type;
  std::string value;
};

struct instruction {
  std::vector<parameter> parameters;
  std::string keyword;
};

struct func {
  std::vector<instruction> instructions;
  std::vector<parameter> parameters; 
  std::string returnType;
  std::string identifier;
  int paramCount;
};
#endif
