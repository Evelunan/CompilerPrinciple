#include "token.h"
#include <unordered_map>

Token::Token(TokenType type, const QString& value, int line)
    : type(type), value(value), line(line) {}

QString getTokenTypeString(TokenType type) {
    static const std::unordered_map<TokenType, QString> tokenTypeStrings = {
        {TokenType::PLUS, "PLUS"}, {TokenType::MINUS, "MINUS"}, {TokenType::MULTIPLY, "MULTIPLY"},
        {TokenType::DIVIDE, "DIVIDE"}, {TokenType::EQUAL, "EQUAL"}, {TokenType::NOT_EQUAL, "NOT_EQUAL"},
        {TokenType::LESS, "LESS"}, {TokenType::GREATER, "GREATER"}, {TokenType::ASSIGNMENT, "ASSIGNMENT"},
        {TokenType::LEFT_PAREN, "LEFT_PAREN"}, {TokenType::RIGHT_PAREN, "RIGHT_PAREN"},
        {TokenType::SEMICOLON, "SEMICOLON"}, {TokenType::LEFT_BRACE, "LEFT_BRACE"},
        {TokenType::RIGHT_BRACE, "RIGHT_BRACE"}, {TokenType::COMMA, "COMMA"},
        {TokenType::DOT, "DOT"}, {TokenType::COLON, "COLON"},
        {TokenType::NUMBER, "NUMBER"}, {TokenType::IDENTIFIER, "IDENTIFIER"},
        {TokenType::AUTO, "AUTO"}, {TokenType::BREAK, "BREAK"}, {TokenType::CASE, "CASE"},
        {TokenType::CHAR, "CHAR"}, {TokenType::CONST, "CONST"}, {TokenType::CONTINUE, "CONTINUE"},
        {TokenType::DEFAULT, "DEFAULT"}, {TokenType::DO, "DO"}, {TokenType::DOUBLE, "DOUBLE"},
        {TokenType::ELSE, "ELSE"}, {TokenType::ENUM, "ENUM"}, {TokenType::EXTERN, "EXTERN"},
        {TokenType::FLOAT, "FLOAT"}, {TokenType::FOR, "FOR"}, {TokenType::GOTO, "GOTO"},
        {TokenType::IF, "IF"}, {TokenType::INLINE, "INLINE"}, {TokenType::INT, "INT"},
        {TokenType::LONG, "LONG"}, {TokenType::REGISTER, "REGISTER"}, {TokenType::RESTRICT, "RESTRICT"},
        {TokenType::RETURN, "RETURN"}, {TokenType::SHORT, "SHORT"}, {TokenType::SIGNED, "SIGNED"},
        {TokenType::SIZEOF, "SIZEOF"}, {TokenType::STATIC, "STATIC"}, {TokenType::STRUCT, "STRUCT"},
        {TokenType::SWITCH, "SWITCH"}, {TokenType::TYPEDEF, "TYPEDEF"}, {TokenType::UNION, "UNION"},
        {TokenType::UNSIGNED, "UNSIGNED"}, {TokenType::VOID, "VOID"}, {TokenType::VOLATILE, "VOLATILE"},
        {TokenType::WHILE, "WHILE"}, {TokenType::_BOOL, "_Bool"}, {TokenType::_COMPLEX, "_Complex"},
        {TokenType::_IMAGINARY, "_Imaginary"}, {TokenType::EOF_TOKEN, "EOF_TOKEN"}
    };
    auto it = tokenTypeStrings.find(type);
    if (it != tokenTypeStrings.end()) {
        return it->second;
    }
    return "UNKNOWN";
}