#ifndef ABSTRACTIONS_HPP
#define ABSTRACTIONS_HPP
#include <string>
#include <vector>

struct parameter {
  std::string type;
  std::string value;
};

struct func {
  std::vector<std::string> instructions;
  std::vector<parameter> parameters; 
  std::string returnType;
  std::string identifier;
};
#endif
