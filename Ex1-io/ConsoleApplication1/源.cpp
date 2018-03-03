#include "stdafx.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace cv;

int main() {
	//ͼ����������ʾ
	Mat girl = imread("pic.jpg");
	namedWindow("Ů��");
	imshow("Ů��",girl);
	//����ͼ����
	Mat image = imread("dota.jpg");
	Mat logo = imread("logo.jpg");

	namedWindow("ԭ��");
	imshow("ԭ��", image);

	namedWindow("logo");
	imshow("logo", logo);

	Mat imageROI;//���ͼ���ROI
	imageROI = image(Rect(800, 350, logo.cols, logo.rows));//����1
	//����2
	//imageROI = image(Range(350, 350+logo.rows), Range(800, 800+logo.cols))
	
	addWeighted(imageROI, 0.5, logo, 0.3, 0., imageROI);//��logo����ԭ����

	namedWindow("����");
	imshow("����", image);

	//ͼ�����
	imwrite("dota666.jpg", image);

	waitKey();

	return 0;

}