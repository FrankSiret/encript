#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDir>
#include <QMainWindow>
#include <QTextStream>
#include "loadthread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void preorden(QDir);
    void print(QString a, QString b);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void endp();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    QString path;
    QFile *file;
    QTextStream *out;
};

#endif // MAINWINDOW_H
