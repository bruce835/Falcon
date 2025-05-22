#include <vector>
#include <string>
#include <fstream>
#include "../../include/tokenProcessor.h"
#include "../../include/lexer_main.h"

void processTokens(std::vector<char>& buf, const char& ch, std::ifstream& src) {
  if (std::isspace(ch)) {
    if (ch == '\n') {
      lineNumber++;
    }

    if (tokenType != "String") {
      tokenize(tokens, buf, src);
    }
    
    else {
      buf.push_back(ch);
    }
    return;
  }

  else if (ch == ',') {
    if (tokenType != "String") { 
    tokenize(tokens, buf, src);
      if (buf.empty()) {
        tokenType = ",";
        buf.push_back(ch);
        tokenize(tokens, buf, src);
      }
      return;
    }
    
    else {
      buf.push_back(ch);
    }
  }

  else if (ch == '\"') {
    if (tokenType != "String") {
      tokenize(tokens, buf, src);
      tokenType = "\"";
      buf.push_back(ch);
      tokenize(tokens, buf, src);
      tokenType = "String";
    }

    else {
      tokenize(tokens, buf, src);
      buf.push_back(ch);
      tokenType = "\"";
      tokenize(tokens, buf, src);
    }
    return;
  }
  
  else if (tokenType != "String") {

   if (ch == '(' || ch == ')') {
    tokenize(tokens, buf, src);
    tokenType = std::string(1, ch);
    buf.push_back(ch);
    tokenize(tokens, buf, src);
  }
    
    else if (ch == '{' || ch == '}') {
      tokenize(tokens, buf, src);
      tokenType = std::string(1, ch);
      buf.push_back(ch);
      tokenize(tokens, buf, src);
    }

    else if (ch == ';') {
     tokenize(tokens, buf, src);
     tokenType = ";";
     buf.push_back(ch);
     tokenize(tokens, buf, src);
    }

    else {
      buf.push_back(ch);
    }
    return;
  }
  
  else if (tokenType == "String") {
    buf.push_back(ch);
  }
  return;
}
