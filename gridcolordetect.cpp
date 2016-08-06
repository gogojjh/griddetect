#include "gridcolordetect.h"

void  gridcolordetect(const Mat src, int &areaColor)
{
    Mat srcDst, redDst, yellowDst, blueDst;
    //resize(src, srcDst, Size(200, 200));
    src.copyTo(srcDst);
    cvtColor(srcDst, srcDst, CV_BGR2HSV);
    vector<Mat> channels;
    split(srcDst, channels);
    Mat srcH, srcS;
    channels[0].copyTo(srcH);
    channels[1].copyTo(srcS);
    Mat element = getStructuringElement(1, Size(3, 3));
    //areaColor = NOTHING;
    vector<vector<Point> > contours;

    // yes->white red
    /*
    redDst = (((srcH > 160) & (srcH < 180)) | ((srcH > 0) & (srcH < 20)));
    morphologyEx(redDst, redDst, MORPH_ERODE,  element);
    imshow("red", redDst);
    findContours( redDst, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE );
    //Mat imgContour;
    //redDst.copyTo(imgContour);
    //Scalar color(180, 180, 180);
    for (int i=0; i<contours.size(); i++)
    {
        //drawContours(imgContour,contours,i,color,3,8,vector<Vec4i>(),0,Point());
        float nowarea = contourArea(contours[i]);
        cout << "Red: " << nowarea << endl;
        if (nowarea >= redDst.rows*redDst.cols / 3)
        {
            areaColor = RED;
        }
    }*/
    //imshow("red", redDst);
    //imshow("redContour", imgContour);

    // yes->white yellow
    /*
    yellowDst = ((srcH > 65) & (srcH < 100)) ;
    morphologyEx(yellowDst, yellowDst, MORPH_DILATE,  element);
    findContours( yellowDst, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE );
    yellowDst.copyTo(imgContour);
    for (int i=0; i<contours.size(); i++)
    {
        drawContours(imgContour,contours,i,color,3,8,vector<Vec4i>(),0,Point());
        float nowarea = contourArea(contours[i]);
        cout << "Yellow: " << nowarea << endl;
        if (nowarea >= yellowDst.rows*yellowDst.cols / 3)
        {
            areaColor = YELLOW;
            return ;
        }
    }
    imshow("yellowContour", imgContour);
    imshow("yellow", yellowDst);
    cout << endl;*/

    // yes->white blue
    /*
    if (areaColor == NOTHING)
    {
        blueDst = ((srcH > 90) & (srcH < 120)) ;
        morphologyEx(blueDst, blueDst, MORPH_ERODE,  element);
        findContours( blueDst, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE );
        //blueDst.copyTo(imgContour);
        for (int i=0; i<contours.size(); i++)
        {
            float nowarea = contourArea(contours[i]);
            cout << "Blue: " << nowarea << endl;
            if (nowarea >= blueDst.rows*blueDst.cols / 3)
            {
                areaColor = BLUE;
            }
        }
        imshow("blue", blueDst);
        cout << endl;
    }
    waitKey(0);*/

    /*
    Mat red_test = imread( "/home/gogojjh/QT/griddetect/temp/red.jpg", 1 );
    Mat yellow_test = imread( "/home/gogojjh/QT/griddetect/temp/yellow.jpg", 1 );
    Mat blue_test = imread( "/home/gogojjh/QT/griddetect/temp/blue.jpg", 1 );

    Mat srcDst, redDst, yellowDst, blueDst;

    resize(src, srcDst, Size(100, 100));
    resize(red_test, redDst, Size(100, 100));
    resize(yellow_test, yellowDst, Size(100, 100));
    resize(blue_test, blueDst, Size(100, 100));

    cvtColor(srcDst, srcDst, CV_BGR2HSV);
    cvtColor(redDst, redDst, CV_BGR2HSV);
    cvtColor(yellowDst, yellowDst, CV_BGR2HSV);
    cvtColor(blueDst, blueDst, CV_BGR2HSV);
    Mat imgHSV;
    vector<Mat> channels;
    split(srcDst, channels);
    channels[0].copyTo(srcDst);
    split(redDst, channels);
    channels[0].copyTo(redDst);
    split(yellowDst, channels);
    channels[0].copyTo(yellowDst);
    split(blueDst, channels);
    channels[0].copyTo(blueDst);

    int redDiff = 0;
    int yellowDiff = 0;
    int blueDiff = 0;
    int i, j;
    uchar *p;
    for (i=0; i<srcDst.rows; i++)
        for (j=0; j<srcDst.cols; j++)
        {
            redDiff += abs(srcDst.at<uchar>(i,j)-redDst.at<uchar>(i,j));
            yellowDiff += abs(srcDst.at<uchar>(i,j)-yellowDst.at<uchar>(i,j));
            blueDiff += abs(srcDst.at<uchar>(i,j)-blueDst.at<uchar>(i,j));
        }

    cout << "Red: " << redDiff << endl;
    cout << "Yellow: " << yellowDiff << endl;
    cout << "Blue: " << blueDiff << endl;

    areaColor = RED;*/

    /*
    int srcAvg = 0, redAvg = 0, yellowAvg = 0, blueAvg = 0;
    int srcArr[64], redArr[64], yellowArr[64], blueArr[64];

    for (int i = 0; i < 8; i++)
    {
        uchar* srcData = srcDst.ptr<uchar>(i);
        uchar* redData = redDst.ptr<uchar>(i);
        uchar* yellowData = yellowDst.ptr<uchar>(i);
        uchar* blueData = blueDst.ptr<uchar>(i);
        int tmp = i * 8;
        for (int j = 0; j < 8; j++)
        {
            int tmp1 = tmp + j;
            srcArr[tmp1] = srcData[j] / 4 * 4;
            redArr[tmp1] = redData[j] / 4 * 4;
            yellowArr[tmp1] = yellowData[j] / 4 * 4;
            blueArr[tmp1] = blueData[j] / 4 * 4;

            srcAvg += srcArr[tmp1];
            redAvg += redArr[tmp1];
            yellowAvg += yellowArr[tmp1];
            blueAvg += blueArr[tmp1];
        }
    }

    srcAvg /= 64; redAvg /= 64; yellowAvg /= 64; blueAvg /= 64;

    for (int i = 0; i < 64; i++)
    {
        srcArr[i] = (srcArr[i] >= srcAvg) ? 1 : 0;
        redArr[i] = (redArr[i] >= srcAvg) ? 1 : 0;
        yellowArr[i] = (yellowArr[i] >= srcAvg) ? 1 : 0;
        blueArr[i] = (blueArr[i] >= srcAvg) ? 1 : 0;
    }

    int redDiff = 0, yellowDiff = 0, blueDiff = 0;
    for (int i = 0; i < 64; i++)
    {
        if (srcArr[i] != redArr[i]) ++redDiff;
        if (srcArr[i] != yellowArr[i]) ++yellowDiff;
        if (srcArr[i] != blueArr[i]) ++blueDiff;
    }

    cout << "Red: " << redDiff << endl;
    cout << "Yellow: " << yellowDiff << endl;
    cout << "Blue: " << blueDiff << endl;

    areaColor = RED;
    */
/*
    if (iDiffNum <= 5)
        cout<<"two images are very similar!"<<endl;
    else if (iDiffNum > 10)
        cout<<"they are two different images!"<<endl;
    else
        cout<<"two image are somewhat similar!"<<endl;
*/
}
