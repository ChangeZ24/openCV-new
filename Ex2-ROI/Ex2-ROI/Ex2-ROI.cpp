// Ex2-ROI.cpp: 利用感兴趣区域ROI实现图像叠加及线性图像混合
//
#include "stdafx.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace cv;

//利用感兴趣区域ROI实现图像叠加
bool ROI_AddImage(){
	Mat srcImage1 = imread("dota.jpg");
	Mat logoImage = imread("logo.jpg");
	if (!srcImage1.data) {
		printf("fxxk!~ read failed! \n");
		return false;
	}
	if (!logoImage.data) {
		printf("fxxk!~ read failed! \n");
		return false;
	}

	Mat imageROI = srcImage1(Rect(0, 0, logoImage.cols, logoImage.rows));

	//加载掩模
	Mat mask = imread("logo.jpg",0);

	//将掩模copy到ROI
	logoImage.copyTo(imageROI, mask);

	namedWindow("dota666");
	imshow("dota666",srcImage1);
	
    
	return true;
}
//利用addWeighted()实现图像线性混合
bool LinearBlending() {
	double alpha = 0.5;
	double beta;
	Mat srcImage2, srcImage3, dstImage;
	
	srcImage2 = imread("dota1.jpg");
	srcImage3 = imread("rain.jpg");
	if (!srcImage2.data) {
		printf("fxxk!~ read failed! \n");
		return false;
	}
	if (!srcImage3.data) {
		printf("fxxk!~ read failed! \n");
		return false;
	}

	//图像混合加权
	beta = (1.0 - alpha);
	addWeighted(srcImage2, alpha, srcImage3, beta, 0.0, dstImage);

	//显示原图
	namedWindow("yeah_dota", 1);
	imshow("yeah_dota", srcImage2);

	//显示混合
	namedWindow("dotahhh", 1);
	imshow("dotahhh", dstImage);
	
	return true;
}
//指定区域进行线性混合
bool ROI_LinerarBlending() {
	Mat srcImage4 = imread("dota.jpg");
	Mat logoImage = imread("logo.jpg");
	if (!srcImage4.data) {
		printf("fxxk!~ read failed! \n");
		return false;
	}
	if (!logoImage.data) {
		printf("fxxk!~ read failed! \n");
		return false;
	}

	Mat imageROI = srcImage4(Rect(0, 0, logoImage.cols, logoImage.rows));

	addWeighted(imageROI, 0.5, logoImage, 0.3, 0., imageROI);

	namedWindow("dotawww");
	imshow("dotawww", srcImage4);
	

	return true;
}
int main() {
	system("color 5E");
	if (ROI_AddImage() && LinearBlending() && ROI_LinerarBlending())
		printf("YES! \n");
	waitKey(0);
	
	return 0;
}

