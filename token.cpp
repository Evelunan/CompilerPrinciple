#include "token.h"
#include <QDebug>

Token::Token(TokenType type, const QString& value, int line)
    : type(type), value(value), line(line) {}

QString getTokenTypeString(TokenType type) {
    switch (type) {
        // 运算符
        case TokenType::PLUS:             return "PLUS";
        case TokenType::MINUS:            return "MINUS";
        case TokenType::MULTIPLY:         return "MULTIPLY";
        case TokenType::DIVIDE:           return "DIVIDE";
        case TokenType::EQUAL:            return "EQUAL";
        case TokenType::NOT_EQUAL:        return "NOT_EQUAL";
        case TokenType::LESS:             return "LESS";
        case TokenType::GREATER:          return "GREATER";
        case TokenType::LESS_EQUAL:       return "LESS_EQUAL";
        case TokenType::GREATER_EQUAL:    return "GREATER_EQUAL";
        case TokenType::ASSIGNMENT:       return "ASSIGNMENT";
        case TokenType::BANG:             return "BANG";

        // 分隔符
        case TokenType::LEFT_PAREN:       return "LEFT_PAREN";
        case TokenType::RIGHT_PAREN:      return "RIGHT_PAREN";
        case TokenType::SEMICOLON:        return "SEMICOLON";
        case TokenType::LEFT_BRACE:       return "LEFT_BRACE";
        case TokenType::RIGHT_BRACE:      return "RIGHT_BRACE";
        case TokenType::COMMA:            return "COMMA";
        case TokenType::DOT:              return "DOT";
        case TokenType::COLON:            return "COLON";

        // 字面量
        case TokenType::NUMBER:           return "NUMBER";
        case TokenType::IDENTIFIER:       return "IDENTIFIER";

        // 关键字（C99）
        case TokenType::AUTO:             return "AUTO";
        case TokenType::BREAK:            return "BREAK";
        case TokenType::CASE:             return "CASE";
        case TokenType::CHAR:             return "CHAR";
        case TokenType::CONST:            return "CONST";
        case TokenType::CONTINUE:         return "CONTINUE";
        case TokenType::DEFAULT:          return "DEFAULT";
        case TokenType::DO:               return "DO";
        case TokenType::DOUBLE:           return "DOUBLE";
        case TokenType::ELSE:             return "ELSE";
        case TokenType::ENUM:             return "ENUM";
        case TokenType::EXTERN:           return "EXTERN";
        case TokenType::FLOAT:            return "FLOAT";
        case TokenType::FOR:              return "FOR";
        case TokenType::GOTO:             return "GOTO";
        case TokenType::IF:               return "IF";
        case TokenType::INLINE:           return "INLINE";
        case TokenType::INT:              return "INT";
        case TokenType::LONG:             return "LONG";
        case TokenType::REGISTER:         return "REGISTER";
        case TokenType::RESTRICT:         return "RESTRICT";
        case TokenType::RETURN:           return "RETURN";
        case TokenType::SHORT:            return "SHORT";
        case TokenType::SIGNED:           return "SIGNED";
        case TokenType::SIZEOF:           return "SIZEOF";
        case TokenType::STATIC:           return "STATIC";
        case TokenType::STRUCT:           return "STRUCT";
        case TokenType::SWITCH:           return "SWITCH";
        case TokenType::TYPEDEF:          return "TYPEDEF";
        case TokenType::UNION:            return "UNION";
        case TokenType::UNSIGNED:         return "UNSIGNED";
        case TokenType::VOID:             return "VOID";
        case TokenType::VOLATILE:         return "VOLATILE";
        case TokenType::WHILE:            return "WHILE";
        case TokenType::_BOOL:            return "_BOOL";
        case TokenType::_COMPLEX:         return "_COMPLEX";
        case TokenType::_IMAGINARY:       return "_IMAGINARY";
        
        // 注释
        case TokenType::SINGLE_LINE_COMMENT: return "SINGLE_LINE_COMMENT";
        case TokenType::MULTI_LINE_COMMENT:   return "MULTI_LINE_COMMENT";

        case TokenType::EOF_TOKEN:        return "EOF_TOKEN";

        default:                          return "UNKNOWN";
    }
}

void printToken(const Token &token)
{
    QString typeString = getTokenTypeString(token.type);
    QString valueString = token.value.isEmpty() ? "N/A" : token.value;
    qDebug() << "Token Type:" << typeString
             << ", Value:" << valueString
             << ", Line:" << token.line;
}

void printTokens(const QVector<Token> &tokens)
{
    for (const Token &token : tokens) {
        printToken(token);
    }
}
