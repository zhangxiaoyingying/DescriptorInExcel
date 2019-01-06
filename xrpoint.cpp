/*****************************************************/
/*              SiftTest图像定位测试程序            */
/****************************************************/

#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include "opencv2/core/core.hpp"//因为在属性中已经配置了opencv等目录，所以把其当成了本地目录一样
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/nonfree.hpp" 
#include "windows.h"
#include "opencv2/legacy/legacy.hpp"
#include <fstream>

using namespace cv;
using namespace std;

//设置采样块的步长
const int StepSize = 50;

ofstream outfile;




/************************************************************************/
/*		test_at():测试遍历读取Mat矩阵元素                                                                     */
/************************************************************************/
void InitMat(Mat& m,float t)
{
	for(int i=0;i<m.rows;i++)
		for(int j=0;j<m.cols;j++)
			m.at<float>(i,j)=i+j;
}
void test_at()
{
	//Mat矩阵中的初始化，可以利用Mat：：at()来完成
	///*			①数字测试，at遍历方式ok			*/
	Mat M01(1000,1000,CV_32F);
	InitMat(M01,3);

	/*	②图像Mat测试，不行。	*/
	Mat M0 = imread("C:\\Users\\ZY\\Desktop\\0103\\1_S.jpg");	//大图


	/*		③描述子Mat测试，ok */
	Mat img1 = imread("C:\\Users\\ZY\\Desktop\\0103\\1_S.jpg");	//大图

	int minHessian=5000;
	SurfFeatureDetector detector1(minHessian);
	Ptr<DescriptorExtractor> descriptor_extractor = DescriptorExtractor::create("SURF");
	Mat descriptors_M0;
	//特征点检测			
	vector <KeyPoint> m_LeftKey,m_LeftKey1;		//特征点
	detector1.detect(img1,m_LeftKey);
	descriptor_extractor->compute(img1,m_LeftKey,descriptors_M0);

	ofstream outFile1,outFile2;//创建对象
	outFile1.open("C:\\Users\\ZY\\Desktop\\0105\\descriptor1.txt");//打开文本

	//使用at，遍历核心代码
	for (int i=0;i<descriptors_M0.rows;i++)
	{
		outFile1<<descriptors_M0.row(i)<<endl;
		for (int j=0;j<descriptors_M0.cols;j++)
		{
			outFile1<<descriptors_M0.at<float>(i,j)<<endl;		//这里的i和j分别表示行和列，注意不要搞反了
		}
	}
	
}


int main()
{
	initModule_nonfree();

	//设置输出文件的保存目录
	outfile.open("C:\\Users\\ZY\\Desktop\\0103\\decript.txt");

	Mat img1 = imread("C:\\Users\\ZY\\Desktop\\0103\\1_S.jpg");	//大图

	int minHessian=5000;
	SurfFeatureDetector detector1(minHessian);
	Ptr<DescriptorExtractor> descriptor_extractor = DescriptorExtractor::create("SURF");

	//特征点检测			
	vector <KeyPoint> m_LeftKey,m_LeftKey1;		//特征点

	Mat img_m_LeftKey;				//画出特征点的输出结果图像
	Mat descriptors1;

	vector<Mat> descriptors12;
	Mat AA = Mat::zeros(64,1,CV_64F);
	/*对小图做特征点检测*/
	detector1.detect(img1,m_LeftKey);
	descriptor_extractor->compute(img1,m_LeftKey,descriptors1);
	int j=0;
	Mat descriptors11=Mat::zeros(descriptors1.rows,descriptors1.cols,CV_64F);

	/*将数据导入到excel表格中*/
	FILE* MyFile=NULL;
	MyFile=fopen("C:\\Users\\ZY\\Desktop\\0103\\desriptors.xls","w");

	if(!MyFile)
	{
		cout<<"无法输出数据到表格"<<endl;
		return 0;
	}

	fprintf(MyFile,"%s\t","x");
	fprintf(MyFile,"%s\t","y");
	fprintf(MyFile,"%s\t","size");
	fprintf(MyFile,"%s\t","angle");
	fprintf(MyFile,"%s\t","response");
	fprintf(MyFile,"%s\t","octave");
	for (int m=1;m<=descriptors1.cols;m++)
	{
		fprintf(MyFile,"%d\t",m);
	}
	fprintf(MyFile,"\n");
	for (int i=0;i<descriptors1.rows;i++)
	{
		fprintf(MyFile,"%2f\t",m_LeftKey[i].pt.x);
		fprintf(MyFile,"%2f\t",m_LeftKey[i].pt.y);
		fprintf(MyFile,"%2f\t",m_LeftKey[i].size);
		fprintf(MyFile,"%2f\t",m_LeftKey[i].angle);
		fprintf(MyFile,"%2f\t",m_LeftKey[i].response);
		fprintf(MyFile,"%2d\t",m_LeftKey[i].octave);

		for (int j=0;j<descriptors1.cols;j++)
		{
			fprintf(MyFile,"%.8f\t",descriptors1.at<float>(i,j));
			
		}
		fprintf(MyFile,"\n");
	

	}

    waitKey(0);
	system("pause");
	return 0;
}





