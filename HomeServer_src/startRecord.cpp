#include "startRecord.h"
#include "mythread.h"
#include <QDebug>
#include <QtCore>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/videoio.hpp"
#include <opencv2/objdetect/objdetect.hpp>
using namespace cv;

void record(Mat & frame)
{
        QTime time = QTime::currentTime();
        QString timeString = time.toString();
        String time2 =timeString.toStdString();

        QDate date=QDate::currentDate();
        QString dateString = date.toString();
        String dateandtime =dateString.toStdString();

        String  textvi = "Videos/" + dateandtime + " " + time2 +".avi";


         cv::VideoWriter oVideoWriter (textvi,oVideoWriter.fourcc('M','J','P','G'),10,cvSize(640,480),true);

         cv::putText(frame,time2,cv::Point(300,400),1,2,cv::Scalar(0,255,0),2);
         cv::putText(frame,dateandtime,cv::Point(0,400),1,2,cv::Scalar(0,255,0),2);
         oVideoWriter.write(frame);



 }

