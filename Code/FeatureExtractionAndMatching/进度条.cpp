#include<iostream>
#include<Windows.h>
#include"进度条.h"
using namespace std;
void loading(int k,int numFE,int flag) {
	if (k < numFE - 1)
	{
		if (flag == 1)
		{
			printf("\r特征提取中[%.2lf%%]:", k * 100.0 / (numFE - 1));
		}
		else if (flag == 2)
		{
			printf("\r影像匹配中[%.2lf%%]:", k * 100.0 / (numFE - 1));
		}
	}
	else
	{
		if (flag == 1)
		{
			printf("\r提取完成[%.2lf%%]:\n\n", k * 100.0 / (numFE - 1));
		}
		else if (flag == 2)
		{
			printf("\r匹配完成[%.2lf%%]:\n", k * 100.0 / (numFE - 1));
		}
	}
	int show_num = k * 20 /numFE;
	for (int j = 1; j <= show_num; j++)
	{
		if(k!=numFE-1)
		std::cout << "█";
		
	}
}