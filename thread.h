#ifndef THREAD_H
#define THREAD_H

#include <QDir>
#include <QMap>
#include <QFile>
#include <QObject>
#include <QTextStream>
#include <QThread>
#include <QDebug>

typedef QPair<QString, QString> par;

class Thread : public QObject
{
    Q_OBJECT
public:
    explicit Thread(QObject *parent = nullptr);
    void start(QDir, QString);
    void reverse(QString);
    void stop();
    QDir renameFile(QString, QString);
    void reverseRenFile(QString);
    void preorder(QDir d);
    void postorder(QDir d);
    void print(QString a, QString b);

signals:
    void finnish();

private:
    QFile *file;
    QString fileSave;
    QString prefix;
    QMap<QString, QString> mp;
    int index;
    QVector<par> renList;
    QTextStream *out;
    bool mStop;
};

#endif // THREAD_H
