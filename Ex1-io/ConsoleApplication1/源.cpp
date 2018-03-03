#include "stdafx.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace cv;

int main() {
	//图像载入与显示
	Mat girl = imread("pic.jpg");
	namedWindow("女神");
	imshow("女神",girl);
	//初级图像混合
	Mat image = imread("dota.jpg");
	Mat logo = imread("logo.jpg");

	namedWindow("原画");
	imshow("原画", image);

	namedWindow("logo");
	imshow("logo", logo);

	Mat imageROI;//存放图像的ROI
	imageROI = image(Rect(800, 350, logo.cols, logo.rows));//方法1
	//方法2
	//imageROI = image(Range(350, 350+logo.rows), Range(800, 800+logo.cols))
	
	addWeighted(imageROI, 0.5, logo, 0.3, 0., imageROI);//把logo加在原画上

	namedWindow("最终");
	imshow("最终", image);

	//图像输出
	imwrite("dota666.jpg", image);

	waitKey();

	return 0;

}