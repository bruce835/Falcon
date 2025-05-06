#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <vector>
#include <cctype>

int tokenize(std::vector<char>& buf, const char& bufChar) {
	std::cout << bufChar;
	return 0;
}

int main(int argc, char *argv[]) {
	std::ifstream src;
	std::string srcPath = argv[1];
	src.open(srcPath);
	std::cout << srcPath << std::endl;
	std::vector<char> buf;
	char ch;
	if (!src) {
		std::cerr << "Source file not found. Exiting.";
		exit(0);
	}

	while (!src.eof()) {
		src.get(ch);
		buf.push_back(ch);
	}
	
	for (const char& bufChar : buf) {
		if (std::isspace(bufChar)) {
			continue;
		}
		else {
			tokenize(buf, bufChar);
		}
	}
	return 0;
}
