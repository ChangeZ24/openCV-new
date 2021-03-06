// Ex12-dilate_erosion.cpp: 膨胀与腐蚀
//

#include "stdafx.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

Mat g_srcImage, g_dstImage;
int g_nTrackbarNumber = 0;//0表示腐蚀erode，1表示膨胀dilate
int g_nStructElementSize = 3;//结构元素（内核矩阵）的尺寸

void Process() {
	//获取自定义核
	Mat element = getStructuringElement(MORPH_RECT, Size(2 * g_nStructElementSize + 1, 2 * g_nStructElementSize + 1), Point(g_nStructElementSize, g_nStructElementSize));
	//进行腐蚀或膨胀操作
	if (g_nTrackbarNumber == 0)
		erode(g_srcImage, g_dstImage, element);
	else
		dilate(g_srcImage, g_dstImage, element);
	imshow("girl666", g_dstImage);
}
//回调函数
void on_TrackbarNumChange(int, void*) {
	Process();
}
void on_ElementSizeChange(int, void*) {
	Process();
}

int main(){
	g_srcImage = imread("girl.jpg");
	if (!g_srcImage.data) {
		printf("fxxk!~read failed!!\n");
		return false;
	}
	namedWindow("girl");
	namedWindow("girl666");

	imshow("girl", g_srcImage);
	//获取自定义核
	Mat element = getStructuringElement(MORPH_RECT, Size(2*g_nStructElementSize+1, 2*g_nStructElementSize+1),Point(g_nStructElementSize,g_nStructElementSize));

	erode(g_srcImage, g_dstImage, element);
	imshow("girl666", g_dstImage);
	//创建轨迹条
	createTrackbar("腐蚀/膨胀", "girl666", &g_nTrackbarNumber, 1, on_TrackbarNumChange);
	createTrackbar("内核尺寸", "girl666", &g_nStructElementSize, 21, on_ElementSizeChange);

	waitKey(0);
    return 0;
}

