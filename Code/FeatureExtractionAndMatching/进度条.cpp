#include<iostream>
#include<Windows.h>
#include"������.h"
using namespace std;
void loading(int k,int numFE,int flag) {
	if (k < numFE - 1)
	{
		if (flag == 1)
		{
			printf("\r������ȡ��[%.2lf%%]:", k * 100.0 / (numFE - 1));
		}
		else if (flag == 2)
		{
			printf("\rӰ��ƥ����[%.2lf%%]:", k * 100.0 / (numFE - 1));
		}
	}
	else
	{
		if (flag == 1)
		{
			printf("\r��ȡ���[%.2lf%%]:\n\n", k * 100.0 / (numFE - 1));
		}
		else if (flag == 2)
		{
			printf("\rƥ�����[%.2lf%%]:\n", k * 100.0 / (numFE - 1));
		}
	}
	int show_num = k * 20 /numFE;
	for (int j = 1; j <= show_num; j++)
	{
		if(k!=numFE-1)
		std::cout << "��";
		
	}
}