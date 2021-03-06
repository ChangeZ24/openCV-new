// Ex17-floodfill.cpp:漫水填充操作
//

#include "stdafx.h"
#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;

Mat g_srcImage, g_dstImage, g_grayImage, g_maskImage;
int g_nFillMode = 1;//漫水填充模式
int g_nLowDifference = 20, g_nUpDifference = 20;//负差最大值，正差最大值
int g_nConnectivity = 4;//floodFill函数标识符第八位的连通值
int g_bIsColor = true;//是否为彩色图的标识符布尔值    ///////////////////////////
bool g_bUseMask = false;//是否显示掩模窗口的布尔值
int g_nNewMaskVal = 255;//新的重新绘制的像素值

static void ShowHelpText() {
	printf("\t\t鼠标点击图中区域进行漫水填充操作\n");
	printf("\t\t键盘按键‘ESC’，退出程序\n");
	printf("\t\t键盘按键‘1’，切换彩色图/灰度图\n");
	printf("\t\t键盘按键‘2’，显示/隐藏掩模窗口\n");
	printf("\t\t键盘按键‘3’，恢复原始图像\n");
	printf("\t\t键盘按键‘4’，使用空范围的漫水填充\n");
	printf("\t\t键盘按键‘5’，使用渐变、固定范围的漫水填充\n");
	printf("\t\t键盘按键‘6’，使用渐变、浮动范围的漫水填充\n");
	printf("\t\t键盘按键‘7’，操作标识符的第八位使用4位的连接模式\n");
	printf("\t\t键盘按键‘8’，操作标识符的第八位使用8位的连接模式\n");
}
static void onMouse(int event, int x, int y, int, void *) {
	//没有点击鼠标左键则返回
	if(event != CV_EVENT_LBUTTONDOWN)
		return;
	//准备FloodFill函数参数部分
	Point seed = Point(x, y);
	//空范围的漫水填充，此值设为0，否则为全局g_nLowDifference
	int LowDifference = g_nFillMode == 0 ? 0 : g_nLowDifference;
	//空范围的漫水填充，此值设为0，否则为全局g_nUpDifference
	int UpDifference = g_nFillMode == 0 ? 0 : g_nUpDifference;
	//标识符的0~7位位g_nConnectivity,8~15位为g_NewMaskVal左移8位的值，16~23位为CV_FLOODFILL_FIXED_RANGE或者0
	int flags = g_nConnectivity + (g_nNewMaskVal << 8) + (g_nFillMode == 1 ? CV_FLOODFILL_FIXED_RANGE : 0);
	//随机生成bgr
	int b = (unsigned)theRNG() & 255;
	int g = (unsigned)theRNG() & 255;
	int r = (unsigned)theRNG() & 255;
	Rect ccomp;
	//彩色图模式，取Scalar(b,g,r)，灰度图模式取Scalar(r+0.299+g*0.587+b*0.144)
	Scalar newVal = g_bIsColor ? Scalar(b, g, r) : Scalar(r * 0.299 +g * 0.587 + b * 0.144);
	Mat dst = g_bIsColor ? g_dstImage : g_grayImage;
	int area;
	//漫水填充
	if (g_bUseMask) {
		threshold(g_maskImage, g_maskImage, 1, 128, CV_THRESH_BINARY);
		area = floodFill(dst, g_maskImage, seed, newVal, &ccomp, Scalar(LowDifference, LowDifference, LowDifference),Scalar(UpDifference,UpDifference,UpDifference),flags);
		imshow("mask", g_maskImage);
	}
	else {
		area = floodFill(dst, seed, newVal, &ccomp, Scalar(LowDifference, LowDifference, LowDifference), Scalar(UpDifference, UpDifference, UpDifference), flags);
	}
	imshow("final", dst);
	cout << area << "个像素被重绘" << endl;
}
int main(int argc,char ** argv){
	system("color 2F");
	g_srcImage = imread("girl1.jpg", 1);
	if (!g_srcImage.data)
		cout << "fxxk!!!!read failed!!" << endl;
	ShowHelpText();
	//转化灰度图并初始化掩模mask
	g_srcImage.copyTo(g_dstImage);
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
	g_maskImage.create(g_srcImage.rows+2, g_srcImage.cols+2, CV_8UC1);
	namedWindow("final", CV_WINDOW_AUTOSIZE);

	createTrackbar("负差最大值", "final", &g_nLowDifference, 255, 0);
	createTrackbar("正差最大值", "final", &g_nUpDifference, 255, 0);

	setMouseCallback("final", onMouse, 0);
	while (1) {
		imshow("final", g_bIsColor ? g_dstImage : g_grayImage);

		int c = waitKey(0);
		if ((c & 255) == 27) {
			cout << "quit!!!" << endl;
			break;
		}
		switch ((char)c) {
		case '1':
			if (g_bIsColor) {//原来为彩色图，将其转化为灰度图，并将mask所有元素设置为0
				cout << "选择1，将彩色图切换为灰度图" << endl;
				cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
				g_maskImage = Scalar::all(0);//mask所有元素设为0
				g_bIsColor = false;//标识符设为false,表示当前不是彩色图，是灰度图
			}
			else {//原来为灰度图，将彩图再次copy给image，并且将mask所有元素设置为0
				cout << "选择1，将灰度图切换为彩色图" << endl;
				g_srcImage.copyTo(g_dstImage);
				g_maskImage = Scalar::all(0);
				g_bIsColor = true;//标识符设为true，表示当前为彩图
			}
			break;
		case '2':
			if (g_bUseMask) {
				destroyWindow("mask");
				g_bUseMask = false;
			}
			else {
				namedWindow("mask", 0);
				g_maskImage = Scalar::all(0);
				imshow("mask", g_maskImage);
				g_bUseMask = true;
			}
			break;
		case '3':
			cout << "选择3，恢复原始图像" << endl;
			g_srcImage.copyTo(g_dstImage);
			cvtColor(g_dstImage, g_grayImage, COLOR_BGR2GRAY);
			g_maskImage = Scalar::all(0);
			break;
		case '4':
			cout << "选择4，使用空范围的漫水填充" << endl;
			g_nFillMode = 0;
			break;
		case '5':
			cout << "选择5，使用渐变、固定范围的漫水填充" << endl;
			g_nFillMode = 1;
			break;
		case '6':
			cout << "选择6，使用渐变、浮动范围的漫水填充" << endl;
			g_nFillMode = 2;
		case '7':
			cout << "选择7，操作标识符的低八位使用4位的连接模式" << endl;
			g_nConnectivity = 4;
			break;
		case '8':
			cout << "选择8，操作标识符的低八位使用8位的连接模式" << endl;
			g_nConnectivity = 8;
			break;
		}
	}

	return 0;
}

