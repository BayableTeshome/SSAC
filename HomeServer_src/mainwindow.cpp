#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "startStream.h"
#include "mythread.h"
#include <QImage>
#include "myserver.h"
#include "globalVariables.h"
#include "displayThread.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);
    manager->get(QNetworkRequest(QUrl("http://root:mmnet@192.168.0.90")));
    newstream = new startStream(this);
    dispvideo = new displayThread(this);
    connect(dispvideo,SIGNAL(imageupdate(QImage)),this,SLOT(display(QImage)));
    pMOG2 = createBackgroundSubtractorMOG2(500,16,false); //MOG2 approach
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::display(QImage img)
{

ui->label->setPixmap(QPixmap::fromImage(img));

}

void MainWindow::on_pushButton_clicked()
{
    //start the functionality
      camStop=false;
      dispvideo->start();
      newstream->stream();


}

void MainWindow::on_pushButton_2_clicked()
{
    //stop the functionality
     camStop=true;
}

void MainWindow::on_pushButton_3_clicked()
{
    //turn the camer to the left LEFT
     manager->get(QNetworkRequest(QUrl("http://192.168.0.90/axis-cgi/com/ptz.cgi?camera=1&move=left")));


}


void MainWindow::on_pushButton_9_clicked()
{
    // set tracker

     if(Tracker==false)
     {
         Tracker=true;
         ui->pushButton_9->setFlat(true);
     }
     else
     {
          Tracker=false;
         ui->pushButton_9->setFlat(false);
     }

}

void MainWindow::on_pushButton_10_clicked()
{
    //set Record

    if(Record==false)
    {
        Record=true;
        ui->pushButton_10->setFlat(true);
    }
    else
    {
       Record=false;
       ui->pushButton_10->setFlat(false);
    }

}

void MainWindow::on_pushButton_11_clicked()
{

    //set Alarm
    if(Alarm==false)
    {

       Alarm=true;
        ui->pushButton_11->setFlat(true);
    }
    else
    {

       Alarm=false;
       ui->pushButton_11->setFlat(false);
    }

}

void MainWindow::on_pushButton_13_clicked()
{
        tcpStream=true;
        ui->pushButton_13->setFlat(true);
        newstream->stream();
}

void MainWindow::on_pushButton_14_clicked()
{

    if(RtspStream==false)
    {

       RtspStream=true;
        ui->pushButton_14->setFlat(true);
    }
    else
    {

       RtspStream=false;
       ui->pushButton_14->setFlat(false);
    }
    newstream->stream();
}

void MainWindow::on_pushButton_15_clicked()
{

    if(httpStream==false)
    {
        httpStream=true;
        ui->pushButton_15->setFlat(true);
    }
    else
    {

        httpStream=false;
        ui->pushButton_15->setFlat(false);
    }

    newstream->stream();
}


void MainWindow::on_pushButton_12_clicked()
{
    tcpStream=false;
    httpStream=false;
    RtspStream=false;
    newstream->stream();

}

void MainWindow::on_pushButton_4_clicked()
{
    //turn the camer to the right
     manager->get(QNetworkRequest(QUrl("http://192.168.0.90/axis-cgi/com/ptz.cgi?camera=1&move=right")));
}

void MainWindow::on_pushButton_5_clicked()
{
    //turn the camera up
     manager->get(QNetworkRequest(QUrl("http://192.168.0.90/axis-cgi/com/ptz.cgi?camera=1&move=up")));
}

void MainWindow::on_pushButton_6_clicked()
{
    // turn the camera Down
      manager->get(QNetworkRequest(QUrl("http://192.168.0.90/axis-cgi/com/ptz.cgi?camera=1&move=down")));
}

void MainWindow::on_pushButton_7_clicked()
{
    // zoom the camera in
     manager->get(QNetworkRequest(QUrl("http://192.168.0.90/axis-cgi/com/ptz.cgi?camera=1&rzoom=+500")));
}

void MainWindow::on_pushButton_8_clicked()
{
    // zoom the camera out
     manager->get(QNetworkRequest(QUrl("http://192.168.0.90/axis-cgi/com/ptz.cgi?camera=1&rzoom=-500")));
}
