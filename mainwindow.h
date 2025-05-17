#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtConcurrent/QtConcurrentRun>
#include <QFutureWatcher>
#include "token.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_codeTextEdit_textChanged();
    void onTokensReady();

private:
    Ui::MainWindow *ui;
    QFutureWatcher<QVector<Token>> *futureWatcher;

};
#endif // MAINWINDOW_H
