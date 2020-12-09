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
	imshow("��ԭͼ��", srcImage);

	/* �����ز�ɫͼƬʱ��
	   Mat src_gray;
	   cvtColor(srcImage, src_gray, COLOR_BGR2GRAY);
	   imshow("���Ҷ�ͼ��", src_gray);
	*/
	//��Ҫ����ͼ����ĸ�ͨ����bgr�ռ���Ҫȷ������ b��g��r�ռ䣩    
	const int channels[1] = { 0 };
	//ֱ��ͼ��ÿһ��ά�ȵ� ��������Ŀ�����ǽ��Ҷȼ����飩  
	int histSize[] = { 256 };   //�������д��int histSize = 256; ��ô������ü���ֱ��ͼ�ĺ�����ʱ�򣬸ñ�����Ҫд &histSize  
		 //����һ�����������洢 ����ά�� ����ֵ��ȡֵ��Χ    
	float midRanges[] = { 0, 256 };
	//ȷ��ÿ��ά�ȵ�ȡֵ��Χ�����Ǻ����������    
	const float *ranges[] = { midRanges };
	//����Ľ���洢�� �ռ� ����MatND�������洢���  MatND��ʾ��Ϊ������opencv2.2��ͳһ��Mat
	MatND dstHist;
	calcHist(&srcImage, 1, channels, Mat(), dstHist, 1, histSize, ranges, true, false);
	//calcHist  �������ý�����dstHist�����н������� ֱ��ͼ����Ϣ  ��dstHist��ģ�溯�� at<Type>(i)�õ���i��������ֵ  at<Type>(i, j)�õ���i�����ҵ�j��������ֵ    

	//�����ȴ���һ���ڵ׵�ͼ��Ϊ�˿�����ʾ��ɫ�����Ըû���ͼ����һ��8λ��3ͨ��ͼ��    
	Mat drawImage = Mat::zeros(Size(300, 256), CV_8UC3);
	//һ��ͼ���ĳ���Ҷȼ������ظ��������Ϊͼ�����������������ܻᳬ����ʾֱ��ͼ���������ͼ��ĳߴ磬��˻���ֱ��ͼ��ʱ����ֱ��ͼ��ߵĵط�ֻ��ͼ��߶ȵ�90%����ʾ  

	//����minMaxLoc�������õ�����ֱ��ͼ������ص�������    
	double g_dHistMaxValue;
	minMaxLoc(dstHist, 0, &g_dHistMaxValue, 0, 0);

	//����ֱ��ͼ�õ�������    
	for (int i = 0; i < 256; i++)
	{
		int value = cvRound(256 * 0.9 *(dstHist.at<float>(i) / g_dHistMaxValue));

		line(drawImage, Point(i, drawImage.rows - 1), Point(i, drawImage.rows - 1 - value), Scalar(255, 0, 0));
	}

	imshow("��ԭͼ���ֱ��ͼ��", drawImage);


	//*****ֱ��ͼ���⻯
	equalizeHist(srcImage, dstImage); //ֱ��ͼ���⻯

	imwrite("C:/Users/hp/Desktop/5_1.jpg", dstImage);//ͼƬ���浽������Ŀ¼��

	String windowNameHist = "��ֱ��ͼ���⻯��ͼ��";
	namedWindow(windowNameHist, WINDOW_AUTOSIZE); //��ʾͼ�� imshow(windowNameSrc, srcImage);
	imshow(windowNameHist, dstImage); //��ʾֱ��ͼ���⻯��ͼ��


	const int channels1[1] = { 0 };

	//ֱ��ͼ��ÿһ��ά�ȵ� ��������Ŀ�����ǽ��Ҷȼ����飩  
	int histSize1[] = { 256 };

	//����һ�����������洢 ����ά�� ����ֵ��ȡֵ��Χ    
	float midRanges1[] = { 0, 256 };

	//ȷ��ÿ��ά�ȵ�ȡֵ��Χ�����Ǻ����������    
	const float *ranges1[] = { midRanges1 };

	//����Ľ���洢�� �ռ� ����MatND�������洢���  
	MatND dstHist1;
	calcHist(&dstImage, 1, channels1, Mat(), dstHist1, 1, histSize1, ranges1, true, false);
	//calcHist  �������ý�����dstHist�����н������� ֱ��ͼ����Ϣ  ��dstHist��ģ�溯�� at<Type>(i)�õ���i��������ֵ  at<Type>(i, j)�õ���i�����ҵ�j��������ֵ    

	//�����ȴ���һ���ڵ׵�ͼ�񣬻���ͼ����һ��8λ��3ͨ��ͼ�񣬿�����ʾ��ɫͼ��  ֱ��ͼ
	Mat drawImage2 = Mat::zeros(Size(300, 256), CV_8UC3);//��ɫֱ��ͼ
	//Mat drawImage2 = Mat::zeros(Size(256, 256), CV_8UC1);//��ͨ���Ҷ�ֱ��ͼ

	//����minMaxLoc�������õ�����ֱ��ͼ������ص�������    
	double g_dHistMaxValue1;
	minMaxLoc(dstHist1, 0, &g_dHistMaxValue1, 0, 0);

	//����ֱ��ͼ�õ�������    
	for (int i = 0; i < 256; i++)
	{
		int value = cvRound(256 * 0.9 *(dstHist1.at<float>(i) / g_dHistMaxValue1));

		line(drawImage2, Point(i, drawImage2.rows - 1), Point(i, drawImage2.rows - 1 - value), Scalar(255, 0, 0));//ֱ��ͼ��ɫScalar�ͱ���ɫ���
	}

	String w = "���⻯��ͼ���ֱ��ͼ";
	namedWindow(w, WINDOW_AUTOSIZE);
	imshow(w, drawImage2);


	Mat SecImage, Image2;
	SecImage = imread("C:/Users/hp/Desktop/5.jpg", IMREAD_GRAYSCALE);	waitKey(0);

	return 0;
}