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
	Mat leftImg, rightImg;//��ͼ��ͼ
	ImageSolution();
	void ReadImg();//��ȡͼ��
	~ImageSolution();
};

//��������ֵ
struct FeaturePoint {
	double value;
	int rows;
	int cols;
};

#define w 2 //��Ȥ���������ڴ�С
#define corner_threshol 700 //Moravec������ȡԤ����ֵ
class FeatureExtraction :
	public ImageSolution
{
public:

	int c_threshol= corner_threshol;
	Mat Img, FeatureImg;//������ȡ���Ӱ��
	FeaturePoint* Candidate;//�洢������
	int numFE = 0;//��¼��Ȥ�㣨�����㣩����
	FeatureExtraction();
	FeatureExtraction(Mat Img)
	{
		this->Img = Img;
		cvtColor(Img, FeatureImg, COLOR_GRAY2RGB);
	};

	void SetThreshol(int threshol);//������ֵ
	void MoravecGetFuature();//Moravec������ȡ����
	double InterestValue(int c, int r);//���㴰�������ķ���ҶȲ�
	double FindMin(double V[4]);//�ҳ���Сֵ��Ϊ��Ȥֵ

	void ShowFeature();//չʾ������
	void WriteFeature(const char*filename);//дһ��txt�ļ��洢������
	~FeatureExtraction();
};

//ͬ����ṹ
struct Match
{
	cv::Point2d srcPt; // ��Ƭ�������
	cv::Point2d dstPt; // ��Ƭ�������
	double dist;       // �����Բ�ȵļ���ֵ
};
#define corr_window_size 25    // Ԥ�� ���ϵ��ƥ�䴰�ڴ�С
#define corr_threshold  0.85 // Ԥ�� ���ϵ��ƥ����ֵ
class ImageMatching :
	public FeatureExtraction
{
public:
	Mat outputImg;//���ͼ��
	int windowSize=corr_window_size;//���ڴ�С
	double  threshold=corr_threshold;//��ֵ

	FeatureExtraction left,right;//�������������
	FeaturePoint* leftCan, * rightCan;//�洢������ͼ��������
	int leftFNum, rightFNum;//����������
	vector<Match> matches;//�洢ͬ����

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
	void setWindowSize(int WindowSize);//���ô��ڴ�С
	void setThreshold(double threshold);//����

	void GGetFeature();//δ��ʼ����ͼ��ͼ��������� �����������ȡ
	void FileReadCan(const char* filename);//�ļ���ȡ������(Ԥ�ȶ�ȡ��)
	
	void Matching();//ƥ��
	bool isVaildPoint(Mat M,Point &pt);//�ж��Ƿ��Ǵ��ڵ�
	double computeCorrelationIdx(Mat& srcWindow,Mat& dstWindow);//�������������ϵ��
	
	void drawMatches();//����Ӱ��ƥ�䴰��
};
