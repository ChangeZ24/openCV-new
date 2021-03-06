// Ex16-Hough_Transform.cpp: 霍夫变换。
//

#include "stdafx.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

Mat g_srcImage, g_dstImage, g_midImage;
vector<Vec4i>g_lines;
int g_nthresshold = 100;

static void on_HoughLines(int, void*) {
	Mat dstImage = g_dstImage.clone();
	Mat midImage = g_midImage.clone();

	vector<Vec4i>mylines;
	HoughLinesP(midImage, mylines, 1, CV_PI / 180, g_nthresshold + 1, 50, 10);

	for (size_t i = 0; i < mylines.size(); i++) {
		Vec4i l = mylines[i];
		line(dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(23, 180, 55), 1, CV_AA);
	}
	imshow("111", dstImage);
}

int main(){
	system("color 3F");

	g_srcImage = imread("99.jpg");
	imshow("原", g_srcImage);
	
	namedWindow("111", 1);
	createTrackbar("值", "111", &g_nthresshold, 200, on_HoughLines);

	Canny(g_srcImage, g_midImage, 50, 200, 3);//检测边缘
	cvtColor(g_midImage, g_dstImage, CV_GRAY2BGR);//转化为灰度图

	on_HoughLines(g_nthresshold, 0);//回调函数
	HoughLinesP(g_midImage, g_lines, 1, CV_PI / 180, 80, 50, 10);//概率霍夫变换
	
	imshow("111", g_dstImage);

	
	waitKey(0);
    return 0;
}

