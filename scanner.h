#ifndef SCANNER_H
#define SCANNER_H

#include <QString>
#include <QVector>
#include "token.h"

/**
 * @class Scanner
 * @brief 用于将输入的源代码扫描为 Token 流。
 *
 * Scanner 类负责对输入的源代码进行逐字符解析，识别出关键字、标识符、数字、运算符等，
 * 并将其转换为对应的 Token 对象集合，供后续的语法分析使用。
 */
class Scanner {
public:
    /**
     * @brief 构造函数，初始化 Scanner。
     * @param source 输入的源代码字符串。
     */
    Scanner(const QString& source);

    /**
     * @brief 执行扫描操作，将源代码转换为 Token 列表。
     * @return 包含所有 Token 的 QVector。
     */
    QVector<Token> scanTokens();

private:
    /**
     * @brief 检查是否到达源代码末尾。
     * @return 如果当前指针位置超出源码长度则返回 true。
     */
    bool isAtEnd() const;

    /**
     * @brief 获取当前字符，并将指针前移一位。
     * @return 当前字符。
     */
    QChar advance();

    /**
     * @brief 将当前扫描的字符序列添加为指定类型的 Token。
     * @param type 要添加的 Token 类型。
     */
    void addToken(TokenType type);

    /**
     * @brief 查看当前字符（不移动指针）。
     * @return 当前字符。
     */
    QChar peek() const;

    /**
     * @brief 查看下一个字符（不移动指针）。
     * @return 下一个字符。
     */
    QChar peekNext() const;

    /**
     * @brief 如果下一个字符匹配预期值，则消费该字符。
     * @param expected 预期的字符。
     * @return 是否匹配成功。
     */
    bool match(QChar expected);
    
    /**
     * @brief 根据当前字符扫描出一个 Token。
     */
    void scanToken();

    /**
     * @brief 处理标识符（变量名、关键字等）的扫描。
     */
    void identifier();

    /**
     * @brief 处理数字字面量的扫描。
     */
    void number();

    /**
     * @brief 尝试识别并处理注释（单行或多行）
     * @return 如果识别到注释则返回 true，否则返回 false。
     */
    bool tryConsumeComment();

    const QString source;  ///< 原始源代码字符串。
    int start;             ///< 当前 Token 开始位置索引。
    int current;           ///< 当前扫描位置索引。
    int line;              ///< 当前所在的行号，用于错误报告。
    QVector<Token> tokens; ///< 存储扫描结果 Token 列表。
};

#endif // SCANNER_H