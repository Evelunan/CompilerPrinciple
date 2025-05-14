#ifndef TOKEN_H
#define TOKEN_H

#include <QString>
#include <QVector>

enum class TokenType {
    // 运算符
    PLUS, MINUS, MULTIPLY, DIVIDE,
    EQUAL, NOT_EQUAL, LESS, GREATER, ASSIGNMENT,

    // 分隔符
    LEFT_PAREN, RIGHT_PAREN, SEMICOLON, LEFT_BRACE, RIGHT_BRACE,
    COMMA, DOT, COLON,

    // 字面量
    NUMBER, IDENTIFIER,

    // 关键字（完整C99标准）
    AUTO, BREAK, CASE, CHAR, CONST, CONTINUE, DEFAULT, DO, DOUBLE, ELSE,
    ENUM, EXTERN, FLOAT, FOR, GOTO, IF, INLINE, INT, LONG, REGISTER,
    RESTRICT, RETURN, SHORT, SIGNED, SIZEOF, STATIC, STRUCT, SWITCH,
    TYPEDEF, UNION, UNSIGNED, VOID, VOLATILE, WHILE,
    _BOOL, _COMPLEX, _IMAGINARY,

    EOF_TOKEN
};

struct Token {
    TokenType type;
    QString value;
    int line;
    Token() = default;
    Token(TokenType type, const QString& value, int line);
};

QString getTokenTypeString(TokenType type);

#endif // TOKEN_H