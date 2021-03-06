// Ex14-edge_detector.cpp:边缘检测-----canny、sobel、laplace算子，scharr滤波器
#include"stdafx.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

Mat g_srcImage, g_srcGrayImage, g_dstImage;
//Canny边缘检测相关变量
Mat g_cannyDetectedEdges;
int g_cannyLowThreshold = 1;
//Sobel边缘检测相关变量
Mat g_sobelGradient_X, g_sobelGradient_Y;
Mat g_sobelAbsGradient_X, g_sobelAbsGradient_Y;
int g_sobelKernelSize = 1;//Trackbar位置参数
//Scharr滤波器相关变量
Mat g_scharrGradient_X, g_scharrGradient_Y;
Mat g_scharrAbsGradient_X, g_scharrAbsGradient_Y;

//回调函数
static void on_Canny(int, void*) {
	//使用3x3的内核降噪
	blur(g_srcGrayImage, g_cannyDetectedEdges, Size(3, 3));
	//Canny算子
	Canny(g_cannyDetectedEdges, g_cannyDetectedEdges, g_cannyLowThreshold, g_cannyLowThreshold * 3, 3);
	//使用输出边缘图g_cannyDetectedEdges作为掩码将原图copy到输出图
	g_dstImage = Scalar::all(0);
	g_srcImage.copyTo(g_dstImage, g_cannyDetectedEdges);
	
	imshow("boy_canny", g_dstImage);
}
static void on_Sobel(int, void*) {
	//求X方向梯度并计算绝对值，将结果转换为8位
	Sobel(g_srcImage, g_sobelGradient_X, CV_16S, 1, 0, (2 * g_sobelKernelSize + 1), 1, 1, BORDER_DEFAULT);
	convertScaleAbs(g_sobelGradient_X, g_sobelAbsGradient_X);
	//求Y方向梯度并计算绝对值，将结果转换为8位
	Sobel(g_srcImage, g_sobelGradient_Y, CV_16S, 0, 1, (2 * g_sobelKernelSize + 1), 1, 1, BORDER_DEFAULT);
	convertScaleAbs(g_sobelGradient_Y, g_sobelAbsGradient_Y);
	//合并梯度
	addWeighted(g_sobelAbsGradient_X, 0.5, g_sobelAbsGradient_Y, 0.5, 0, g_dstImage);

	imshow("boy_sobel", g_dstImage);
}
void Scharr() {
	//求X方向梯度并计算绝对值，将结果转换为8位
	Scharr(g_srcImage, g_scharrGradient_X, CV_16S, 1, 0, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(g_scharrGradient_X, g_scharrAbsGradient_X);
	//求Y方向梯度并计算绝对值，将结果转换为8位
	Scharr(g_srcImage, g_scharrGradient_Y, CV_16S, 0, 1, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(g_scharrGradient_Y, g_scharrAbsGradient_Y);
	//合并梯度
	addWeighted(g_scharrAbsGradient_X, 0.5, g_scharrAbsGradient_Y, 0.5, 0, g_dstImage);

	imshow("boy_scharr", g_dstImage);
}

int main(){
	system("color 2F");
	printf("按下“q”键程序退出！！");

	g_srcImage = imread("lin.jpg");
	if (!g_srcImage.data) {
		printf("fxxk!~~read failed!!\n");
		return false;
	}

	namedWindow("boy");
	imshow("boy", g_srcImage);
	//原图转换为灰度图
	g_dstImage.create(g_srcImage.size(), g_srcImage.type());
	cvtColor(g_srcImage, g_srcGrayImage, CV_BGR2GRAY);

	namedWindow("boy_canny", CV_WINDOW_AUTOSIZE);
	namedWindow("boy_sobel", CV_WINDOW_AUTOSIZE);
	//创建轨迹条
	createTrackbar("参数值", "boy_canny", &g_cannyLowThreshold, 120, on_Canny);
	createTrackbar("参数值", "boy_sobel", &g_sobelKernelSize, 3, on_Sobel);
	//设置回掉函数
	on_Canny(0, 0);
	on_Sobel(0, 0);
	//调用边缘检测
	Scharr();

	waitKey(0);
    return 0;
}

