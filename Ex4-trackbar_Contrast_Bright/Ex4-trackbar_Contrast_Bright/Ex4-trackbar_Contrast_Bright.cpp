// Ex4-trackbar_Contrast_Bright.cpp: 创建轨迹条进行亮度、对比度调整
//

#include "stdafx.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int g_nContrastValue;//对比度
int g_nBrightValue;//亮度
Mat g_srcImage, g_dstImage;

static void ContrastAndBright(int, void*) {
	namedWindow("girl", 1);

	//调整对比度及亮度，相应公式：
	//g_dstImage(i,j) = a * g_srcImage(i,j) + b
	//a：用来控制对比度
	//b：用来控制亮度
	for (int y = 0; y < g_srcImage.rows; y++)
		for (int x = 0; x < g_srcImage.cols; x++)
			for (int c = 0; c < 3; c++)
				g_dstImage.at<Vec3b>(y, x)[c] = saturate_cast<uchar>((g_nContrastValue*0.01)*(g_srcImage.at<Vec3b>(y, x)[c]) + g_nBrightValue);
	//g_dstImage.at<Vec3b>(y, x)[c]表示dst图像中y行x列，c为RGB（0，1，2）其中之一
	//saturate_cast<uchar>转换结果防止超出像素取值范围
	//对比度取值为0.0~3.0，轨迹条取整数，故使用g_nContrastValue*0.01确保对比度处于范围内

	imshow("girl", g_srcImage);
	imshow("girl666", g_dstImage);
	
}
int main()
{
	g_srcImage = imread("girl.jpg");
	if (!g_srcImage.data) {
		printf("fxxk!~ read failed!  \n");
		return false;
	}

	g_srcImage.copyTo(g_dstImage);
	//设初值
	g_nContrastValue = 80;
	g_nBrightValue = 80;

	namedWindow("girl666", 1);
	
	createTrackbar("对比度：", "girl666", &g_nContrastValue, 300, ContrastAndBright);
	createTrackbar("亮  度：", "girl666", &g_nBrightValue, 200, ContrastAndBright);
	
	ContrastAndBright(g_nContrastValue, 0);
	ContrastAndBright(g_nBrightValue, 0);

	printf("按下Q键，程序退出！~~");

	while(char(waitKey(1))!='q'){}

    return 0;
}

