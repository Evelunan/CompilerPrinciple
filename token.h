#ifndef TOKEN_H
#define TOKEN_H

#include <QString>
#include <QVector>

/**
 * @enum TokenType
 * @brief 枚举定义了所有可能的Token类型，包括运算符、分隔符、字面量和关键字。
 */
enum class TokenType {
    // 运算符
    PLUS, MINUS, MULTIPLY, DIVIDE,
    EQUAL, NOT_EQUAL,
    LESS, GREATER,
    LESS_EQUAL,     ///< 表示 <= 小于等于
    GREATER_EQUAL,  ///< 表示 >= 大于等于
    ASSIGNMENT,
    BANG,           ///< 表示 ! 逻辑非

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

    // 注释
    SINGLE_LINE_COMMENT, ///< 表示单行注释，如 // 这是注释
    MULTI_LINE_COMMENT,  ///< 表示多行注释，如 /* 这是多行注释 */
    
    EOF_TOKEN
};
/**
 * @struct Token
 * @brief 表示源代码中的一个Token，包含其类型、值以及所在行号。
 */
struct Token {
    TokenType type; ///< Token的类型。
    QString value;  ///< Token的字符串值，对于标识符或数字字面量等有意义。
    int line;       ///< Token在源文件中出现的行号。

    /**
     * @brief 默认构造函数。
     */
    Token() = default;

    /**
     * @brief 参数化构造函数，用于初始化Token对象。
     * @param type Token的类型。
     * @param value Token的字符串值。
     * @param line Token在源文件中的行号。
     */
    Token(TokenType type, const QString& value, int line);
};

/**
 * @brief 根据给定的TokenType返回对应的字符串表示形式。
 * @param type 需要查询的TokenType。
 * @return 返回对应类型的字符串表示形式，如果类型未知，则返回"UNKNOWN"。
 */
QString getTokenTypeString(TokenType type);

/**
 * @brief 打印Token的详细信息，包括类型、值和行号。
 * @param token 需要打印的Token对象。
 */
void printToken(const Token& token);

/**
 * @brief 打印Token列表的详细信息，包括每个Token的类型、值和行号。
 * @param tokens 需要打印的Token列表。
 */
void printTokens(const QVector<Token>& tokens);
#endif // TOKEN_H