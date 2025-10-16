#ifndef JAVALEXER_H
#define JAVALEXER_H

#include "Token.h"
#include <vector>
#include <string>
#include <unordered_map>

class JavaLexer {
private:
    std::unordered_map<std::string, TokenType> keywords;
    std::unordered_map<std::string, TokenType> operators;
    std::unordered_map<char, TokenType> separators;

    void initializeKeywords();
    void initializeOperators();
    void initializeSeparators();
    bool isHexDigit(char c);
    bool isOperatorChar(char c);
    void skipWhitespace(const std::string& source, size_t& i, int& line, int& column);
    Token processPreprocessor(const std::string& source, size_t& i, int line, int column);
    Token processLineComment(const std::string& source, size_t& i, int line, int column);
    Token processBlockComment(const std::string& source, size_t& i, int& line, int& column);
    Token processStringLiteral(const std::string& source, size_t& i, int& line, int& column);
    Token processCharLiteral(const std::string& source, size_t& i, int& line, int& column);
    Token processNumber(const std::string& source, size_t& i, int line, int column);
    Token processIdentifierOrKeyword(const std::string& source, size_t& i, int line, int column);
    Token processOperator(const std::string& source, size_t& i, int line, int column);
    Token processSeparator(const std::string& source, size_t& i, int line, int column);

public:
    JavaLexer();
    std::vector<Token> tokenize(const std::string& source);
};

#endif