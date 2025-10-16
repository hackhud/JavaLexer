#include "JavaLexer.h"
#include "OutputFormatter.h"
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file.java> <output_mode>\n";
        std::cerr << "Output modes:\n";
        std::cerr << "  color  - Colored syntax highlighting\n";
        std::cerr << "  list   - Token list with details\n";
        return 1;
    }

    std::string filename = argv[1];
    std::string mode = argv[2];

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return 1;
    }

    std::string source((std::istreambuf_iterator<char>(file)),
                       std::istreambuf_iterator<char>());
    file.close();

    JavaLexer lexer;
    std::vector<Token> tokens = lexer.tokenize(source);

    if (mode == "color") {
        OutputFormatter::printColoredOutput(tokens);
    } else if (mode == "list") {
        OutputFormatter::printTokenList(tokens);
    } else {
        std::cerr << "Error: Unknown output mode '" << mode << "'\n";
        return 1;
    }

    return 0;
}