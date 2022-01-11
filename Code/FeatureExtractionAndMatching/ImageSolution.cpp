#include "ImageSolution.h"
#include"进度条.h"
ImageSolution::ImageSolution()
{
}

void ImageSolution::ReadImg()
{

    leftImg = imread("./RawImage/u0369_panLeft.tif", 0);
    rightImg = imread("./RawImage/u0367_panRight.tif", 0);
    imshow("RawImageLeft", leftImg);
    imshow("RawImageRight", rightImg);
    waitKey(0);
}

ImageSolution::~ImageSolution()
{
}

FeatureExtraction::FeatureExtraction()
{
}

void FeatureExtraction::SetThreshol(int threshol)
{
	this->c_threshol = threshol;
}

void FeatureExtraction::MoravecGetFuature()
{

	int c = 0, r = 0;//初始化图像遍历位置

	FeaturePoint* temp = (FeaturePoint*)malloc(sizeof(FeaturePoint) * 1000000);

	for (c = int(w / 2); c < Img.rows - int(w / 2); c++) {
		for (r = int(w / 2); r < Img.cols - int(w / 2); r++) {
			double F = InterestValue(c, r);
			if (F >this->c_threshol) {
				//temp[numFE].value = InterestValue(c, r);
				temp[numFE].value = F;

				temp[numFE].rows = c;	temp[numFE].cols = r;
				numFE++;
			}
			
		}
	}

	Candidate = (FeaturePoint*)malloc(sizeof(FeaturePoint) * numFE);

	for (int i = 0; i < numFE; i++) {
		Candidate[i].value = temp[i].value;
		Candidate[i].rows = temp[i].rows;
		Candidate[i].cols = temp[i].cols;
	}
	free(temp);

	ShowFeature();
}

double FeatureExtraction::InterestValue(int c, int r)
{
	int k = w / 2;
	double F = 0;//兴趣值初始化

	double V[4] = { 0,0,0,0 };//四个方向的灰度差
	for (int i = -k; i <= k - 1; i++) {
		
		//水平方向
		V[0] += pow((Img.at<uchar>(c + i, r) - Img.at<uchar>(c + i + 1, r)), 2);
		//左对角线
		V[1] += pow((Img.at<uchar>(c + i, r + i) - Img.at<uchar>(c + i + 1, r + i + 1)), 2);
		//竖直方向
		V[2] += pow((Img.at<uchar>(c, r + i) - Img.at<uchar>(c, r + i + 1)), 2);
		//右对角线
		V[3] += pow((Img.at<uchar>(c + i, r - i) - Img.at<uchar>(c + i + 1, r - i - 1)), 2);

	}

	F = FindMin(V);
	return F;
}

double FeatureExtraction::FindMin(double V[4])
{
	double min = V[0];
	for (int i = 0; i < 4; i++)
	{
		if (V[i] < min)
			min = V[i];
	}
	return min;
}

void FeatureExtraction::ShowFeature()
{
	int imgRows = FeatureImg.rows;
	int imgCols = FeatureImg.cols;
	for (int k = 0; k < numFE; k++)
	{

		loading(k, numFE,1);
	/*	cout << k << "\t" << Candidate[k].rows << "\t" << Candidate[k].cols << endl;*/
		if (Candidate[k].value != 0 )
		{
			for (int p = -3; p < 7; p++)
			{
				if (Candidate[k].rows + 6 < imgRows && Candidate[k].rows - 3 > 0 && Candidate[k].cols + 6 < imgCols && Candidate[k].cols - 3 > 0)
				{ //画红十字（周围像素变红色）
					FeatureImg.at<Vec3b>(Candidate[k].rows + p, Candidate[k].cols + p)[0] = 0;
					FeatureImg.at<Vec3b>(Candidate[k].rows + p, Candidate[k].cols + p)[1] = 0;
					FeatureImg.at<Vec3b>(Candidate[k].rows + p, Candidate[k].cols + p)[2] = 255;

					FeatureImg.at<Vec3b>(Candidate[k].rows + p, Candidate[k].cols - p)[0] = 0;
					FeatureImg.at<Vec3b>(Candidate[k].rows + p, Candidate[k].cols - p)[1] = 0;
					FeatureImg.at<Vec3b>(Candidate[k].rows + p, Candidate[k].cols - p)[2] = 255;
				}
			/*	Img.at<uchar>(Candidate[k].rows + p, Candidate[k].cols + p) = 0;
				Img.at<uchar>(Candidate[k].rows + p, Candidate[k].cols - p) = 0;*/

			}
		}
	}
	

}

void FeatureExtraction::WriteFeature(const char* filename)
{

	FILE *fp;
	errno_t error;
	error=fopen_s(&fp, filename, "w");
	if (error != 0)
	{
		cout << "文件打开失败";
	}

	fprintf_s(fp, "%d\n", numFE);
	fprintf_s(fp, "num\tValue\trows\tcols\t\n");
	for (int i = 0; i < numFE; i++)
	{
		fprintf_s(fp, "%d\t%lf\t%d\t%d\t\n", i, Candidate[i].value, Candidate[i].rows, Candidate[i].cols);
	}
		
	fclose(fp);
}

FeatureExtraction::~FeatureExtraction()
{
}

ImageMatching::ImageMatching()
{
	ReadImg();
	left.Img = leftImg;
	right.Img = rightImg;

}

void ImageMatching::GGetFeature()
{
	left.MoravecGetFuature();
	right.MoravecGetFuature();
	Candidate = (FeaturePoint*)malloc(sizeof(FeaturePoint) * numFE);
	this->leftCan = (FeaturePoint*)malloc(sizeof(FeaturePoint) * left.numFE);
	this->leftFNum = left.numFE;
	this->leftCan=left.Candidate;
	this->rightCan = (FeaturePoint*)malloc(sizeof(FeaturePoint) * right.numFE);
	this->rightFNum = right.numFE;
	this->leftCan =right.Candidate;
}

void ImageMatching::FileReadCan(const char*filename)
{

	FILE* fleft;
	errno_t error;
	error = fopen_s(&fleft, filename, "r");
	if (error != 0)
	{
		cout << "文件打开失败";
	}
	fscanf_s(fleft, "%d\n", &left.numFE);
	fscanf_s(fleft, "num\tValue\trows\tcols\t\n");
	leftCan = (FeaturePoint*)malloc(sizeof(FeaturePoint) * left.numFE);
	
	while (!feof(fleft))
	{
		int i, rows, cols;
		double val;
		fscanf_s(fleft, "%d\t%lf\t%d\t%d\t\n", &i, &val, &rows, &cols);
		leftCan[i].value = val;
		leftCan[i].rows = rows;
		leftCan[i].cols = cols;
	}
	fclose(fleft);
}

void ImageMatching::setWindowSize(int WindowSize)
{
	this->windowSize = WindowSize;

}

void ImageMatching::setThreshold(double threshold)
{
	this->threshold = threshold;
}

bool ImageMatching::isVaildPoint(Mat M,Point& pt)
{
	double r = windowSize / 2;
	if (pt.x < r || pt.y < r || pt.x >= M.cols - r || pt.y >= M.rows - r)
		return false;
	return true;
}

double ImageMatching::computeCorrelationIdx(Mat& srcWindow, Mat& dstWindow)
{
	if (srcWindow.size != dstWindow.size)
	{
		cerr << "窗口大小不匹配！" << std::endl;
		return 0;
	}

	// 总像元数量
	double totalNum = srcWindow.rows * srcWindow.cols;

	// 计算两张影像窗口中像素的平均值
	double gAverSrc = 0.0, gAverDst = 0.0;
	for (int i = 0; i < srcWindow.rows; i++)
		for (int j = 0; j < srcWindow.cols; j++)
		{
			gAverSrc += srcWindow.at<unsigned char>(i, j);
			gAverDst += dstWindow.at<unsigned char>(i, j);
		}
	gAverSrc /= totalNum;
	gAverDst /= totalNum;

	// 计算相关系数
	double numerator = 0.0;
	double denominatorSrc = 0.0;
	double denominatorDst = 0.0;

	for (int i = 0; i < srcWindow.rows; i++)
		for (int j = 0; j < srcWindow.cols; j++)
		{
			numerator += (srcWindow.at<unsigned char>(i, j) - gAverSrc) * (dstWindow.at<unsigned char>(i, j) - gAverDst);
			denominatorSrc += pow((srcWindow.at<unsigned char>(i, j) - gAverSrc), 2);
			denominatorDst += pow((dstWindow.at<unsigned char>(i, j) - gAverDst), 2);
		}

	double denominator = sqrt(denominatorSrc * denominatorDst);
	return abs(numerator / denominator);
}

void ImageMatching::Matching()
{
	matches.clear();

	Mat srcImgCopy, dstImgCopy;
	if (leftImg.channels() != 1)
		cvtColor(leftImg, srcImgCopy, COLOR_BGR2GRAY);
	else
		srcImgCopy = leftImg.clone();

	if (rightImg.channels() != 1)
		cvtColor(rightImg, dstImgCopy, COLOR_BGR2GRAY);
	else
		dstImgCopy = rightImg.clone();

	double r =windowSize / 2;


	for (int i=0;i<leftFNum;i++)
	{
		loading(i, leftFNum, 2);
		Point srcPt;
		srcPt.x = leftCan[i].cols;
		srcPt.y = leftCan[i].rows;
	
		if (isVaildPoint(srcImgCopy, srcPt))
		{
			// 使用ROI从原图中切出一个窗口
			Rect rectSrc, rectDst;
			Mat windowSrc, windowDst;
			rectSrc = Rect(srcPt.x - r, srcPt.y - r, windowSize, windowSize);
			windowSrc = srcImgCopy(rectSrc);

			// 遍历目标图像的特征点，寻找满足条件的同名点
			double idx = 0.0, maxIdx = 0.0;
			Point maxPt;
			for (int j = 0; j < rightFNum; j++)
			{
				Point dstPt;
				dstPt.x = rightCan[j].cols;
				dstPt.y = rightCan[j].rows;
				if (isVaildPoint(dstImgCopy, dstPt))
				{
					rectDst = Rect(dstPt.x - r, dstPt.y - r, windowSize, windowSize);
					windowDst = dstImgCopy(rectDst);
					idx = computeCorrelationIdx(windowSrc, windowDst);
					if (idx > maxIdx)
					{
						maxIdx = idx;
						maxPt = dstPt;
					}
				}
			}
			// 判断最大的相关系数是否满足设定阈值
			if (maxIdx > threshold)
			{
				Match mat;
				mat.srcPt = srcPt;
				mat.dstPt = maxPt;
				mat.dist = maxIdx;
				matches.push_back(mat);
			}
		}
	}
	
}

void ImageMatching::drawMatches()
{
	cvtColor(leftImg, leftImg, COLOR_GRAY2RGB);
	cvtColor(rightImg, rightImg, COLOR_GRAY2RGB);
	outputImg.create(Size(leftImg.cols + rightImg.cols, std::max(leftImg.rows, rightImg.rows)), CV_8UC3);

	leftImg.copyTo(outputImg(Rect(0, 0, leftImg.cols, leftImg.rows)));
	rightImg.copyTo(outputImg(Rect(leftImg.cols, 0, rightImg.cols, rightImg.rows)));

	Point pt1, pt2;

	for (Match match : matches)
	{
		Scalar color(0,0,255);

		pt1 = match.srcPt;
		pt2 = Point(match.dstPt.x + leftImg.cols, match.dstPt.y);

		circle(outputImg, pt1, 5, color, 1);
		circle(outputImg, pt2, 5, color, 1);
		line(outputImg, pt1, pt2, color, 1);
	}
}
