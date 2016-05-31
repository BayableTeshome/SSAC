#include "threatDetection.h"
#include "opencv2/face.hpp"
#include <opencv2/opencv.hpp>
#include "opencv2/objdetect.hpp"
#include "globalVariables.h"

using namespace cv::face;
void faceRecognition(Mat& frame)
{

    string fn_haar = string("haarcascade_frontalface_alt.xml");
    Ptr<FaceRecognizer> model = createFisherFaceRecognizer();
    string persone;
    Mat original;
    model->load("model_2.yml");
    CascadeClassifier haar_cascade;
    haar_cascade.load(fn_haar);
    // Clone the current frame:
    original = frame;
    // Convert the current frame to grayscale:
    Mat gray;
    cvtColor(original, gray, CV_BGR2GRAY);
    // Find the faces in the frame:
    vector< Rect_<int> > faces;
    haar_cascade.detectMultiScale(gray, faces);
    for(int i = 0; i < faces.size(); i++) {
        // Process face by face:
        Rect face_i = faces[i];
        Mat face = gray(face_i);
        Mat face_resized;
        cv::resize(face, face_resized, Size(92,112), 1.0, 1.0, INTER_CUBIC);
        int predicted_label = -1;
        double predicted_confidence = 0.0;
        model->predict(face_resized, predicted_label, predicted_confidence);
        rectangle(original, face_i, CV_RGB(0, 255,0), 1);
        if (predicted_label==1 && predicted_confidence>500)
        {
            persone ="yonas";
            isDetected=false;


        }
        else if(predicted_label==0 && predicted_confidence>100)
        {
            persone="yonas";
             isDetected=false;
        }
        else
        {
            persone="unknown";
            isDetected=true;

        }
        string box_text = persone;
        int pos_x = std::max(face_i.tl().x - 10, 0);
        int pos_y = std::max(face_i.tl().y - 10, 0);
        putText(frame, box_text, Point(pos_x, pos_y), FONT_HERSHEY_PLAIN, 1.0, CV_RGB(0,255,0), 2.0);

        }


}
