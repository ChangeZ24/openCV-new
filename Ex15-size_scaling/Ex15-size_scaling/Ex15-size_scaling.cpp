// Ex15-size_scaling.cpp: 高斯金字塔、拉普拉斯金字塔及图片缩放
//

#include "stdafx.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

Mat g_srcImage, g_dstImage, g_tmpImage;
static void ShowHelpText() {
	printf("\n\n\n\t欢迎来到OpenCV图像金字塔和resize示例程序~\n\n");
	printf("\n\n\t按键操作说明: \n\n"
		"\t\t键盘按键【ESC】或者【Q】- 退出程序\n"
		"\t\t键盘按键【1】或者【W】- 进行基于【resize】函数的图片放大\n"
		"\t\t键盘按键【2】或者【S】- 进行基于【resize】函数的图片缩小\n"
		"\t\t键盘按键【3】或者【A】- 进行基于【pyrUp】函数的图片放大\n"
		"\t\t键盘按键【4】或者【D】- 进行基于【pyrDown】函数的图片缩小\n"
		
	);
}
int main(){
	system("color 2F");
	ShowHelpText();
	g_srcImage = imread("boy1.jpg");
	if (!g_srcImage.data) {
		printf("fxxk!~read failed!!\n");
		return false;
	}
	namedWindow("BOY", CV_WINDOW_AUTOSIZE);
	imshow("BOY", g_srcImage);
	g_tmpImage = g_srcImage;
	g_dstImage = g_tmpImage;
	int key = 0;
	while (1) {
		key = waitKey(9);
		switch (key) {
		case 27://ESC
			return 0;
			break;
		case 'q':
			return 0;
			break;
		case 'a':
			pyrUp(g_tmpImage, g_dstImage, Size(g_tmpImage.cols * 2, g_tmpImage.rows * 2));
			printf("选择“A”，开始进行基于pyrup函数的图片放大，尺寸x2\n");
			break;
		case 'w':
			resize(g_tmpImage, g_dstImage, Size(g_tmpImage.cols * 2, g_tmpImage.rows * 2));
			printf("选择“W”，开始进行基于resize函数的图片放大，尺寸x2\n");
			break;
		case '1':
			resize(g_tmpImage, g_dstImage, Size(g_tmpImage.cols * 2, g_tmpImage.rows * 2));
			printf("选择“1”，开始进行基于resize函数的图片放大，尺寸x2\n");
			break;
		case '3':
			pyrUp(g_tmpImage, g_dstImage, Size(g_tmpImage.cols * 2, g_tmpImage.rows * 2));
			printf("选择“3”，开始进行基于pyrup函数的图片放大，尺寸x2\n");
			break;
		case 'd':
			pyrDown(g_tmpImage, g_dstImage, Size(g_tmpImage.cols / 2, g_tmpImage.rows / 2));
			printf("选择“d”，开始进行基于pyrdown函数的图片缩小，尺寸/2\n");
			break;
		case 's':
			resize(g_tmpImage, g_dstImage, Size(g_tmpImage.cols / 2, g_tmpImage.rows / 2));
			printf("选择“s”，开始进行基于resize函数的图片缩小，尺寸/2\n");
			break;
		case '4':
			pyrDown(g_tmpImage, g_dstImage, Size(g_tmpImage.cols / 2, g_tmpImage.rows / 2));
			printf("选择“4”，开始进行基于pyrdown函数的图片缩小，尺寸/2\n");
			break;
		case '2':
			resize(g_tmpImage, g_dstImage, Size(g_tmpImage.cols / 2, g_tmpImage.rows / 2));
			printf("选择“2”，开始进行基于resize函数的图片缩小，尺寸/2\n");
			break;

		}
		imshow("BOY", g_dstImage);
		g_tmpImage = g_dstImage;
	}
	
    return 0;
}

