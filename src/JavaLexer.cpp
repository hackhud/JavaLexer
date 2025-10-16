#include "JavaLexer.h"
#include <cctype>

void JavaLexer::initializeKeywords() {
    keywords = {
            {"byte", TokenType::KEYWORD}, {"short", TokenType::KEYWORD},
            {"int", TokenType::KEYWORD}, {"long", TokenType::KEYWORD},
            {"float", TokenType::KEYWORD}, {"double", TokenType::KEYWORD},
            {"char", TokenType::KEYWORD}, {"boolean", TokenType::KEYWORD},
            {"void", TokenType::KEYWORD},
            {"public", TokenType::KEYWORD}, {"private", TokenType::KEYWORD},
            {"protected", TokenType::KEYWORD}, {"static", TokenType::KEYWORD},
            {"final", TokenType::KEYWORD}, {"abstract", TokenType::KEYWORD},
            {"synchronized", TokenType::KEYWORD}, {"volatile", TokenType::KEYWORD},
            {"transient", TokenType::KEYWORD}, {"native", TokenType::KEYWORD},
            {"if", TokenType::KEYWORD}, {"else", TokenType::KEYWORD},
            {"for", TokenType::KEYWORD}, {"while", TokenType::KEYWORD},
            {"do", TokenType::KEYWORD}, {"switch", TokenType::KEYWORD},
            {"case", TokenType::KEYWORD}, {"default", TokenType::KEYWORD},
            {"break", TokenType::KEYWORD}, {"continue", TokenType::KEYWORD},
            {"return", TokenType::KEYWORD},
            {"class", TokenType::KEYWORD}, {"interface", TokenType::KEYWORD},
            {"enum", TokenType::KEYWORD}, {"extends", TokenType::KEYWORD},
            {"implements", TokenType::KEYWORD}, {"super", TokenType::KEYWORD},
            {"this", TokenType::KEYWORD}, {"new", TokenType::KEYWORD},
            {"instanceof", TokenType::KEYWORD},
            {"try", TokenType::KEYWORD}, {"catch", TokenType::KEYWORD},
            {"finally", TokenType::KEYWORD}, {"throw", TokenType::KEYWORD},
            {"throws", TokenType::KEYWORD},
            {"package", TokenType::KEYWORD}, {"import", TokenType::KEYWORD},
            {"assert", TokenType::KEYWORD}, {"const", TokenType::KEYWORD},
            {"goto", TokenType::KEYWORD}, {"strictfp", TokenType::KEYWORD},
            {"true", TokenType::BOOLEAN_LITERAL}, {"false", TokenType::BOOLEAN_LITERAL},
            {"null", TokenType::KEYWORD}
    };
}

void JavaLexer::initializeOperators() {
    operators = {
            {"+", TokenType::OPERATOR}, {"-", TokenType::OPERATOR},
            {"*", TokenType::OPERATOR}, {"/", TokenType::OPERATOR},
            {"%", TokenType::OPERATOR}, {"=", TokenType::OPERATOR},
            {"+=", TokenType::OPERATOR}, {"-=", TokenType::OPERATOR},
            {"*=", TokenType::OPERATOR}, {"/=", TokenType::OPERATOR},
            {"%=", TokenType::OPERATOR}, {"==", TokenType::OPERATOR},
            {"!=", TokenType::OPERATOR}, {">", TokenType::OPERATOR},
            {"<", TokenType::OPERATOR}, {">=", TokenType::OPERATOR},
            {"<=", TokenType::OPERATOR}, {"&&", TokenType::OPERATOR},
            {"||", TokenType::OPERATOR}, {"!", TokenType::OPERATOR},
            {"&", TokenType::OPERATOR}, {"|", TokenType::OPERATOR},
            {"^", TokenType::OPERATOR}, {"~", TokenType::OPERATOR},
            {"<<", TokenType::OPERATOR}, {">>", TokenType::OPERATOR},
            {">>>", TokenType::OPERATOR}, {"++", TokenType::OPERATOR},
            {"--", TokenType::OPERATOR}, {".", TokenType::OPERATOR},
            {"::", TokenType::OPERATOR}, {"?", TokenType::OPERATOR},
            {":", TokenType::OPERATOR}
    };
}

void JavaLexer::initializeSeparators() {
    separators = {
            {'(', TokenType::SEPARATOR}, {')', TokenType::SEPARATOR},
            {'{', TokenType::SEPARATOR}, {'}', TokenType::SEPARATOR},
            {'[', TokenType::SEPARATOR}, {']', TokenType::SEPARATOR},
            {';', TokenType::SEPARATOR}, {',', TokenType::SEPARATOR}
    };
}

bool JavaLexer::isHexDigit(char c) {
    return std::isxdigit(c);
}

bool JavaLexer::isOperatorChar(char c) {
    return std::string("+-*/%=!&|^~<>?:").find(c) != std::string::npos;
}

void JavaLexer::skipWhitespace(const std::string& source, size_t& i, int& line, int& column) {
    while (i < source.length() && std::isspace(source[i])) {
        if (source[i] == '\n') {
            line++;
            column = 1;
        } else {
            column++;
        }
        i++;
    }
}

Token JavaLexer::processPreprocessor(const std::string& source, size_t& i, int line, int column) {
    size_t start = i;
    while (i < source.length() && source[i] != '\n') {
        i++;
    }
    return Token(TokenType::PREPROCESSOR, source.substr(start, i - start), line, column);
}

Token JavaLexer::processLineComment(const std::string& source, size_t& i, int line, int column) {
    size_t start = i;
    while (i < source.length() && source[i] != '\n') {
        i++;
    }
    return Token(TokenType::LINE_COMMENT, source.substr(start, i - start), line, column);
}

Token JavaLexer::processBlockComment(const std::string& source, size_t& i, int& line, int& column) {
    size_t start = i;
    i += 2;
    bool terminated = false;

    while (i < source.length()) {
        if (source[i] == '\n') {
            line++;
            column = 0;
        }

        if (source[i] == '*' && i + 1 < source.length() && source[i + 1] == '/') {
            i += 2;
            terminated = true;
            break;
        }
        i++;
    }

    if (!terminated) {
        return Token(TokenType::UNTERMINATED_COMMENT, source.substr(start, i - start), line, column);
    }
    return Token(TokenType::BLOCK_COMMENT, source.substr(start, i - start), line, column);
}

Token JavaLexer::processStringLiteral(const std::string& source, size_t& i, int& line, int& column) {
    size_t start = i;
    i++;
    bool terminated = false;
    bool escape = false;

    while (i < source.length()) {
        if (source[i] == '\n') {
            line++;
            column = 0;
        }

        if (escape) {
            escape = false;
        } else if (source[i] == '\\') {
            escape = true;
        } else if (source[i] == '"') {
            i++;
            terminated = true;
            break;
        }
        i++;
    }

    if (!terminated) {
        return Token(TokenType::UNTERMINATED_STRING, source.substr(start, i - start), line, column);
    }
    return Token(TokenType::STRING_LITERAL, source.substr(start, i - start), line, column);
}

Token JavaLexer::processCharLiteral(const std::string& source, size_t& i, int& line, int& column) {
    size_t start = i;
    i++;
    bool terminated = false;
    bool escape = false;

    while (i < source.length()) {
        if (source[i] == '\n') {
            line++;
            column = 0;
        }

        if (escape) {
            escape = false;
        } else if (source[i] == '\\') {
            escape = true;
        } else if (source[i] == '\'') {
            i++;
            terminated = true;
            break;
        }
        i++;
    }

    if (!terminated) {
        return Token(TokenType::UNTERMINATED_CHAR, source.substr(start, i - start), line, column);
    }
    return Token(TokenType::CHAR_LITERAL, source.substr(start, i - start), line, column);
}

Token JavaLexer::processNumber(const std::string& source, size_t& i, int line, int column) {
    size_t start = i;
    bool isFloat = false;
    bool isHex = false;

    if (source[i] == '0' && i + 1 < source.length() && (source[i + 1] == 'x' || source[i + 1] == 'X')) {
        isHex = true;
        i += 2;
    }

    while (i < source.length() && (std::isdigit(source[i]) ||
                                   (isHex && isHexDigit(source[i])) ||
                                   source[i] == '.' || source[i] == 'e' || source[i] == 'E' ||
                                   source[i] == '+' || source[i] == '-' || source[i] == 'f' ||
                                   source[i] == 'F' || source[i] == 'd' || source[i] == 'D' ||
                                   source[i] == 'l' || source[i] == 'L')) {

        if (source[i] == '.' || source[i] == 'e' || source[i] == 'E' ||
            source[i] == 'f' || source[i] == 'F' || source[i] == 'd' || source[i] == 'D') {
            isFloat = true;
        }
        i++;
    }

    std::string number = source.substr(start, i - start);
    TokenType type = isHex ? TokenType::HEX_LITERAL :
                     isFloat ? TokenType::FLOAT_LITERAL : TokenType::INTEGER_LITERAL;
    return Token(type, number, line, column);
}

Token JavaLexer::processIdentifierOrKeyword(const std::string& source, size_t& i, int line, int column) {
    size_t start = i;
    while (i < source.length() && (std::isalnum(source[i]) || source[i] == '_' || source[i] == '$')) {
        i++;
    }

    std::string identifier = source.substr(start, i - start);
    TokenType type = TokenType::IDENTIFIER;

    if (keywords.find(identifier) != keywords.end()) {
        type = keywords[identifier];
    }

    return Token(type, identifier, line, column);
}

Token JavaLexer::processOperator(const std::string& source, size_t& i, int line, int column) {
    size_t start = i;

    if (i + 2 < source.length() && operators.find(source.substr(i, 3)) != operators.end()) {
        i += 3;
    } else if (i + 1 < source.length() && operators.find(source.substr(i, 2)) != operators.end()) {
        i += 2;
    } else {
        i++;
    }

    std::string op = source.substr(start, i - start);
    return Token(TokenType::OPERATOR, op, line, column);
}

Token JavaLexer::processSeparator(const std::string& source, size_t& i, int line, int column) {
    char sep = source[i];
    i++;
    return Token(separators[sep], std::string(1, sep), line, column);
}

JavaLexer::JavaLexer() {
    initializeKeywords();
    initializeOperators();
    initializeSeparators();
}

std::vector<Token> JavaLexer::tokenize(const std::string& source) {
    std::vector<Token> tokens;
    int line = 1;
    int column = 1;
    size_t i = 0;

    while (i < source.length()) {
        skipWhitespace(source, i, line, column);
        if (i >= source.length()) break;

        char current = source[i];

        if (current == '#' && i == 0) {
            tokens.push_back(processPreprocessor(source, i, line, column));
            continue;
        }

        if (current == '/' && i + 1 < source.length()) {
            if (source[i + 1] == '/') {
                tokens.push_back(processLineComment(source, i, line, column));
                continue;
            }
            if (source[i + 1] == '*') {
                tokens.push_back(processBlockComment(source, i, line, column));
                continue;
            }
        }

        if (current == '"') {
            tokens.push_back(processStringLiteral(source, i, line, column));
            continue;
        }

        if (current == '\'') {
            tokens.push_back(processCharLiteral(source, i, line, column));
            continue;
        }

        if (std::isdigit(current) || (current == '.' && i + 1 < source.length() && std::isdigit(source[i + 1]))) {
            tokens.push_back(processNumber(source, i, line, column));
            continue;
        }

        if (std::isalpha(current) || current == '_' || current == '$') {
            tokens.push_back(processIdentifierOrKeyword(source, i, line, column));
            continue;
        }

        if (isOperatorChar(current)) {
            tokens.push_back(processOperator(source, i, line, column));
            continue;
        }

        if (separators.find(current) != separators.end()) {
            tokens.push_back(processSeparator(source, i, line, column));
            continue;
        }

        tokens.push_back(Token(TokenType::UNRECOGNIZED, std::string(1, current), line, column));
        i++;
        column++;
    }

    return tokens;
}