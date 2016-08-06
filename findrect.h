#ifndef FINDRECT_H
#define FINDRECT_H

#include <iostream>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#define PI 3.1415926

using namespace std;
using namespace cv;

void findrect(const Mat src, const Mat imgBinary, float &angle, Point2f &goal, float &minD);

#endif // FINDRECT_H
