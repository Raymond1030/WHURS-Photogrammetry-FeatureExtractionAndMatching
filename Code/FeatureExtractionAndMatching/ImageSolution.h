#pragma once

#include"tic_toc.h"
#include<opencv2/opencv.hpp>
#include <iostream>
#include<vector>
using namespace cv;
using namespace std;


class ImageSolution
{
public:
	Mat leftImg, rightImg;//左图右图
	ImageSolution();
	void ReadImg();//读取图像
	~ImageSolution();
};

//像素特征值
struct FeaturePoint {
	double value;
	int rows;
	int cols;
};

#define w 2 //兴趣点搜索窗口大小
#define corner_threshol 700 //Moravec特征提取预设阈值
class FeatureExtraction :
	public ImageSolution
{
public:

	int c_threshol= corner_threshol;
	Mat Img, FeatureImg;//特征提取后的影像
	FeaturePoint* Candidate;//存储特征点
	int numFE = 0;//记录兴趣点（特征点）数量
	FeatureExtraction();
	FeatureExtraction(Mat Img)
	{
		this->Img = Img;
		cvtColor(Img, FeatureImg, COLOR_GRAY2RGB);
	};

	void SetThreshol(int threshol);//设置阈值
	void MoravecGetFuature();//Moravec特征提取运算
	double InterestValue(int c, int r);//计算窗口像素四方向灰度差
	double FindMin(double V[4]);//找出最小值作为兴趣值

	void ShowFeature();//展示特征点
	void WriteFeature(const char*filename);//写一个txt文件存储特征点
	~FeatureExtraction();
};

//同名点结构
struct Match
{
	cv::Point2d srcPt; // 左片像点坐标
	cv::Point2d dstPt; // 右片像点坐标
	double dist;       // 相似性测度的计算值
};
#define corr_window_size 25    // 预设 相关系数匹配窗口大小
#define corr_threshold  0.85 // 预设 相关系数匹配阈值
class ImageMatching :
	public FeatureExtraction
{
public:
	Mat outputImg;//输出图像
	int windowSize=corr_window_size;//窗口大小
	double  threshold=corr_threshold;//阈值

	FeatureExtraction left,right;//左、右特征点对象
	FeaturePoint* leftCan, * rightCan;//存储左右两图的特征点
	int leftFNum, rightFNum;//特征点数量
	vector<Match> matches;//存储同名点

	ImageMatching();
	ImageMatching(FeatureExtraction L, FeatureExtraction R)
	{
		leftImg = L.Img;
		rightImg = R.Img;
		leftCan = L.Candidate;
		leftFNum = L.numFE;
		rightCan = R.Candidate;
		rightFNum = R.numFE;

	}
	void setWindowSize(int WindowSize);//设置窗口大小
	void setThreshold(double threshold);//设置

	void GGetFeature();//未初始化左图右图特征点对象 则进行特征提取
	void FileReadCan(const char* filename);//文件读取特征点(预先读取好)
	
	void Matching();//匹配
	bool isVaildPoint(Mat M,Point &pt);//判断是否是窗口点
	double computeCorrelationIdx(Mat& srcWindow,Mat& dstWindow);//计算两窗口相关系数
	
	void drawMatches();//绘制影像匹配窗口
};
