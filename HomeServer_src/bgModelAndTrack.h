#include "TargetObject.h"
#include "threatDetection.h"

#ifndef BGMODELANDTRACK_H
#define BGMODELANDTRACK_H

void trackObject(Mat&, vector<TargetObject>&, double, Ptr<BackgroundSubtractor>&);

bool featureAssociateHist(vector<TargetObject>&, const MatND&, const Rect&);

bool mergeRectangles(vector<Rect>&);

void enlargeRectangle(Rect&, int, int);


#endif // BGMODELANDTRACK_H
