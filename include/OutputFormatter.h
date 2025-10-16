#ifndef OUTPUTFORMATTER_H
#define OUTPUTFORMATTER_H

#include "Token.h"
#include <vector>
#include <string>

class OutputFormatter {
public:
    static void printColoredOutput(const std::vector<Token>& tokens);
    static void printTokenList(const std::vector<Token>& tokens);
    static std::string tokenTypeToString(TokenType type);
};

#endif