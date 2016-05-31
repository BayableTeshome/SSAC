#include "TargetObject.h"


TargetObject::TargetObject()
{
    stateSize = 6;
    measSize = 4;
    contrSize = 0;
    notFoundCount = 0;
    found = false;
    type = CV_32F;
}

TargetObject::TargetObject(Rect newBox, MatND newHistogram) // think about pass by value
{
    // >>>> Kalman Filter
    stateSize = 6;
    measSize = 4;
    contrSize = 0;
    notFoundCount = 0;
    found = false;
    type = CV_32F;

//    // >>>> SIFT Parameters
//    keypoints = newKeypoints;
//    descriptors = newDescriptors;
//    // <<<< SIFT Parameters

    //>>>>> Histogram params
    hist_base = newHistogram;
    //<<<<< Histogram params

    tracker.init(stateSize, measSize, contrSize, type);

    Mat newState(stateSize, 1, type);  // [x,y,v_x,v_y,w,h]
    newState.copyTo(state);
    Mat newMeas(measSize, 1, type);    // [z_x,z_y,z_w,z_h] try to obtimize this copy
    newMeas.copyTo(meas);

    setIdentity(tracker.transitionMatrix);

    tracker.measurementMatrix = Mat::zeros(measSize, stateSize, type);
    tracker.measurementMatrix.at<float>(0) = 1.0f;
    tracker.measurementMatrix.at<float>(7) = 1.0f;
    tracker.measurementMatrix.at<float>(16) = 1.0f;
    tracker.measurementMatrix.at<float>(23) = 1.0f;

    tracker.processNoiseCov.at<float>(0) = 1e-2;
    tracker.processNoiseCov.at<float>(7) = 1e-2;
    tracker.processNoiseCov.at<float>(14) = 5.0f;
    tracker.processNoiseCov.at<float>(21) = 5.0f;
    tracker.processNoiseCov.at<float>(28) = 1e-2;
    tracker.processNoiseCov.at<float>(35) = 1e-2;

    setIdentity(tracker.measurementNoiseCov, cv::Scalar(1e-1));
     //<<<< Kalman Filter

    meas.at<float>(0) = newBox.x + newBox.width / 2;
    meas.at<float>(1) = newBox.y + newBox.height / 2;
    meas.at<float>(2) = (float)newBox.width;
    meas.at<float>(3) = (float)newBox.height;

    // >>>> Initialization >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> needs attention here
    tracker.errorCovPre.at<float>(0) = 1; // px
    tracker.errorCovPre.at<float>(7) = 1; // px
    tracker.errorCovPre.at<float>(14) = 1;
    tracker.errorCovPre.at<float>(21) = 1;
    tracker.errorCovPre.at<float>(28) = 1; // px
    tracker.errorCovPre.at<float>(35) = 1; // px

    state.at<float>(0) = meas.at<float>(0);
    state.at<float>(1) = meas.at<float>(1);
    state.at<float>(2) = 0;
    state.at<float>(3) = 0;
    state.at<float>(4) = meas.at<float>(2);
    state.at<float>(5) = meas.at<float>(3);
    // <<<< Initialization

    found = true;

}

TargetObject::~TargetObject()
{

}

KalmanFilter TargetObject::getTracker() const
{
    return tracker;
}

Mat TargetObject::getState() const
{
    return state;
}

void TargetObject::setState()
{
    state = tracker.predict();
}

Mat TargetObject::getMeas() const
{
    return meas;
}

void TargetObject::setMeas(const Rect newBox)
{
    meas.at<float>(0) = newBox.x + newBox.width / 2;
    meas.at<float>(1) = newBox.y + newBox.height / 2;
    meas.at<float>(2) = (float)newBox.width;
    meas.at<float>(3) = (float)newBox.height;
    found = true;
    //tracker.correct(newMeas);
}
int TargetObject::getNotFoundCount()
{
    return notFoundCount;
}

//vector<KeyPoint> TargetObject::getKeypoints()
//{
//    return keypoints;
//}

//void TargetObject::setKeyPoints(vector<KeyPoint> newKeyPoints)
//{
//    keypoints = newKeyPoints;
//}

//Mat TargetObject::getDescriptors()
//{
//    return descriptors;
//}

//void TargetObject::setDescriptors(Mat newDescriptors)
//{
//    descriptors = newDescriptors;
//}

MatND TargetObject::getHistogram()
{
    return hist_base;
}

void TargetObject::setHistogram(MatND newHistogram)
{
    hist_base = newHistogram;
}

void TargetObject::correctTracker()
{
    if (found)
    {
        tracker.correct(meas);
        found = false;
        notFoundCount = 0;
    }
    else
    {
        notFoundCount++;
        if( notFoundCount >= 100 )
        {
            // drope me
        }
    }


}

void TargetObject::predictObjectState(Mat& res, double dT)
{
    if (notFoundCount<100)
    {
        tracker.transitionMatrix.at<float>(2) = dT;
        tracker.transitionMatrix.at<float>(9) = dT;

        state = tracker.predict();

        Rect predRect;
        predRect.width = state.at<float>(4);
        predRect.height = state.at<float>(5);
        predRect.x = state.at<float>(0) - predRect.width / 2;
        predRect.y = state.at<float>(1) - predRect.height / 2;

        Point center;
        center.x = state.at<float>(0);
        center.y = state.at<float>(1);
        circle(res, center, 2, CV_RGB(255,0,0), -1);

        rectangle(res, predRect, CV_RGB(255,0,0), 2);
    }
}










