#include "displayThread.h"

#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QDebug>
#include "mythread.h"

class MyServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyServer(QObject *parent =0);
    void StartServer();

public slots:

protected:
    void incomingConnection(int socketDescriptor);

};

#endif // MYSERVER_H
