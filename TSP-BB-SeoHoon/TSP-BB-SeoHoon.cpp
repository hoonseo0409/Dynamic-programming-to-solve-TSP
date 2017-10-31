#include <stdio.h>
#include <malloc.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <iomanip>

using namespace std;

int** make_array(int n)	//n*n 2���� �迭 ����
{
	int** array;
	array=(int**)malloc(sizeof(int*)*n);
	for(int i=0; i<n; i++)
	{
		array[i]=(int*)malloc(sizeof(int)*n);
	}
	return array;
}
void print_console(int* W[], int n)	//�ܼ� â�� �迭 ������ִ� �Լ�(�ɼ�)
{
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			if(W[i][j]==-1)
			{
				cout<<"inf"<<" ";
			}
			else
			{
				cout<<W[i][j]<<" ";
			}
		}
		cout<<endl;
	}
}

void main()
{	
	//���� ���� ��� ������ ���Ƿ� 1�� ��忡�� ����Ѵٰ� ����
	int **W;
	int n;

	FILE* file;
	fopen_s(&file, "input.txt","r");
	fscanf_s(file, "%d", &n);	//���Ϸκ��� ��� ũ�� n�� �о����
	W=make_array(n);	//n*nũ���� 2���� ��ĵ� �����س���
	
	for(int i=0; i<n; i++)	//txt�� ����� ���� W�迭�� �����Ű��
	{
		for(int j=0; j<n; j++)
		{
			fscanf_s(file, "%d", &W[i][j]);
			
		}
	}

	cout<<"W��� ���"<<endl;	//�о�� W��� ����ϱ�
	print_console(W,n);
	
}