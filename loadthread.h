#ifndef LOADTHREAD_H
#define LOADTHREAD_H

#include <QDialog>
#include <QtConcurrent>
#include "thread.h"

namespace Ui {
class loadThread;
}

class loadThread : public QDialog
{
    Q_OBJECT

public:
    explicit loadThread(QWidget *parent = nullptr, bool b = 0, QString p = QString(), QDir d = QDir());
    void closeEvent(QCloseEvent *);
    void showEvent(QShowEvent *);
    ~loadThread();

public slots:
    void handleReady();
    void handleError(QString);
    void start();

signals:
    void end_process();
    void on_stop();

private slots:
    void on_cancel_clicked();

private:
    Ui::loadThread *ui;
    bool complete;
    bool flag;
    Thread thread;
    QDir filePath;
    QString fileSave;
    QString load;
    QString prefix;
};

#endif // LOADTHREAD_H
