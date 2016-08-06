#include "findrect.h"

void findrect(const Mat src, const Mat imgBinary, float &an, Point2f &goal, float &minD)
{
    /* dilate */
    Mat imgResult;
    src.copyTo(imgResult);
    Mat element = getStructuringElement(1, Size(5, 5));
    morphologyEx(imgBinary, imgBinary, MORPH_DILATE,  element);;
    imshow("img", imgBinary);

    vector<Vec4i> lines;
    /* operation in Red Areas*/
    HoughLinesP(imgBinary, lines, 1, CV_PI/90, 50, 10, 0 );
    Mat imgLines = Mat::zeros(imgBinary.rows,imgBinary.cols,imgBinary.type());
    for( size_t i = 0; i < lines.size(); i++ )
    {
        Vec4i l = lines[i];
        line( imgLines, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255), 10, CV_AA);
    }
    // draw the line
    //imshow("imgLineR", imgLines);

    /* find contours through the lines*/
    vector<vector<Point> > contoursr;
    vector<Vec4i> hierarchyr;
    Mat imgr2c;
    imgLines.copyTo(imgr2c);

    element = getStructuringElement(1, Size(20, 20));
    morphologyEx(imgr2c, imgr2c, MORPH_DILATE,  element);
    //imshow("img2r",imgr2c);

    int top = 0.005*src.rows; int bottom = 0.005*src.rows;
    int left = 0.005*src.cols; int right = 0.005*src.cols;
    Scalar border(255);
    copyMakeBorder( imgr2c, imgr2c, top, bottom, left, right, BORDER_CONSTANT, border );

    imgr2c = ~imgr2c;

    vector<Vec4i> hierarchy;

    /* find interior contours */
    //findContours( imgr2c, contoursr, hierarchyr,CV_RETR_CCOMP,CHAIN_APPROX_SIMPLE );
    findContours( imgr2c, contoursr, CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE );

    //Mat imgContour;
    //imgRed.copyTo(imgContour);
    Mat imgROI;
    vector<Mat> imgAp;
    Scalar color(180, 180, 180);
    Point2f center(src.cols/2, src.rows/2);
    float near_point = src.cols * src.rows;
    float angle;
    for(int i = 0;i<contoursr.size();i ++)
    {
            //drawContours(imgContour,contoursr,i,color,3,8,vector<Vec4i>(),0,Point());
            //if ((hierarchyr[i][3]) != -1)
            //{
                float nowarea = contourArea(contoursr[i]);
                if ((nowarea > 6000) && (nowarea <100000))
                {
                    cout << "Area: " << nowarea << endl;
                    drawContours(imgResult,contoursr,i,color,3,8,vector<Vec4i>(),0,Point());

                    /* use rectangles */
                    RotatedRect box = minAreaRect(Mat(contoursr[i]));
                    Point2f vertex[4];
                    box.points(vertex);
                    for(int j = 0;j < 4;j ++)
                    {
                        line(imgResult,vertex[j],vertex[(j+1)%4],CV_RGB(255,0,0),2,CV_AA);
                    }

                    Rect rect = box.boundingRect();
                    rect.x = max(0, rect.x); rect.y = max(0, rect.y);
                    rect.width = rect.x+rect.width>=src.cols ? src.cols-rect.x-1 : rect.width;
                    rect.height = rect.y+rect.height>=src.rows ? src.rows-rect.y-1 : rect.height;
                    imgROI = src(rect);
                    //imshow("ROI", imgROI);
                    //waitKey(0);

                    /* get the center */
                    Point2f imgROI_center;
                    imgROI_center.x = (vertex[0].x + vertex[1].x + vertex[2].x + vertex[3].x)/4;
                    imgROI_center.y = (vertex[0].y + vertex[1].y + vertex[2].y + vertex[3].y)/4;
                    circle(imgResult,imgROI_center,2,Scalar(0,0,255),2);

                    /* find the average length */
                    float length[5] = {0};
                    length[0] = (vertex[0].x - vertex[1].x)*(vertex[0].x - vertex[1].x) + (vertex[0].y - vertex[1].y)*(vertex[0].y - vertex[1].y);
                    length[1] = (vertex[1].x - vertex[2].x)*(vertex[1].x - vertex[2].x) + (vertex[1].y - vertex[2].y)*(vertex[1].y - vertex[2].y);
                    length[2] = (vertex[2].x - vertex[3].x)*(vertex[2].x - vertex[3].x) + (vertex[2].y - vertex[3].y)*(vertex[2].y - vertex[3].y);
                    length[3] = (vertex[0].x - vertex[3].x)*(vertex[0].x - vertex[3].x) + (vertex[0].y - vertex[3].y)*(vertex[0].y - vertex[3].y);
                    for(int k = 0;k < 4;k++)
                    {
                        length[5]+=length[i];
                    }
                    length[5]/=4;
                    if (sqrt(pow(center.x-imgROI_center.x, 2.0)+pow(center.y-imgROI_center.y, 2.0)) < near_point)
                    {
                        near_point = sqrt(pow(center.x-imgROI_center.x, 2.0)+pow(center.y-imgROI_center.y, 2.0));
                        goal.x = imgROI_center.x; goal.y = imgROI_center.y;
                        if (center.y > imgROI_center.y)
                        {
                            if ( imgROI_center.x>center.x )
                            {
                                angle=180*atan(float ((imgROI_center.x-center.x)/(center.y-imgROI_center.y))) / PI;
                            }
                            else
                            {
                                angle=360 + 180*atan(float ((imgROI_center.x-center.x)/(center.y-imgROI_center.y))) / PI;
                            }
                        }
                        else if (center.y < imgROI_center.y)
                        {
                             if (imgROI_center.x>center.x )
                            {
                               angle=180 - 180*atan(float ((imgROI_center.x-center.x)/(imgROI_center.y-center.y))) / PI;
                            }
                            else
                            {
                                angle=180 + 180*atan(float ((center.x-imgROI_center.x)/(imgROI_center.y-center.y))) / PI;
                            }
                        }
                    }
            }
    }
    if (near_point < minD)
    {
        minD = near_point;
        an = angle;
    }
    imshow("imgResult",imgResult);
}
