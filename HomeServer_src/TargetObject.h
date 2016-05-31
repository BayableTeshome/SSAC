#include <opencv2/core/core.hpp>
#include <opencv2/video/video.hpp>
#include "opencv2/features2d/features2d.hpp"
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include "opencv2/objdetect.hpp"
#include <string>
#include <opencv2/opencv.hpp>
// Output
#include <iostream>

// Vector
#include <vector>

using namespace std;
using namespace cv;


#ifndef TARGETOBJECT_H
#define TARGETOBJECT_H

class TargetObject //: public KalmanFilter
{
public:
    //Default Constructor
    TargetObject();

    // Overload constructors
    TargetObject(Rect, MatND);

    //Destructor
    ~TargetObject();

    //Accessor Functions
    KalmanFilter getTracker() const;
        //getTracker - returns kalman filter parametrs

    Mat getState() const;
        //getState - returns last measured state

    void setState();

    Mat getMeas() const;
        //getMeas - returns current measurement

    void setMeas(const Rect newBox);

    int getNotFoundCount();

    MatND getHistogram();

    void setHistogram(MatND);

    void predictObjectState(Mat& res, double dT);

    void correctTracker();



private:
    //Member Variables

    // >>>> Kalman Filter
    int stateSize, measSize, contrSize, notFoundCount;
    unsigned int type;
    bool found;

    KalmanFilter tracker;
    Mat state;
    Mat meas;
    // <<<< Kalman Filter

    // >>>> SIFT Parameters
//    vector<KeyPoint> keypoints;
//    Mat descriptors;
    MatND hist_base;
    // <<<< SIFT Parameters
};

#endif // TARGETOBJECT_H
