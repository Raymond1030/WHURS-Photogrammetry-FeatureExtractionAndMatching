

void FeatureExtraction : ImageSolutionFeatureExtraction::GetFuature()
{
	int c = 0, r = 0;//��ʼ��ͼ�����λ��

	FeaturePoint* temp = (FeaturePoint*)malloc(sizeof(FeaturePoint) * 2000);

	for (c = int(w / 2); c < Img.rows - int(w / 2); c++) {
		for (r = int(w / 2); r <Img. cols - int(w / 2); r++) {
			double F = InterestValue(c, r);
			if (F > 2500) {
				temp[numFE].value = InterestValue( c, r);
				temp[numFE].rows = c;	temp[numFE].cols = r;
				numFE++;
			}
			else {
				temp[numFE].value = 0;
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

//����(c,r)����Ȥֵ����w*w�Ĵ����У������ĸ�����ˮƽ����ֱ���Խ��ߣ����������ػҶȲ��ƽ���ͣ�ȡ��СֵΪ����ȤֵF
double FeatureExtraction::InterestValue(int c,int r)
{

	int k = w / 2;
	double F = 0;//��Ȥֵ��ʼ��

	double V[4] = { 0,0,0,0 };//�ĸ�����ĻҶȲ�
	for (int i = -k; i <= k - 1; i++) {
		//ˮƽ����
		V[0] += pow((Img.at<uchar>(c + i, r) - Img.at<uchar>(c + i + 1, r)), 2);
		//��Խ���
		V[1] += pow((Img.at<uchar>(c + i, r + i) - Img.at<uchar>(c + i + 1, r + i + 1)), 2);
		//��ֱ����
		V[2] += pow((Img.at<uchar>(c, r + i) - Img.at<uchar>(c, r + i + 1)), 2);
		//�ҶԽ���
		V[3] += pow((Img.at<uchar>(c + i, r - i) - Img.at<uchar>(c + i + 1, r - i - 1)), 2);

	}
		
	F = FindMin(V);
	return F;
			
		
	
}

//�ҵ���С����Ϊ��Ȥֵ
double FeatureExtraction::FindMin(double V[4])
{
	double min = V[0];
	for (int i = 1; i < 4; i++)
	{
		if (V[i] < min)
			min = V[i];
	}
	return min;
}

//������ͼչʾ
void FeatureExtraction::ShowFeature()
{
	for (int i = 0; i < Img.rows; i++)
	{
		for (int j = 0; j < Img.cols; j++)
		{
			for (int k = 0; k < numFE; k++)
			{
				if (Candidate[k].rows == i && Candidate[k].cols == j)
				{
					for (int p = -2; p < 5; p++)
					{
						//����ʮ�֣���Χ���ر��ɫ��
						FeatureImg.at<Vec3b>(i + p, j + p)[0] = 255;
						FeatureImg.at<Vec3b>(i + p, j + p)[1] = 0;
						FeatureImg.at<Vec3b>(i + p, j + p)[2] = 0;

						FeatureImg.at<Vec3b>(i + p, j - p)[0] = 255;
						FeatureImg.at<Vec3b>(i + p, j - p)[1] = 0;
						FeatureImg.at<Vec3b>(i + p, j - p)[2] = 0;
					}
				}
			}
		}

	}
	namedWindow("MaekPic", 0);
	imshow("MaekPic", FeatureImg);
	waitKey(0);
}

FeatureExtraction::~FeatureExtraction()
{
}
