#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include <QAbstractSocket>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QUrl>
#include "startStream.h"
#include "displayThread.h"

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(int ID,QObject *parent = 0);
    explicit MyThread(QObject *parent = 0);

    void run();
    void sendlistner();
    QString serverdata;
    int index=1;
signals:
     void error(QTcpSocket::SocketError socketerror);


public slots:
    void readyRead();
    void disconnected();

private:
    QTcpSocket *socket;
    int socketDescriptor;
    QNetworkAccessManager *manager;
    //MainWindow *setParameter;
    startStream *play;
    displayThread *display;
};

#endif // MYTHREAD_H
