#ifndef GRIDCOLORDETECT_H
#define GRIDCOLORDETECT_H

#include <iostream>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#define RED 0
#define YELLOW 1
#define BLUE 2
#define NOTHING -1
#define PI 3.1415926

using namespace std;
using namespace cv;

void  gridcolordetect(const Mat imgROI, int &areaColor);

#endif // GRIDCOLORDETECT_H
