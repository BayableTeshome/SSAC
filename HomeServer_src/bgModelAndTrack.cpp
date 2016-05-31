#include "bgModelAndTrack.h"
#include "TargetObject.h"



void trackObject(Mat& frame, vector<TargetObject>& myObjects, double dT, Ptr<BackgroundSubtractor>& pMOG2){
    Mat res, fgMaskMOG2;

    // resize(frame, frame, Size(640,480)); //for saved video
    frame.copyTo( res );


    // >>>> Predict
    unsigned int size = myObjects.size();
    //cout<<size <<" objects moving"<<endl;
    for (unsigned int i = 0; i < size; i++)
    {
        myObjects[i].predictObjectState(frame, dT);
    }
    // <<<< Predict

    // >>>>> Noise smoothing
    GaussianBlur(res, res, Size(5, 5), 3.0, 3.0);
    // <<<<< Noise smoothing

    // >>>> Background Subtraction
    pMOG2->apply(res, fgMaskMOG2);
    // <<<< Background Subtraction

    // >>>>> Improving the result
    cv::erode(fgMaskMOG2, fgMaskMOG2, cv::Mat(), cv::Point(-1, -1), 2);
    cv::dilate(fgMaskMOG2, fgMaskMOG2, cv::Mat(), cv::Point(-1, -1), 2);
    // <<<<< Improving the result

    // >>>>> Contours detection
    vector<vector<Point> > contours;
    findContours(fgMaskMOG2, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    // <<<<< Contours detection

    // >>>>> Histogram Params
    Mat hsv_base;
    // Using 50 bins for hue and 60 for saturation
    int h_bins = 50; int s_bins = 60;
    int histSize[] = { h_bins, s_bins };

    // hue varies from 0 to 179, saturation from 0 to 255
    float h_ranges[] = { 0, 180 };
    float s_ranges[] = { 0, 256 };

    const float* ranges[] = { h_ranges, s_ranges };

    // Use the o-th and 1-st channels
    int channels[] = { 0, 1 };

    // >>>>> Histogram Params
    MatND hist_base;
    // <<<<< Histogram Params

    vector<Rect> boxRect;

    int frameCols = frame.cols;
    int frameRows = frame.rows;

    for (size_t i = 0; i < contours.size(); i++)
    {
        Rect bBox;
        bBox = boundingRect(contours[i]);

        // Searching for a bBox almost square
        if (bBox.area() >= 3500) // this is a hard decision (threshold for smallest object detection)
        {
            enlargeRectangle(bBox, frameCols, frameRows);
            boxRect.push_back(bBox);
        }
    }

    //>>>>> Feature Assosiation

    if (boxRect.size() > 1)
    {
        bool overlap = mergeRectangles(boxRect);

        while(overlap && (boxRect.size() > 1))
        {
            overlap = mergeRectangles(boxRect);
        }
    }


    for (size_t j=0; j<boxRect.size(); j++)
    {
        rectangle(frame, boxRect[j], CV_RGB(0,255,0), 1);


        // >>>>> Histogram Coputation
//           frame(boxRect[j]).copyTo(src_base); // got problem, handle the frame size...

//           cout << "There are " << boxRect.size() << endl;

        cvtColor( frame(boxRect[j]), hsv_base, COLOR_BGR2HSV );
        calcHist( &hsv_base, 1, channels, Mat(), hist_base, 2, histSize, ranges, true, false );
        normalize( hist_base, hist_base, 0, 1, NORM_MINMAX, -1, Mat() );

        // <<<<< Histogram Computation

//               detector->detectAndCompute( frame(bBox), Mat(), keypoints, descriptors);
        //associateFeatures -> use function or associate here
        bool matchFound = featureAssociateHist(myObjects, hist_base, boxRect[j]);
        if (!matchFound)
        {
            TargetObject newObject(boxRect[j], hist_base);
            myObjects.push_back(newObject);
            //cout << "There are " << myObjects.size() << " Objects." << endl;
        }
    }


    //<<<<< Feature Assosiation

    // <<<<< Filtering
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    // correct and/or update tracker parametrs
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

    size = myObjects.size();
    for (unsigned int i=0; i<size; i++)
    {
        int notFoundCount = myObjects[i].getNotFoundCount();
        if (notFoundCount >=100)
        {
            myObjects.erase(myObjects.begin() + i); //dropObject
        }
        else
        {
            myObjects[i].correctTracker();
        }
    }

}

bool featureAssociateHist(vector<TargetObject>& newMyObjects, const MatND& hist_base, const Rect& newBox){

    bool newMatchFound = false;
    double goodMatch = 100;
    int matchPoint;
    unsigned int size = newMyObjects.size();
    for (unsigned int i = 0; i < size; i++)   // finds the minimum histogram distance
    {
        Mat PrevHist=newMyObjects[i].getHistogram();
        double base_test = compareHist( hist_base, PrevHist, 2 );

        if (base_test < goodMatch)
        {
            goodMatch = base_test;
            matchPoint = i;
        }
    }

    if (goodMatch < 50) /// tune this parameter
    {
       // cout<<"object number "<< matchPoint <<" have min dist: "<< goodMatch <<endl;
        newMyObjects[matchPoint].setMeas(newBox);
        newMyObjects[matchPoint].setHistogram(hist_base);
        newMatchFound = true;
    }

    return newMatchFound;
}

bool mergeRectangles(vector<Rect>& boxRect)
{
    bool overlapFound = false;
    size_t length = boxRect.size();

    for (size_t i = 0; i < (length - 1); i++)
    {
        for (size_t j = i + 1; j < length; j++)
        {
            if((boxRect.size() > j) && ((boxRect[i] & boxRect[j]).area() > 0))
            {
                vector<Rect> tempRect;
                tempRect.push_back(boxRect[i] | boxRect[j]);
                boxRect.erase(boxRect.begin() + i);
                boxRect.erase(boxRect.begin() + j);
                boxRect.push_back(tempRect[0]);
                overlapFound = true;
            }

        }
    }
    return overlapFound;
}

void enlargeRectangle(Rect& bBox, int frameCols, int frameRows)
{
    int pad = 25; /// tune this parameter
    if (bBox.x > pad)
    {
        bBox.x = bBox.x - pad;
        if ((bBox.x + bBox.width) >= (frameCols - 1 - 2*pad))
        {
            bBox.width = frameCols-bBox.x;
        }
        else
        {
            bBox.width = bBox.width + 2*pad;
        }
    }
    else
    {
        if ((bBox.x + bBox.width) >= (frameCols -1 - pad))
        {
            bBox.width = frameCols-bBox.x;
        }
        else
        {
            bBox.width = bBox.width + pad;
        }
    }

    if (bBox.y > pad)
    {
        bBox.y = bBox.y - pad;
        if ((bBox.y + bBox.height) >= (frameRows -1 - 2*pad))
        {
            bBox.height = frameRows-bBox.y;
        }
        else
        {
            bBox.height = bBox.height + 2*pad;
        }
    }
    else
    {
        if ((bBox.y + bBox.height) >= (frameRows -1 - pad))
        {
            bBox.height = frameRows-bBox.y;
        }
        else
        {
            bBox.height = bBox.height + pad;
        }
    }
}
