#include <stdio.h>
#include <malloc.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <cstdio>
#include <queue>

using namespace std;

struct node{
	int level;
	int* path;
	int bound;
	int pathlen;
};
struct cmp
{
	bool operator()(node d1, node d2)
	{
		return d1.bound>d2.bound;
	}
};
template<typename T>
bool isthere(int obj, T& arr)
{
	int num=sizeof(arr);
	for(int i=0; i<num; i++)
	{
		if(arr[i]==obj)
		{
			return true;
		}
	}
	return false;
}
int* get_bound_array(int n, node v)
{
	int num=n-v.level-1;
	int* bound_array;
	bound_array=(int*)malloc(sizeof(int)*num);
	int j=0;
	for(int i=0; i<n; i++)
	{
		if(!isthere(i, v.path))
		{
			bound_array[j]=i;
			j++;
		}
	}
	return bound_array;
}
void node_cpy(node &n1, node &n2, int n)
{
	n1.bound=n2.bound;
	n1.level=n2.level;
	for(int i=0; i<n; i++)
	{
		n1.path[i]=n2.path[i];
	}
	/*for(int i=n2.pathlen; i<n; i++)
	{
		n1.path[i]=-2;
	}*/
	n1.pathlen=n2.pathlen;
}
void path_cpy(int a[],int b[], int n)
{
	for(int i=0; i<n; i++)
	{
		a[i]=b[i];
	}
}
void main()
{
	priority_queue<node, vector<node>, cmp> pq;
	node v1;
	node v2;
	node v3;
	node test;
	v1.path=(int*)malloc(sizeof(int)*3);
	v2.path=(int*)malloc(sizeof(int)*3);
	v3.path=(int*)malloc(sizeof(int)*3);
	test.path=(int*)malloc(sizeof(int)*3);
	test.bound=13;
	test.level=7;
	test.pathlen=3;
	
	v1.bound=45;
	
	v1.level=1;
	
	v2.path[0]=22;
	v2.path[1]=222;
	
	v1.path[0]=11;
	v1.path[1]=111;
	v2.bound=20;
	
	v2.level=2;
	
	v3.bound=30;
	
	v3.level=3;
	v2.pathlen=2;
	
	v3.path[0]=33;
	v3.path[1]=33;

	node v4;
	v4.bound=30;


	pq.push(v2);
	pq.push(v1);
	pq.push(v3);
	
	
	
	/*node_cpy(test,pq.top(),3);
	//test=pq.top();
	cout<<"test의 바운드 5여야 함:"<<test.level<<"  path는99 999  "<<test.path[0]<<"  "<<test.path[1]<<"  "<<test.path[2]<<endl;*/

	cout<<pq.top().level<<endl;
	cout<<pq.top().path[0]<<pq.top().path[1]<<endl;
	pq.pop();
	
	
	cout<<pq.top().level<<endl;
	cout<<pq.top().path[0]<<pq.top().path[1]<<endl;
	pq.pop();
	
	cout<<pq.top().level<<endl;
	cout<<pq.top().path[0]<<pq.top().path[1]<<endl;
	pq.pop();
	
	
	/*int* test2;
	test2=(int*)malloc(sizeof(int)*3);
	test2[0]=2;
	test2[1]=-3;
	test2[2]=7;*/
	
	//cout<<isthere(3, test2);

	/*int* a;
	a=(int*)malloc(sizeof(int)*4);
	a[0]=1;
	a[1]=2;
	a[2]=3;
	int* b;
	b=(int*)malloc(sizeof(int)*4);
	path_cpy(b,a,4);
	for(int i=0;i<4;i++){cout<<b[i]<<endl;}
	a[1]=93;
	for(int i=0;i<4;i++){cout<<b[i]<<endl;}
	v1.pathlen=77;
	v2.pathlen=v1.pathlen;
	cout<<v2.pathlen<<endl;*/
}