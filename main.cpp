#include "scanner.h"
#include "parser.h"
#include <QCoreApplication>
int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QString source = R"(
        int a = 5;
        int b = !a;

        a = a + 1;
        b = b - 1;
    )";
    Scanner scanner(source);
    QVector<Token> tokens = scanner.scanTokens();

    printTokens(tokens);
    
    // Parser parser(tokens);
    // parser.parse();

    return 0;
}
