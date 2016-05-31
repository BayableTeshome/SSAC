#ifndef DISPLAYTHREAD_H
#define DISPLAYTHREAD_H
#include <QThread>
#include <QImage>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/videoio.hpp"
#include "TargetObject.h"
#include <opencv2/objdetect/objdetect.hpp>
class displayThread : public QThread
{
    Q_OBJECT
public:
    displayThread();
    explicit displayThread(QObject *parent =0);
    void run();
    int take=0;

private:
    cv::VideoCapture cap;
    cv::Mat frame;
    cv::Mat original;
    QImage img;
    cv::Mat RGBframe;
signals:
    void imageupdate(const QImage &image);


};

#endif // DISPLAYTHREAD_H
