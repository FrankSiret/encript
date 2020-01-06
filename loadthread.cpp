#include "loadthread.h"
#include "ui_loadthread.h"

#include <QMessageBox>

loadThread::loadThread(QWidget *parent, bool b, QString p, QDir d) :
    QDialog(parent), ui(new Ui::loadThread)
{
    ui->setupUi(this);

    flag = b;
    if(b) {
        load = p;
    }
    else {
        filePath = d;
        prefix = p;
    }
}

void loadThread::closeEvent(QCloseEvent *)
{
    if(complete) {
        emit on_stop();
        emit end_process();
    }
    else {
        emit on_stop();
    }
}

void loadThread::showEvent(QShowEvent *)
{
    ui->l_staus->setText("Inicializando...");
    ui->pb_main->setMinimum(0);
    ui->pb_main->setMaximum(0);
    start();
}

loadThread::~loadThread()
{
    delete ui;
}

void loadThread::handleReady()
{
    complete = true;
    close();
}

void loadThread::handleError(QString error)
{
    QMessageBox::critical(this, "¡Error fatal!", error);
    close();
}

void loadThread::start()
{
    ui->l_staus->setText("Esto puede demorar algunos minutos, espere por favor...");
    connect(this, &loadThread::on_stop, &thread, &Thread::stop);
    connect(&thread, &Thread::finnish, this, &loadThread::close);
    if( flag )
        QFuture<void> procesar = QtConcurrent::run(&thread, &Thread::reverse, load);
    else
        QFuture<void> procesar = QtConcurrent::run(&thread, &Thread::start, filePath, prefix);
}

void loadThread::on_cancel_clicked()
{
    close();
}
