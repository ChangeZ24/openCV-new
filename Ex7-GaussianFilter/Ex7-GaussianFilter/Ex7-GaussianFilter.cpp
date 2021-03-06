// Ex7-GaussianFilter.cpp: 高斯滤波
//

#include "stdafx.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int main() {
	Mat image = imread("girl.jpg");
	namedWindow("girl");
	namedWindow("girl666");
	imshow("girl", image);

	//滤波操作
	Mat out;
	GaussianBlur(image, out, Size(3, 3), 0, 0);

	imshow("girl666", out);
	waitKey(0);
	return 0;
}