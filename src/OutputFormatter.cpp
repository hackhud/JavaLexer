#include <iostream>
#include <iomanip>
#include "OutputFormatter.h"

std::string OutputFormatter::tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::KEYWORD: return "KEYWORD";
        case TokenType::INTEGER_LITERAL: return "INTEGER_LITERAL";
        case TokenType::FLOAT_LITERAL: return "FLOAT_LITERAL";
        case TokenType::HEX_LITERAL: return "HEX_LITERAL";
        case TokenType::STRING_LITERAL: return "STRING_LITERAL";
        case TokenType::CHAR_LITERAL: return "CHAR_LITERAL";
        case TokenType::BOOLEAN_LITERAL: return "BOOLEAN_LITERAL";
        case TokenType::IDENTIFIER: return "IDENTIFIER";
        case TokenType::OPERATOR: return "OPERATOR";
        case TokenType::SEPARATOR: return "SEPARATOR";
        case TokenType::LINE_COMMENT: return "LINE_COMMENT";
        case TokenType::BLOCK_COMMENT: return "BLOCK_COMMENT";
        case TokenType::PREPROCESSOR: return "PREPROCESSOR";
        case TokenType::UNRECOGNIZED: return "UNRECOGNIZED";
        case TokenType::UNTERMINATED_STRING: return "UNTERMINATED_STRING";
        case TokenType::UNTERMINATED_CHAR: return "UNTERMINATED_CHAR";
        case TokenType::UNTERMINATED_COMMENT: return "UNTERMINATED_COMMENT";
        default: return "UNKNOWN";
    }
}

void OutputFormatter::printColoredOutput(const std::vector<Token>& tokens) {
    for (size_t i = 0; i < tokens.size(); ++i) {
        const auto& token = tokens[i];

        if (i > 0) {
            bool needsSpace = true;
            std::string prevValue = tokens[i-1].value;
            std::string currentValue = token.value;

            if (prevValue == "(" || prevValue == "[" || prevValue == "{" ||
                prevValue == "." || prevValue == "::" || prevValue == "->" ||
                prevValue == "@") {
                needsSpace = false;
            }

            if (currentValue == ")" || currentValue == "]" || currentValue == "}" ||
                currentValue == "." || currentValue == "," || currentValue == ";" ||
                currentValue == "::" || currentValue == "->") {
                needsSpace = false;
            }

            if (tokens[i-1].type == TokenType::LINE_COMMENT ||
                tokens[i-1].type == TokenType::BLOCK_COMMENT) {
                needsSpace = true;
            }

            if (needsSpace) {
                std::cout << " ";
            }
        }

        switch (token.type) {
            case TokenType::KEYWORD:
                std::cout << "\033[1;35m" << token.value << "\033[0m";
                break;
            case TokenType::INTEGER_LITERAL:
            case TokenType::FLOAT_LITERAL:
            case TokenType::HEX_LITERAL:
                std::cout << "\033[1;33m" << token.value << "\033[0m";
                break;
            case TokenType::STRING_LITERAL:
            case TokenType::CHAR_LITERAL:
                std::cout << "\033[1;32m" << token.value << "\033[0m";
                break;
            case TokenType::BOOLEAN_LITERAL:
                std::cout << "\033[1;36m" << token.value << "\033[0m";
                break;
            case TokenType::IDENTIFIER:
                std::cout << "\033[1;37m" << token.value << "\033[0m";
                break;
            case TokenType::OPERATOR:
            case TokenType::SEPARATOR:
                std::cout << "\033[1;34m" << token.value << "\033[0m";
                break;
            case TokenType::LINE_COMMENT:
            case TokenType::BLOCK_COMMENT:
                std::cout << "\033[1;30m" << token.value << "\033[0m";
                break;
            case TokenType::PREPROCESSOR:
                std::cout << "\033[1;31m" << token.value << "\033[0m";
                break;
            case TokenType::UNRECOGNIZED:
            case TokenType::UNTERMINATED_STRING:
            case TokenType::UNTERMINATED_CHAR:
            case TokenType::UNTERMINATED_COMMENT:
                std::cout << "\033[1;41m" << token.value << "\033[0m";
                break;
            default:
                std::cout << token.value;
        }
    }
    std::cout << std::endl;
}

void OutputFormatter::printTokenList(const std::vector<Token>& tokens) {
    std::cout << "Line\tColumn\tType\t\t\tValue\n";
    std::cout << "----\t------\t----\t\t\t-----\n";

    for (const auto& token : tokens) {
        std::cout << token.line << "\t" << token.column << "\t"
                  << std::left << std::setw(20) << tokenTypeToString(token.type)
                  << token.value << std::endl;
    }
}