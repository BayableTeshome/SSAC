#include "mythread.h"
#include "mainwindow.h"
#include "displayThread.h"
#include "startStream.h"
#include "globalVariables.h"

MyThread::MyThread(QObject *parent):
    QThread(parent)
{

}

MyThread::MyThread(int ID, QObject *parent):
    QThread(parent)
{
    this->socketDescriptor= ID;


}



void MyThread::run()
{

    qDebug()<<socketDescriptor << "Starting thread";
    socket =new QTcpSocket();
    // for Ptz camera controling
    display = new displayThread(this);
    manager = new QNetworkAccessManager();
    manager->get(QNetworkRequest(QUrl("http://root:mmnet@192.168.0.90")));
    play  =new startStream(this);


    if(!socket->setSocketDescriptor(this->socketDescriptor))
    {
        emit error(socket->error());
        return;

    }
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()),Qt::DirectConnection);
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()),Qt::DirectConnection);

    exec();
}

void MyThread::readyRead()
{
        QString mesage ="Intruder";
        if(isDetected==true)
        {

           QByteArray array (mesage.toStdString().c_str());
           socket->write(array);

        }

    QByteArray Data =socket->readAll();

  qDebug() << socketDescriptor <<" Data in:"<<Data;

    QString myString(Data);

    qDebug()<<myString;

    if(myString=="Left")
    {
        manager->get(QNetworkRequest(QUrl("http://192.168.0.90/axis-cgi/com/ptz.cgi?camera=1&move=left")));
       // socket->write(array);

    }
    else if(myString=="Right")
    {

        manager->get(QNetworkRequest(QUrl("http://192.168.0.90/axis-cgi/com/ptz.cgi?camera=1&move=right")));

    }
    else if(myString=="Up")
    {
        manager->get(QNetworkRequest(QUrl("http://192.168.0.90/axis-cgi/com/ptz.cgi?camera=1&move=up")));

    }
    else if(myString=="Down")
    {
        manager->get(QNetworkRequest(QUrl("http://192.168.0.90/axis-cgi/com/ptz.cgi?camera=1&move=down")));

    }
    else if(myString=="plus")
    {

        manager->get(QNetworkRequest(QUrl("http://192.168.0.90/axis-cgi/com/ptz.cgi?camera=1&rzoom=+500")));

    }
    else if(myString=="minus")
    {
        manager->get(QNetworkRequest(QUrl("http://192.168.0.90/axis-cgi/com/ptz.cgi?camera=1&rzoom=-500")));

    }
    else if(myString=="track")
    {

          Tracker=true;

    }
    else if(myString=="stopTrack")
    {

          Tracker=false;

    }
    else if(myString=="alarm")
    {

           Alarm=true;

    }
    else if(myString=="stopAlarm")
    {

           Alarm=false;

    }
    else if(myString=="TCP")
    {

       tcpStream=true;
       play->stream();
    }
    else if(myString=="HLS")
    {


       httpStream=true;
       play->stream();

    }
    else if( myString=="RTSP")
    {
        RtspStream=true;
        play->stream();
    }
    else if(myString=="streamOff")
    {
        tcpStream=false;
        httpStream=false;
        RtspStream=false;
        play->stream();
    }

    else if(myString=="record")
    {

           Record=true;

    }
    else if(myString=="stopRecord")
    {

           Record=false;

    }

}
void MyThread::disconnected()
{
    qDebug() << socketDescriptor <<"Disconnected";
    socket->deleteLater();
    exit(0);


}


