#include <QtConcurrent/QtConcurrentRun>
#include <QFutureWatcher>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scanner.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    futureWatcher = new QFutureWatcher<QVector<Token>>(this);


    ui->splitter->setStretchFactor(0,70);
    ui->splitter->setStretchFactor(1,40);

    ui->codeTextEdit->setLineWrapMode(QTextEdit::NoWrap);
    ui->codeTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

       // 初始化表格
    ui->scannerTableWidget->setColumnCount(4);
    QStringList headers = {"Type (Int)", "Type (Name)", "Value", "Line"};
    ui->scannerTableWidget->setHorizontalHeaderLabels(headers);

    // 设置所有列自动拉伸
    for(int col = 0; col < ui->scannerTableWidget->columnCount(); ++col){
        ui->scannerTableWidget->horizontalHeader()->setSectionResizeMode(col, QHeaderView::Stretch);
    }


     connect(futureWatcher, &QFutureWatcher<QVector<Token>>::finished, this, &MainWindow::onTokensReady);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_codeTextEdit_textChanged()
{
    QString text = ui->codeTextEdit->toPlainText();
    // 开始异步扫描
    QFuture<QVector<Token>> future = QtConcurrent::run([text]() {
        Scanner scanner(text);
        return scanner.scanTokens();
    });

    // 使用 QFutureWatcher 监听 future 的完成状态
    futureWatcher->setFuture(future);

//    ui->pa
}
void MainWindow::onTokensReady()
{
    auto tokens = futureWatcher->result();

    // 清空表格
    ui->scannerTableWidget->clearContents();
    ui->scannerTableWidget->setRowCount(0);

    // 设置行数
    ui->scannerTableWidget->setRowCount(tokens.size());

    for (int i = 0; i < tokens.size(); ++i) {
        const Token &token = tokens[i];

        // 插入枚举整数值（第0列）
        QTableWidgetItem *typeItem = new QTableWidgetItem(QString::number(static_cast<int>(token.type)));
        typeItem->setTextAlignment(Qt::AlignCenter); // 设置文本居中
        ui->scannerTableWidget->setItem(i, 0, typeItem);

        // 插入类型字符串（第1列）
        QTableWidgetItem *typeNameItem = new QTableWidgetItem(getTokenTypeString(token.type));
        typeNameItem->setTextAlignment(Qt::AlignCenter); // 设置文本居中
        ui->scannerTableWidget->setItem(i, 1, typeNameItem);

        // 插入值（第2列）
        QTableWidgetItem *valueItem = new QTableWidgetItem(token.value);
        valueItem->setTextAlignment(Qt::AlignCenter); // 设置文本居中
        ui->scannerTableWidget->setItem(i, 2, valueItem);

        // 插入行号（第3列）
        QTableWidgetItem *lineItem = new QTableWidgetItem(QString::number(token.line));
        lineItem->setTextAlignment(Qt::AlignCenter); // 设置文本居中
        ui->scannerTableWidget->setItem(i, 3, lineItem);
    }
}
