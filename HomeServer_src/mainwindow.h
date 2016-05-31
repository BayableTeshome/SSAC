#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QUrl>
#include "displayThread.h"
#include "TargetObject.h"
#include "bgModelAndTrack.h"
#include "startStream.h"
#include "mythread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //displayThread *dispThread;
    startStream *newstream;
    vector<TargetObject> myObjects;
    Mat frame;
    Ptr<BackgroundSubtractor> pMOG2; //MOG2 Background subtractor
    VideoCapture cap;

public slots:
    void display(QImage img);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    QNetworkAccessManager *manager;
    displayThread *dispvideo;


};

#endif // MAINWINDOW_H
