// Ex13-operation_hat_gradient.cpp: 开、闭运算、顶帽、黑帽、形态学梯度
//

#include "stdafx.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

Mat g_srcImage, g_dstImage;
int g_nElementShape = MORPH_RECT;//元素结构的形状
//变量接收的Trackbar位置参数
int g_nMaxIterationNum = 10;
int g_nOpenCloseNum = 0;
int g_nErodeDilateNum = 0;
int g_nTopBlackHatNum = 0;
//回调函数
static void on_OpenClose(int, void*) {
	int offset = g_nOpenCloseNum - g_nMaxIterationNum;//偏移量
	int Absolute_offset = offset > 0 ? offset : -offset;//偏移量绝对值
	//自定义核
	Mat element = getStructuringElement(g_nElementShape, Size(Absolute_offset * 2 + 1, Absolute_offset * 2 + 1), Point(Absolute_offset, Absolute_offset));
	//offset<0进行开运算，否则闭运算
	if (offset < 0)
		morphologyEx(g_srcImage, g_dstImage, CV_MOP_OPEN, element);
	else
		morphologyEx(g_srcImage, g_dstImage, CV_MOP_CLOSE, element);

	imshow("boy_operation", g_dstImage);
}
static void on_ErodeDilate(int, void*) {
	int offset = g_nOpenCloseNum - g_nMaxIterationNum;//偏移量
	int Absolute_offset = offset > 0 ? offset : -offset;//偏移量绝对值
														//自定义核
	Mat element = getStructuringElement(g_nElementShape, Size(Absolute_offset * 2 + 1, Absolute_offset * 2 + 1), Point(Absolute_offset, Absolute_offset));
	//offset<0进行腐蚀，否则膨胀
	if (offset < 0)
		erode(g_srcImage, g_dstImage, element);
	else
		dilate(g_srcImage, g_dstImage, element);

	imshow("boy_erode&dilate", g_dstImage);
}
static void on_TopBlackHat(int, void*) {
	int offset = g_nOpenCloseNum - g_nMaxIterationNum;//偏移量
	int Absolute_offset = offset > 0 ? offset : -offset;//偏移量绝对值
														//自定义核
	Mat element = getStructuringElement(g_nElementShape, Size(Absolute_offset * 2 + 1, Absolute_offset * 2 + 1), Point(Absolute_offset, Absolute_offset));
	//offset<0进行顶帽，否则黑帽
	if (offset < 0)
		morphologyEx(g_srcImage, g_dstImage, MORPH_TOPHAT, element);
	else
		morphologyEx(g_srcImage, g_dstImage, MORPH_BLACKHAT, element);

	imshow("boy_hat", g_dstImage);
}
//帮助文字显示
static void ShowHelpText() {
	printf("\n\n\n\t请调整滚动条观察图像效果~\n\n");
	printf("\n\n\t按键操作说明: \n\n"
		"\t\t键盘按键【ESC】或者【Q】- 退出程序\n"
		"\t\t键盘按键【1】- 使用椭圆(Elliptic)结构元素\n"
		"\t\t键盘按键【2】- 使用矩形(Rectangle )结构元素\n"
		"\t\t键盘按键【3】- 使用十字型(Cross-shaped)结构元素\n"
		"\t\t键盘按键【空格SPACE】- 在矩形、椭圆、十字形结构元素中循环\n"
	);
}
int main(){
	ShowHelpText();
	
	g_srcImage = imread("boy1.jpg");
	if (!g_srcImage.data) {
		printf("fxxk!~~read failed!!\n");
		return false;
	}
	
	namedWindow("boy");
	namedWindow("boy_operation");
	namedWindow("boy_erode&dilate");
	namedWindow("boy_hat");

	imshow("boy", g_srcImage);
	//参数赋值
	g_nOpenCloseNum = 9;
	g_nErodeDilateNum = 9;
	g_nTopBlackHatNum = 2;
	//创建轨迹条
	createTrackbar("迭代值", "boy_operation", &g_nOpenCloseNum, g_nMaxIterationNum * 2 + 1, on_OpenClose);
	createTrackbar("迭代值", "boy_erode&dilate", &g_nErodeDilateNum, g_nMaxIterationNum * 2 + 1, on_ErodeDilate);
	createTrackbar("迭代值", "boy_hat", &g_nTopBlackHatNum, g_nMaxIterationNum * 2 + 1, on_TopBlackHat);
	//获取按键信息
	while (1) {
		int c;

		on_OpenClose(g_nOpenCloseNum, 0);
		on_ErodeDilate(g_nErodeDilateNum, 0);
		on_TopBlackHat(g_nTopBlackHatNum, 0);

		c = waitKey(0);

		if ((char)c == 'q' || (char)c == 27)
			break;
		if ((char)c == 49)//按键1使用椭圆结构元素，ASII码为49
			g_nElementShape = MORPH_ELLIPSE;
		else if ((char)c == 50)//按键2使用矩形结构元素，ASII码为50
			g_nElementShape = MORPH_RECT;
		else if ((char)c == 51)//按键3使用十字形结构元素，ASII码为51
			g_nElementShape = MORPH_CROSS;
		else if ((char)c == ' ')//按键space，在三种结构元素中循环
			g_nElementShape = (g_nElementShape + 1) % 3;
	}

    return 0;
}

