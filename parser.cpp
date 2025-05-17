#include "parser.h"
#include <QDebug>

Parser::Parser(const QVector<Token>& tokens)
    : tokens(tokens), current(0), hadError(false) {}

// 入口，解析程序
bool Parser::parse() {
    bool result = program();
    if (result) {
        qDebug() << "语法分析成功！";
    }
    return result;
}

bool Parser::program() {
    while (!isAtEnd()) {
        if (!declaration()) {
            synchronize();
        }
    }
    return !hadError;
}

// program -> declaration* EOF
// declaration -> varDecl | statement
// 声明 -> 变量声明 | 函数声明 | 语句
bool Parser::declaration() {
    if (match(TokenType::INT) || match(TokenType::FLOAT) || match(TokenType::CHAR)) {
        if (!match(TokenType::IDENTIFIER)) {
            error(previous(), "变量或函数声明缺少标识符");
            return false;
        }
        if (match(TokenType::LEFT_PAREN)) {
            // 解析函数参数列表（简单示例，支持空参数）
            if (!match(TokenType::RIGHT_PAREN)) {
                error(peek(), "函数参数列表解析未实现");
                return false;
            }
            if (!statement()) {
                error(peek(), "函数体解析失败");
                return false;
            }
            return true;
        } else {
            // 变量声明支持初始化
            if (match(TokenType::ASSIGNMENT)) {
                if (!expression()) {
                    error(peek(), "变量初始化表达式无效");
                    return false;
                }
            }
            if (!match(TokenType::SEMICOLON)) {
                error(previous(), "变量声明缺少分号");
                return false;
            }
            return true;
        }
    }
    return statement();
}



// statement -> expressionStatement | block
bool Parser::statement() {
    // 块语句
    if (match(TokenType::LEFT_BRACE)) {
        while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
            if (!declaration()) return false;
        }
        if (!match(TokenType::RIGHT_BRACE)) {
            error(peek(), "缺少右花括号");
            return false;
        }
        return true;
    }

    // if语句
    if (match(TokenType::IF)) {
        if (!match(TokenType::LEFT_PAREN)) {
            error(peek(), "if语句缺少左括号");
            return false;
        }
        if (!expression()) return false;  // 条件表达式
        if (!match(TokenType::RIGHT_PAREN)) {
            error(peek(), "if语句缺少右括号");
            return false;
        }
        if (!statement()) return false;   // if语句体
        // 可选else分支
        if (match(TokenType::ELSE)) {
            if (!statement()) return false;
        }
        return true;
    }

    // return语句
    if (match(TokenType::RETURN)) {
        // return后可跟表达式，也可以直接分号
        if (!check(TokenType::SEMICOLON)) {
            if (!expression()) return false;
        }
        if (!match(TokenType::SEMICOLON)) {
            error(previous(), "return语句缺少分号");
            return false;
        }
        return true;
    }

    // 其他情况当作表达式语句处理
    return expressionStatement();
}



// expressionStatement -> expression ';'
bool Parser::expressionStatement() {
    if (!expression()) return false;
    if (!match(TokenType::SEMICOLON)) {
        error(previous(), "缺少语句结束的分号");
        return false;
    }
    return true;
}

// expression -> assignment
bool Parser::expression() {
    return assignment();
}

// assignment -> IDENTIFIER '=' assignment | equality
bool Parser::assignment() {
    if (match(TokenType::IDENTIFIER)) {
        if (match(TokenType::ASSIGNMENT)) {
            if (!assignment()) {
                error(peek(), "赋值表达式右侧无效");
                return false;
            }
            return true;
        } else {
            // 回退，当前Token不是赋值符号，回到IDENTIFIER
            current--;
        }
    }
    return equality();
}

// equality -> comparison ( ( '==' | '!=' ) comparison )*
bool Parser::equality() {
    if (!comparison()) return false;
    while (match(TokenType::EQUAL) || match(TokenType::NOT_EQUAL)) {
        if (!comparison()) return false;
    }
    return true;
}

// comparison -> term ( ('<' | '<=' | '>' | '>=') term )*
bool Parser::comparison() {
    if (!term()) return false;
    while (match(TokenType::LESS) || match(TokenType::LESS_EQUAL) ||
           match(TokenType::GREATER) || match(TokenType::GREATER_EQUAL)) {
        if (!term()) return false;
    }
    return true;
}

// term -> factor ( ('+' | '-') factor )*
bool Parser::term() {
    if (!factor()) return false;
    while (match(TokenType::PLUS) || match(TokenType::MINUS)) {
        if (!factor()) return false;
    }
    return true;
}

// factor -> unary ( ('*' | '/') unary )*
bool Parser::factor() {
    if (!unary()) return false;
    while (match(TokenType::MULTIPLY) || match(TokenType::DIVIDE)) {
        if (!unary()) return false;
    }
    return true;
}

// unary -> ( '!' | '-' ) unary | primary
bool Parser::unary() {
    if (match(TokenType::BANG) || match(TokenType::MINUS)) {
        return unary();
    }
    return primary();
}

// primary -> NUMBER | IDENTIFIER | '(' expression ')'
bool Parser::primary() {
    if (match(TokenType::NUMBER) || match(TokenType::IDENTIFIER)) {
        return true;
    }
    if (match(TokenType::LEFT_PAREN)) {
        if (!expression()) return false;
        if (!match(TokenType::RIGHT_PAREN)) {
            error(peek(), "缺少右括号");
            return false;
        }
        return true;
    }
    error(peek(), "预期数字、标识符或括号表达式");
    return false;
}

// 工具函数实现

bool Parser::match(TokenType type) {
    if (check(type)) {
        advance();
        return true;
    }
    return false;
}

bool Parser::check(TokenType type) const {
    if (isAtEnd()) return false;
    return peek().type == type;
}

const Token& Parser::advance() {
    if (!isAtEnd()) current++;
    return previous();
}

bool Parser::isAtEnd() const {
    return peek().type == TokenType::EOF_TOKEN;
}

const Token& Parser::peek() const {
    return tokens[current];
}

const Token& Parser::previous() const {
    return tokens[current - 1];
}

void Parser::error(const Token& token, const QString& message) {
    hadError = true;
    QString errorMsg = QString("语法错误 [行 %1]: %2 (Token: %3)")
                       .arg(token.line)
                       .arg(message)
                       .arg(token.value.isEmpty() ? getTokenTypeString(token.type) : token.value);
    qWarning() << errorMsg;
}

void Parser::synchronize() {
    advance();

    while (!isAtEnd()) {
        if (previous().type == TokenType::SEMICOLON) return;

        switch (peek().type) {
            case TokenType::INT:
            case TokenType::FLOAT:
            case TokenType::CHAR:
            case TokenType::IF:
            case TokenType::WHILE:
            case TokenType::FOR:
            case TokenType::RETURN:
                return;
            default:
                break;
        }
        advance();
    }
}
