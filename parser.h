#ifndef PARSER_H
#define PARSER_H

#include <QVector>
#include <QString>
#include "token.h"

/**
 * @class Parser
 * @brief 递归下降语法分析器，用于对词法分析器生成的Token序列进行语法检查和结构分析。
 *
 * 支持简单C语言子集的语法规则，包括变量声明、表达式语句、块语句等。
 */
class Parser {
public:
    /**
     * @brief 构造函数，初始化语法分析器。
     * @param tokens 词法分析器生成的Token序列。
     */
    Parser(const QVector<Token>& tokens);

    /**
     * @brief 执行语法分析，入口函数。
     * @return 语法分析成功返回true，否则返回false。
     */
    bool parse();

private:
    const QVector<Token>& tokens; ///< 词法分析得到的Token列表
    int current;                  ///< 当前解析到的Token索引

    /**
     * @brief 顶层程序规则，解析整个程序。
     * @return 语法分析成功返回true，否则false。
     */
    bool program();

    /**
     * @brief 声明规则，支持变量声明和语句。
     * @return 解析成功返回true，否则false。
     */
    bool declaration();

    /**
     * @brief 语句规则，包括块语句和表达式语句。
     * @return 解析成功返回true，否则false。
     */
    bool statement();

    /**
     * @brief 表达式语句规则，表达式后跟分号。
     * @return 解析成功返回true，否则false。
     */
    bool expressionStatement();

    /**
     * @brief 表达式规则，入口为赋值表达式。
     * @return 解析成功返回true，否则false。
     */
    bool expression();

    /**
     * @brief 赋值表达式规则。
     * @return 解析成功返回true，否则false。
     */
    bool assignment();

    /**
     * @brief 相等表达式规则。
     * @return 解析成功返回true，否则false。
     */
    bool equality();

    /**
     * @brief 比较表达式规则。
     * @return 解析成功返回true，否则false。
     */
    bool comparison();

    /**
     * @brief 加减表达式规则。
     * @return 解析成功返回true，否则false。
     */
    bool term();

    /**
     * @brief 乘除表达式规则。
     * @return 解析成功返回true，否则false。
     */
    bool factor();

    /**
     * @brief 一元表达式规则。
     * @return 解析成功返回true，否则false。
     */
    bool unary();

    /**
     * @brief 基本表达式规则，数字、标识符或括号表达式。
     * @return 解析成功返回true，否则false。
     */
    bool primary();

    /**
     * @brief 如果当前Token类型匹配参数type，则消费该Token并返回true，否则返回false。
     * @param type 期望匹配的Token类型。
     * @return 是否匹配成功。
     */
    bool match(TokenType type);

    /**
     * @brief 判断当前Token是否为指定类型type。
     * @param type 期望检查的Token类型。
     * @return 是否匹配。
     */
    bool check(TokenType type) const;

    /**
     * @brief 消费当前Token，返回之前的Token。
     * @return 被消费的Token。
     */
    const Token& advance();

    /**
     * @brief 判断是否已到达Token序列末尾。
     * @return 是否到达末尾。
     */
    bool isAtEnd() const;

    /**
     * @brief 查看当前Token但不消费。
     * @return 当前Token。
     */
    const Token& peek() const;

    /**
     * @brief 查看上一个已消费的Token。
     * @return 上一个Token。
     */
    const Token& previous() const;

    /**
     * @brief 语法错误报告函数，打印错误信息并标记错误状态。
     * @param token 出错的Token。
     * @param message 错误描述信息。
     */
    void error(const Token& token, const QString& message);

    /**
     * @brief 同步错误恢复函数。
     * 遇到语法错误时，跳过无效Token直到找到可能的语句起始Token，避免错误传播。
     */
    void synchronize();

    bool hadError; ///< 标记是否出现语法错误
};

#endif // PARSER_H
