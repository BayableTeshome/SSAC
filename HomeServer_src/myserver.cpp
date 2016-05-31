#include "myserver.h"

MyServer::MyServer(QObject *parent) :
    QTcpServer(parent)
{

}
void MyServer::StartServer()
{

     QHostAddress hostadd("192.168.0.50");
    if(!this->listen(hostadd,8004))
    {
        qDebug() <<"Could not start server";
    }
    else
    {

        qDebug() <<"Listening...";

     }

}
void MyServer::incomingConnection(int socketDescriptor)
{

 qDebug() <<socketDescriptor << "Connecting...";
 MyThread *thread= new MyThread(socketDescriptor,this);
 connect(thread, SIGNAL(finished()),thread,SLOT(deleteLater()));
 thread->start();

}

