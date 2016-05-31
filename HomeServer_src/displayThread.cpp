#include "displayThread.h"
#include "TargetObject.h"
#include "mainwindow.h"
#include "threatDetection.h"
#include "startRecord.h"
#include <QImage>
#include <QDebug>
#include <QtCore>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/videoio.hpp"
#include <opencv2/objdetect/objdetect.hpp>
#include "globalVariables.h"
using namespace cv;
displayThread::displayThread( QObject *parent):
    QThread(parent)
{

}

void displayThread::run()
{
   // cap.open("http://root:mmnet@192.168.0.90/mjpg/video.mjpg");
   // cap.open(0);
    VideoCapture cap("souphttpsrc location=http://root:mmnet@192.168.0.90/mjpg/video.mjpg is_live=true ! jpegdec ! videoconvert ! appsink");
    QTime time = QTime::currentTime();
    QString timeString = time.toString();
    String time2 =timeString.toStdString();
    QDate date=QDate::currentDate();
    QString dateString = date.toString();
    String dateandtime =dateString.toStdString();
    String  textvi = "Videos/" + dateandtime + " " + time2 +".avi";

    MainWindow *status;
    status=new MainWindow();
    vector<TargetObject> myObjects;
    Ptr<BackgroundSubtractor> pMOG2; //MOG2 Background subtractor
    pMOG2 = createBackgroundSubtractorMOG2(500,16,false); //MOG2 approach
    double ticks = 0;


     while(camStop==false)
   {
         cap >> frame;
        // if(status->getTracker())
        if(Tracker==true)
         {
             double precTick = ticks;
             ticks = (double) getTickCount();
             double dT = (ticks - precTick) / getTickFrequency(); //seconds
             trackObject(frame,myObjects,dT,pMOG2);
       }
         if(Alarm==true)
         {

             faceRecognition(frame);
         }

         if(Record==true)
         {
           // record(frame);
            cv::VideoWriter oVideoWriter (textvi,oVideoWriter.fourcc('M','J','P','G'),10,cvSize(640,480),true);
            cv::putText(frame,time2,cv::Point(300,400),1,2,cv::Scalar(0,255,0),2);
            cv::putText(frame,dateandtime,cv::Point(0,400),1,2,cv::Scalar(0,255,0),2);
            oVideoWriter.write(frame);

         }

         cv::resize(frame,frame,cvSize(740,510));
         cv::cvtColor(frame, original,  cv::COLOR_BGR2RGB);
         img= QImage((uchar*) original.data, original.cols, original.rows, original.step, QImage::Format_RGB888);
         emit imageupdate(img);
   }

    cap.release();

}

