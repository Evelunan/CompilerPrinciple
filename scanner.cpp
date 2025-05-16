#include "scanner.h"
#include <QDebug>
#include <cctype>


Scanner::Scanner(const QString& source)
    : source(source), start(0), current(0), line(1) {}

QVector<Token> Scanner::scanTokens() {
    while (!isAtEnd()) {
        start = current;
        scanToken();
    }
    tokens.append(Token(TokenType::EOF_TOKEN, "", line));
    return tokens;
}

bool Scanner::isAtEnd() const {
    return current >= source.size();
}

QChar Scanner::advance() {
    return source[current++];
}

void Scanner::addToken(TokenType type) {
    QString text = source.mid(start, current - start);
    tokens.append(Token(type, text, line));
}

QChar Scanner::peek() const {
    if (isAtEnd()) return QChar();
    return source[current];
}

QChar Scanner::peekNext() const {
    if (current + 1 >= source.size()) return QChar();
    return source[current + 1];
}

bool Scanner::match(QChar expected) {
    if (isAtEnd()) return false;
    if (source[current] != expected) return false;
    current++;
    return true;
}

void Scanner::scanToken() {
    QChar c = advance();

    switch (c.toLatin1()) { // 转换为ASCII值进行比较
        case '(': addToken(TokenType::LEFT_PAREN); break;
        case ')': addToken(TokenType::RIGHT_PAREN); break;
        case '{': addToken(TokenType::LEFT_BRACE); break;
        case '}': addToken(TokenType::RIGHT_BRACE); break;
        case ',': addToken(TokenType::COMMA); break;
        case '.': addToken(TokenType::DOT); break;
        case ':': addToken(TokenType::COLON); break;
        case '+': addToken(TokenType::PLUS); break;
        case '-': addToken(TokenType::MINUS); break;
        case '*': addToken(TokenType::MULTIPLY); break;

        case '/':
            // 不是注释，视为除号
            if (!tryConsumeComment())
                addToken(TokenType::DIVIDE);
            break;

        case '<':
            if (match('=')) addToken(TokenType::LESS_EQUAL);
            else addToken(TokenType::LESS);
            break;
        case '>':
            if (match('=')) addToken(TokenType::GREATER_EQUAL);
            else addToken(TokenType::GREATER);
            break;
        case '=':
            if (match('=')) addToken(TokenType::EQUAL);
            else addToken(TokenType::ASSIGNMENT);
            break;
        case '!':
            if (match('=')) addToken(TokenType::NOT_EQUAL);
            else addToken(TokenType::BANG);
            break;
        case ';': addToken(TokenType::SEMICOLON); break;
        case ' ': case '\r': case '\t': break; // 忽略空白字符
        case '\n': line++; break;

        default:
            if (c.isDigit()) {
                number();
            } else if (c.isLetter() || c == '_') {
                identifier();
            } else {
                qWarning() << "Unexpected character '" << c << "' at line" << line;
            }
            break;
    }
}

void Scanner::identifier() {
    while (peek().isLetterOrNumber() || peek() == '_') advance();

    QString text = source.mid(start, current - start);

    static const QMap<QString, TokenType> keywords = {
        {"auto", TokenType::AUTO},
        {"break", TokenType::BREAK},
        {"case", TokenType::CASE},
        {"char", TokenType::CHAR},
        {"const", TokenType::CONST},
        {"continue", TokenType::CONTINUE},
        {"default", TokenType::DEFAULT},
        {"do", TokenType::DO},
        {"double", TokenType::DOUBLE},
        {"else", TokenType::ELSE},
        {"enum", TokenType::ENUM},
        {"extern", TokenType::EXTERN},
        {"float", TokenType::FLOAT},
        {"for", TokenType::FOR},
        {"goto", TokenType::GOTO},
        {"if", TokenType::IF},
        {"inline", TokenType::INLINE},
        {"int", TokenType::INT},
        {"long", TokenType::LONG},
        {"register", TokenType::REGISTER},
        {"restrict", TokenType::RESTRICT},
        {"return", TokenType::RETURN},
        {"short", TokenType::SHORT},
        {"signed", TokenType::SIGNED},
        {"sizeof", TokenType::SIZEOF},
        {"static", TokenType::STATIC},
        {"struct", TokenType::STRUCT},
        {"switch", TokenType::SWITCH},
        {"typedef", TokenType::TYPEDEF},
        {"union", TokenType::UNION},
        {"unsigned", TokenType::UNSIGNED},
        {"void", TokenType::VOID},
        {"volatile", TokenType::VOLATILE},
        {"while", TokenType::WHILE},
        {"_Bool", TokenType::_BOOL},
        {"_Complex", TokenType::_COMPLEX},
        {"_Imaginary", TokenType::_IMAGINARY}
    };

    auto it = keywords.find(text);
    if (it != keywords.end()) {
        addToken(it.value());
    } else {
        addToken(TokenType::IDENTIFIER);
    }
}

void Scanner::number() {
    while (peek().isDigit()) advance();
    addToken(TokenType::NUMBER);
}

bool Scanner::tryConsumeComment() {
    if (peek() == '/') {
        // 单行注释: 跳过直到换行
        while (peek() != '\n' && !isAtEnd()) advance();
        addToken(TokenType::SINGLE_LINE_COMMENT);
        return true;
    }
    if (peek() == '*') {
        // 多行注释: 跳过直到 '*/'
        advance(); advance(); // 跳过 '/*'

        bool closed = false;
        while (!isAtEnd()) {
            QChar c = advance();
            if (c == '*' && peek() == '/') {
                advance(); // 跳过 '/'
                closed = true;
                break;
            }
            if (c == '\n') line++; // 更新行号
        }

        if (!closed) {
            qWarning() << "Unterminated multi-line comment at line" << line;
        } else {
            addToken(TokenType::MULTI_LINE_COMMENT);
        }
        return true;
    }

    return false; // 没有识别到注释
}
