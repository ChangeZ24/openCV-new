// Ex5-boxFilter.cpp: 方框滤波
//

#include "stdafx.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int main(){
	Mat image = imread("girl.jpg");
	namedWindow("girl");
	namedWindow("girl666");
	imshow("girl", image);

	//滤波操作
	Mat out;
	boxFilter(image, out, -1, Size(5, 5));

	imshow("girl666", out);
	waitKey(0);
    return 0;
}

