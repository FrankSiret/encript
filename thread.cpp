#include "thread.h"

#include <QDir>
#include <QFileDialog>

Thread::Thread(QObject *parent) : QObject(parent)
{
    mStop = false;
}

void Thread::start(QDir dir, QString p)
{
    mStop = false;
    prefix = p;
    index = 0;

    preorder(dir);

    fileSave = QFileDialog::getSaveFileName(nullptr, "Save File", "",
                               tr("Encripter (*.qfs) ;; Text File (*.txt) ;; All Files (*.*)"));
    QFile file(fileSave);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
        return;
    file.resize(0);

    QTextStream out(&file);

    foreach (par id, renList) {
        QString a = id.first;
        QString b = id.second;
        out << "\"" + a + "\" \"" + b + "\"\n";
    }

    stop();
}

void Thread::reverse(QString l)
{
    mStop = false;

    QFile file(l);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
        return;

    QTextStream in(&file);

    //QString asd = in.read(100);
    //qDebug() << asd;

    QStringList line = in.readLine(1000).split("\"", QString::KeepEmptyParts);
    QString a = line[1];
    QString b = line[3];
    //qDebug() << "mp" << a << b;
    mp[b] = a;
    QDir dir(b);
    while (!in.atEnd()) {
        line = in.readLine(1000).split("\"", QString::KeepEmptyParts);
        a = line[1];
        b = line[3];
        //qDebug() << "mp" << a << b;
        mp[b] = a;
    }
    postorder(dir);
    stop();
}

void Thread::stop()
{
    mStop = true;
    emit finnish();
}

QDir Thread::renameFile(QString a, QString b)
{
    QString tb = a.section("/",0,-2) + "/" + b + QString("_%1").arg(++index, 6, 10, QLatin1Char('0'));
    QFile::rename(a, tb);
    renList << par(a, tb);
    return QDir(tb);
}

void Thread::reverseRenFile(QString a)
{
    //qDebug() << a << mp[a];
    QFile::rename(a, mp[a]);
}

void Thread::preorder(QDir d)
{
    QDir td = renameFile(d.absolutePath(), prefix);
    QFileInfoList listDir = td.entryInfoList(QDir::NoDotAndDotDot | QDir::Dirs |
                               QDir::Files | QDir::NoSymLinks | QDir::Readable);
    foreach (QFileInfo i, listDir) {
        if(i.isFile())
            renameFile(i.absoluteFilePath(), "_"+prefix);
    }
    foreach (QFileInfo i, listDir) {
        if(i.isDir())
            preorder(QDir(i.absoluteFilePath()));
    }
}

void Thread::postorder(QDir d)
{
    QFileInfoList listDir = d.entryInfoList(QDir::NoDotAndDotDot | QDir::Dirs |
                               QDir::Files | QDir::NoSymLinks | QDir::Readable);
    foreach (QFileInfo i, listDir) {
        if(i.isFile())
            reverseRenFile(i.absoluteFilePath());
    }
    foreach (QFileInfo i, listDir) {
        if(i.isDir())
            postorder(QDir(i.absoluteFilePath()));
    }
    reverseRenFile(d.absolutePath());
}

void Thread::print(QString a, QString b)
{
    qDebug() << a << b;
    out->operator <<("\"" + a + "\" \"" + b + "\"\n");
}
