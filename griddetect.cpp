#include "griddetect.h"
#include "gridcolordetect.h"
#include "findrect.h"

int main()
{
    Mat imgResize = imread("/home/gogojjh/QT/griddetect/data/12.jpg", 1);
    int cnt = 0;
    int avearea = 0;

    /*rgb2hsv */
    Mat imgHSV = Mat::zeros(imgResize.rows,imgResize.cols,imgResize.type());
    vector<Mat> channels;
    cvtColor( imgResize, imgHSV, CV_BGR2HSV );

    split(imgHSV,channels);
    Mat imgH = channels.at(0);
    Mat imgS = channels.at(1);
    Mat imgV = channels.at(2);

    /* extract the lighting area */
    Mat imgVthreshold;
    threshold(imgV,imgVthreshold,205,255,cv::THRESH_BINARY);

    Mat imgHMasked = Mat::zeros(imgResize.rows,imgResize.cols,imgResize.type());
    imgH.copyTo(imgHMasked, imgVthreshold);
    Mat imgRed = (((imgHMasked > 160)&(imgHMasked < 180))|((imgHMasked > 0)&(imgHMasked < 15)));
    Mat imgBlue = ((imgHMasked > 90) & (imgHMasked < 120));
    //Mat imgYellow = ((imgHMasked > 90) & (imgHMasked < 120));

    float angle = -1;
    float minD = imgResize.cols * imgResize.rows;
    Point2f goal;

    findrect(imgResize, imgRed,  angle, goal, minD);
    waitKey(0);
    findrect(imgResize, imgBlue,  angle, goal, minD);
    waitKey(0);
    //findrect(imgResize, imgYellow,  angle, goal, minD);
    //waitKey(0);
    if (minD<50) angle = -2;
    cout << "Angle: " << angle << endl;
    return 0;
}
