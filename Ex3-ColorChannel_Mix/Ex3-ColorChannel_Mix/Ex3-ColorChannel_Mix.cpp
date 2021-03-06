// Ex3-ColorChannel_Mix.cpp: 颜色通道及多通道混合
//
#include "stdafx.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

bool MultiChannelBLending() {
	/*---------------------------------蓝色通道---------------------------------*/

	Mat srcImage;
	Mat logoImage;
	Mat imageBlueChannel;
	vector<Mat> channels;

	srcImage = imread("dota.jpg");
	logoImage = imread("logo.jpg", 0);
	if (!srcImage.data) {
		printf("fxxk!~ read failed! \n");
		return false;
	}
	if (!logoImage.data) {
		printf("fxxk!~ read failed! \n");
		return false;
	}
	//将3通道图像转换为3个单通道图像
	split(srcImage, channels);
	//原图蓝色通道引用返回给imageBlueChannel
	imageBlueChannel = channels.at(0);

	//将原图蓝色通道的一块区域和logo图进行加权混合并存入imageBlueChannel中
	addWeighted(imageBlueChannel(Rect(0, 0, logoImage.cols, logoImage.rows)), 1.0, logoImage, 0.5, 0., imageBlueChannel(Rect(0, 0, logoImage.cols, logoImage.rows)));

	//将3个单通道重新合并
	merge(channels, srcImage);

	namedWindow("dotaBlue666");
	imshow("dotaBlue666", srcImage);

	/*---------------------------------绿色通道---------------------------------*/

	Mat imageGreenChannel;
	srcImage = imread("dota.jpg");
	logoImage = imread("logo.jpg", 0);
	if (!srcImage.data) {
		printf("fxxk!~ read failed! \n");
		return false;
	}
	if (!logoImage.data) {
		printf("fxxk!~ read failed! \n");
		return false;
	}
	//将3通道图像转换为3个单通道图像
	split(srcImage, channels);
	//原图绿色通道引用返回给imageGreenChannel
	imageGreenChannel = channels.at(1);

	//将原图绿色通道的一块区域和logo图进行加权混合并存入imageGreenChannel中
	addWeighted(imageGreenChannel(Rect(0, 0, logoImage.cols, logoImage.rows)), 1.0, logoImage, 0.5, 0., imageGreenChannel(Rect(0, 0, logoImage.cols, logoImage.rows)));

	//将3个单通道重新合并
	merge(channels, srcImage);

	namedWindow("dotaGreen666");
	imshow("dotaGreen666", srcImage);

	/*---------------------------------红色通道---------------------------------*/

	Mat imageRedChannel;
	srcImage = imread("dota.jpg");
	logoImage = imread("logo.jpg", 0);
	if (!srcImage.data) {
		printf("fxxk!~ read failed! \n");
		return false;
	}
	if (!logoImage.data) {
		printf("fxxk!~ read failed! \n");
		return false;
	}
	//将3通道图像转换为3个单通道图像
	split(srcImage, channels);
	//原图红色通道引用返回给imageRedChannel
	imageRedChannel = channels.at(2);

	//将原图红色通道的一块区域和logo图进行加权混合并存入imageRedChannel中
	addWeighted(imageRedChannel(Rect(0, 0, logoImage.cols, logoImage.rows)), 1.0, logoImage, 0.5, 0., imageRedChannel(Rect(0, 0, logoImage.cols, logoImage.rows)));

	//将3个单通道重新合并
	merge(channels, srcImage);

	namedWindow("dotaRed666");
	imshow("dotaRed666", srcImage);

	return true;
}
int main()
{
	system("color 5E");
	if (MultiChannelBLending())
		printf("Yes!~\n");

	waitKey(0);
    return 0;
}

