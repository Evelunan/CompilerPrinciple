#include <QCoreApplication>
#include <QString>
#include <QVector>
#include <QDebug>
#include "scanner.h"
#include "token.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // 测试源代码字符串
    QString source = R"(
        int main() {
            int a = 5;
            int b = 0;
            if (a > 5) {
                b = a * 2;
            } else {
                b = 3;
            }

            while (b > 0) {
                b = b - 1;
            }

            return 0;
        }
    )";

    // 创建 Scanner 实例并扫描 Tokens
    Scanner scanner(source);
    QVector<Token> tokens = scanner.scanTokens();

    // 打印所有 Tokens
    foreach (const Token &token, tokens)
    {
        qDebug() << "[Line" << token.line << "] Type:" << getTokenTypeString(token.type)
                 << ", Value:" << token.value;
    }

    return a.exec();
}