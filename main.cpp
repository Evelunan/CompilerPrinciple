#include <QApplication>  // 注意这里要包含 QApplication 的头文件

#include "scanner.h"
#include "parser.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);  // 修改为 QApplication
    MainWindow win;
    win.show();

    return app.exec();
}
