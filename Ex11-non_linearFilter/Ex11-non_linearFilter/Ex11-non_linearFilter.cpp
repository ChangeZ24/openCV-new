// Ex11-non_linearFilter.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

Mat g_srcImage, g_dstImage1, g_dstImage2, g_dstImage3, g_dstImage4, g_dstImage5;
int g_nBoxFilterValue = 6;//方框滤波参数值
int g_nMeanBlurValue = 10;//均值滤波参数值
int g_nGaussianBlurValue = 6;//高斯滤波参数值
int g_nMedianBlurValue = 10;//中值滤波参数值
int g_nBilateralFilterValue = 10;//双边滤波参数值

static void on_BoxFilter(int, void*) {

	boxFilter(g_srcImage, g_dstImage1, -1, Size(g_nBoxFilterValue + 1, g_nBoxFilterValue + 1));
	imshow("boxfilter", g_dstImage1);
}
static void on_MeanBlur(int, void*) {
	blur(g_srcImage, g_dstImage2, Size(g_nMeanBlurValue + 1, g_nMeanBlurValue + 1), Point(-1, -1));
	imshow("meanfilter", g_dstImage2);
}
static void on_GaussianBlur(int, void*) {
	GaussianBlur(g_srcImage, g_dstImage3, Size(g_nGaussianBlurValue * 2 + 1, g_nGaussianBlurValue * 2 + 1), 0, 0);
	imshow("gaussianfilter", g_dstImage3);
}
static void on_MedianBlur(int, void*) {
	medianBlur(g_srcImage, g_dstImage4, g_nMedianBlurValue * 2 + 1);
	imshow("medianfilter", g_dstImage4);
}
static void on_BilateralFilter(int, void*) {
	bilateralFilter(g_srcImage, g_dstImage5, g_nBilateralFilterValue, g_nBilateralFilterValue * 2, g_nBilateralFilterValue / 2);
	imshow("bilateralfilter", g_dstImage5);
}


int main() {
	system("color 5E");

	g_srcImage = imread("girl1.jpg", 1);
	if (!g_srcImage.data) {
		printf("fxxk!~ read failed!!\n");
		return false;
	}
	//克隆原图到5个Mat类型中
	g_dstImage1 = g_srcImage.clone();
	g_dstImage2 = g_srcImage.clone();
	g_dstImage3 = g_srcImage.clone();
	g_dstImage4 = g_srcImage.clone();
	g_dstImage5 = g_srcImage.clone();

	namedWindow("girl", 1);
	imshow("girl", g_srcImage);

	/***********************boxFilter***************************/

	namedWindow("boxfilter", 1);
	createTrackbar("内核值", "boxfilter", &g_nBoxFilterValue, 50, on_BoxFilter);
	on_BoxFilter(g_nBoxFilterValue, 0);

	/***********************meanFilter***************************/

	namedWindow("meanfilter", 1);
	createTrackbar("内核值", "meanfilter", &g_nMeanBlurValue, 50, on_MeanBlur);
	on_MeanBlur(g_nMeanBlurValue, 0);

	/***********************gaussianFilter***************************/

	namedWindow("gaussianfilter", 1);
	createTrackbar("内核值", "gaussianfilter", &g_nGaussianBlurValue, 50, on_GaussianBlur);
	on_GaussianBlur(g_nGaussianBlurValue, 0);

	/***********************medianFilter***************************/

	namedWindow("medianfilter", 1);
	createTrackbar("参数值", "medianfilter", &g_nMedianBlurValue, 50, on_MedianBlur);
	on_MedianBlur(g_nMedianBlurValue, 0);

	/***********************bilateralFilter***************************/

	namedWindow("bilateralfilter", 1);
	createTrackbar("参数值", "bilateralfilter", &g_nBilateralFilterValue, 50, on_BilateralFilter);
	on_BilateralFilter(g_nBilateralFilterValue, 0);
	waitKey(0);
	return 0;
}

