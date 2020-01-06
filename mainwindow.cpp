#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDateTime>
#include <QDebug>
#include <QFileDialog>
#include <QFileInfoList>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    path = QFileDialog::getExistingDirectory(this, "Seleccionar Directorio", "",
                     QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(path.isEmpty())
        return;
    ui->ruta->setText(path);
}

void MainWindow::on_pushButton_2_clicked()
{
    QString prefix = ui->prefijo->text();

    if(prefix.isEmpty())
        return;

    QDir dir(path);

    loadThread *t = new loadThread(this, false, prefix, dir);
    connect(t, &loadThread::end_process, this, &MainWindow::endp);
    t->show();
}

void MainWindow::endp()
{
    QMessageBox::information(this, "Encrypter", "El proceso de excaneo ha finalizado");
}


void MainWindow::on_pushButton_3_clicked()
{
    QString load = QFileDialog::getOpenFileName(nullptr, "Load File", "",
                               tr("Encrypter (*.qfs) ;; Text File (*.txt) ;; All Files (*.*)"));
    QFile file(load);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
        return;

    loadThread *t = new loadThread(this, true, load);
    connect(t, &loadThread::end_process, this, &MainWindow::endp);
    t->show();
}
