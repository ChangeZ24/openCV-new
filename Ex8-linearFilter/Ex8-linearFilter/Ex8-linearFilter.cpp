// Ex8-linearFilter.cpp: 方框滤波、均值滤波、高斯滤波综合
//

#include "stdafx.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

Mat g_srcImage, g_dstImage1, g_dstImage2, g_dstImage3;
int g_nBoxFilterValue = 3;//方框滤波参数值
int g_nMeanBlurValue = 3;//均值滤波参数值
int g_nGaussianBlurValue = 3;//高斯滤波参数值

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


int main(){
	system("color 5E");

	g_srcImage = imread("girl1.jpg", 1);
	if (!g_srcImage.data) {
		printf("fxxk!~ read failed!!\n");
		return false;
	}
	//克隆原图到3个Mat类型中
	g_dstImage1 = g_srcImage.clone();
	g_dstImage2 = g_srcImage.clone();
	g_dstImage3 = g_srcImage.clone();
    
	namedWindow("girl", 1);
	imshow("girl", g_srcImage);

	/***********************boxFilter***************************/
	
	namedWindow("boxfilter", 1);
	createTrackbar("内核值", "boxfilter", &g_nBoxFilterValue, 40, on_BoxFilter);
	on_BoxFilter(g_nBoxFilterValue, 0);

	/***********************meanFilter***************************/

	namedWindow("meanfilter", 1);
	createTrackbar("内核值", "meanfilter", &g_nMeanBlurValue, 40, on_MeanBlur);
	on_MeanBlur(g_nMeanBlurValue, 0);
	
	/***********************gaussianFilter***************************/

	namedWindow("gaussianfilter", 1);
	createTrackbar("内核值", "gaussianfilter", &g_nGaussianBlurValue, 40, on_GaussianBlur);
	on_GaussianBlur(g_nGaussianBlurValue, 0);
	
	waitKey(0);
	return 0;
}

