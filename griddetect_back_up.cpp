/*
Mat hsv_src;
Mat red_test, hsv_red;
Mat yellow_test, hsv_yellow;
Mat blue_test, hsv_blue;

red_test = imread( "/home/gogojjh/QT/griddetect/temp/red.jpg", 1 );
yellow_test = imread( "/home/gogojjh/QT/griddetect/temp/yellow.jpg", 1 );
blue_test = imread( "/home/gogojjh/QT/griddetect/temp/blue.jpg", 1 );

cvtColor( src, hsv_src, CV_BGR2HSV );
cvtColor( red_test, hsv_red, CV_BGR2HSV );
cvtColor( yellow_test, hsv_yellow, CV_BGR2HSV );
cvtColor( blue_test, hsv_blue, CV_BGR2HSV );

int hue_bins = 50; int saturatoin_bins = 60;
int histSize[] = { hue_bins, saturatoin_bins };


float hue_ranges[] = { 0, 360 };
//float saturation_ranges[] = { 0, 180 };
const float* ranges[] = { hue_ranges };

int channels[] = { 0};

MatND hist_base;
MatND hist_red;
MatND hist_yellow;
MatND hist_blue;

// calculate each hist of each image
calcHist( &hsv_src, 1, channels, Mat(), hist_base, 1, histSize, ranges, true, false );
normalize( hist_base, hist_base, 0, 1, NORM_MINMAX, -1, Mat() );

calcHist( &red_test, 1, channels, Mat(), hist_red, 1, histSize, ranges, true, false );
normalize( hist_red, hist_red, 0, 1, NORM_MINMAX, -1, Mat() );

calcHist( &yellow_test, 1, channels, Mat(), hist_yellow, 1, histSize, ranges, true, false );
normalize( hist_yellow, hist_yellow, 0, 1, NORM_MINMAX, -1, Mat() );

calcHist( &blue_test, 1, channels, Mat(), hist_blue, 1, histSize, ranges, true, false );
normalize( hist_blue, hist_blue, 0, 1, NORM_MINMAX, -1, Mat() );

// different methods to compare
for( int i = 2; i < 3; i++ )
{
    int compare_method = i;
    double cbase = compareHist( hist_base, hist_base, compare_method );
    double cred = compareHist( hist_base, hist_red, compare_method );
    double cyellow = compareHist( hist_base, hist_yellow, compare_method );
    double cblue = compareHist( hist_base, hist_blue, compare_method );
    cout << "Base: " << cbase << " Red: " << cred << " Yellow: " << cyellow << " Blue: " << cblue << endl;

}
cout << "Done" << endl;
areaColor = RED;
*/
