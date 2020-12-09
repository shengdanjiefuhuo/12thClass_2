#include <opencv2/opencv.hpp>  
#include<iostream>  
#include"time.h"  
#include<vector>  
#include<map>  

using namespace std;
using namespace cv;

int main()
{
	Mat srcImage, dstImage;
	srcImage = imread("C:/Users/hp/Desktop/5.jpg", IMREAD_GRAYSCALE);
	imshow("【原图】", srcImage);

	/* 调本地彩色图片时用
	   Mat src_gray;
	   cvtColor(srcImage, src_gray, COLOR_BGR2GRAY);
	   imshow("【灰度图】", src_gray);
	*/
	//需要计算图像的哪个通道（bgr空间需要确定计算 b或g或r空间）    
	const int channels[1] = { 0 };
	//直方图的每一个维度的 柱条的数目（就是将灰度级分组）  
	int histSize[] = { 256 };   //如果这里写成int histSize = 256; 那么下面调用计算直方图的函数的时候，该变量需要写 &histSize  
		 //定义一个变量用来存储 单个维度 的数值的取值范围    
	float midRanges[] = { 0, 256 };
	//确定每个维度的取值范围，就是横坐标的总数    
	const float *ranges[] = { midRanges };
	//输出的结果存储的 空间 ，用MatND类型来存储结果  MatND表示多为矩阵在opencv2.2后统一用Mat
	MatND dstHist;
	calcHist(&srcImage, 1, channels, Mat(), dstHist, 1, histSize, ranges, true, false);
	//calcHist  函数调用结束后，dstHist变量中将储存了 直方图的信息  用dstHist的模版函数 at<Type>(i)得到第i个柱条的值  at<Type>(i, j)得到第i个并且第j个柱条的值    

	//首先先创建一个黑底的图像，为了可以显示彩色，所以该绘制图像是一个8位的3通道图像    
	Mat drawImage = Mat::zeros(Size(300, 256), CV_8UC3);
	//一个图像的某个灰度级的像素个数（最多为图像像素总数），可能会超过显示直方图的所定义的图像的尺寸，因此绘制直方图的时候，让直方图最高的地方只有图像高度的90%来显示  

	//先用minMaxLoc函数来得到计算直方图后的像素的最大个数    
	double g_dHistMaxValue;
	minMaxLoc(dstHist, 0, &g_dHistMaxValue, 0, 0);

	//遍历直方图得到的数据    
	for (int i = 0; i < 256; i++)
	{
		int value = cvRound(256 * 0.9 *(dstHist.at<float>(i) / g_dHistMaxValue));

		line(drawImage, Point(i, drawImage.rows - 1), Point(i, drawImage.rows - 1 - value), Scalar(255, 0, 0));
	}

	imshow("【原图像的直方图】", drawImage);


	//*****直方图均衡化
	equalizeHist(srcImage, dstImage); //直方图均衡化

	imwrite("C:/Users/hp/Desktop/5_1.jpg", dstImage);//图片保存到本工程目录中

	String windowNameHist = "【直方图均衡化后图像】";
	namedWindow(windowNameHist, WINDOW_AUTOSIZE); //显示图像 imshow(windowNameSrc, srcImage);
	imshow(windowNameHist, dstImage); //显示直方图均衡化后图像


	const int channels1[1] = { 0 };

	//直方图的每一个维度的 柱条的数目（就是将灰度级分组）  
	int histSize1[] = { 256 };

	//定义一个变量用来存储 单个维度 的数值的取值范围    
	float midRanges1[] = { 0, 256 };

	//确定每个维度的取值范围，就是横坐标的总数    
	const float *ranges1[] = { midRanges1 };

	//输出的结果存储的 空间 ，用MatND类型来存储结果  
	MatND dstHist1;
	calcHist(&dstImage, 1, channels1, Mat(), dstHist1, 1, histSize1, ranges1, true, false);
	//calcHist  函数调用结束后，dstHist变量中将储存了 直方图的信息  用dstHist的模版函数 at<Type>(i)得到第i个柱条的值  at<Type>(i, j)得到第i个并且第j个柱条的值    

	//首先先创建一个黑底的图像，绘制图像是一个8位的3通道图像，可以显示彩色图像  直方图
	Mat drawImage2 = Mat::zeros(Size(300, 256), CV_8UC3);//彩色直方图
	//Mat drawImage2 = Mat::zeros(Size(256, 256), CV_8UC1);//单通道灰度直方图

	//先用minMaxLoc函数来得到计算直方图后的像素的最大个数    
	double g_dHistMaxValue1;
	minMaxLoc(dstHist1, 0, &g_dHistMaxValue1, 0, 0);

	//遍历直方图得到的数据    
	for (int i = 0; i < 256; i++)
	{
		int value = cvRound(256 * 0.9 *(dstHist1.at<float>(i) / g_dHistMaxValue1));

		line(drawImage2, Point(i, drawImage2.rows - 1), Point(i, drawImage2.rows - 1 - value), Scalar(255, 0, 0));//直方图颜色Scalar和背景色相加
	}

	String w = "均衡化后图像的直方图";
	namedWindow(w, WINDOW_AUTOSIZE);
	imshow(w, drawImage2);


	Mat SecImage, Image2;
	SecImage = imread("C:/Users/hp/Desktop/5.jpg", IMREAD_GRAYSCALE);	waitKey(0);

	return 0;
}