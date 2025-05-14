#ifndef SCANNER_H
#define SCANNER_H

#include <QString>
#include <QVector>
#include "token.h"

class Scanner {
public:
    Scanner(const QString& source);

    QVector<Token> scanTokens();

private:
    bool isAtEnd() const;
    QChar advance();
    void addToken(TokenType type);

    QChar peek() const;
    QChar peekNext() const;
    bool match(QChar expected);
    void scanToken();

    void identifier();
    void number();

    const QString source;
    int start, current, line;
    QVector<Token> tokens;
};

#endif // SCANNER_H