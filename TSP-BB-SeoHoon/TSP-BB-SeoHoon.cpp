#include <stdio.h>
#include <malloc.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <iomanip>

using namespace std;

int** make_array(int n)	//n*n 2차원 배열 생성
{
	int** array;
	array=(int**)malloc(sizeof(int*)*n);
	for(int i=0; i<n; i++)
	{
		array[i]=(int*)malloc(sizeof(int)*n);
	}
	return array;
}
void print_console(int* W[], int n)	//콘솔 창에 배열 출력해주는 함수(옵션)
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
	//시작 노드는 상관 없으니 임의로 1번 노드에서 출발한다고 가정
	int **W;
	int n;

	FILE* file;
	fopen_s(&file, "input.txt","r");
	fscanf_s(file, "%d", &n);	//파일로부터 행렬 크기 n을 읽어오기
	W=make_array(n);	//n*n크기의 2차원 행렬들 생성해놓기
	
	for(int i=0; i<n; i++)	//txt에 저장된 값을 W배열에 저장시키기
	{
		for(int j=0; j<n; j++)
		{
			fscanf_s(file, "%d", &W[i][j]);
			
		}
	}

	cout<<"W행렬 출력"<<endl;	//읽어온 W행렬 출력하기
	print_console(W,n);
	
}