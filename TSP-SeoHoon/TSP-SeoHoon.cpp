#include <stdio.h>
#include <malloc.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <cstdio>
#include <queue>


using namespace std;


int** make_array(int n)   //n*n 2차원 배열 생성
{
   int** array;
   array=(int**)malloc(sizeof(int*)*n);
   for(int i=0; i<n; i++)
   {
      array[i]=(int*)malloc(sizeof(int)*n);
   }
   return array;
}

void print_console(int* W[], int n)   //콘솔 창에 배열 출력해주는 함수(옵션)
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
struct node
{
   int bound;
   int level;
   int* path;
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

int bound(node v, int n, int* W[])
{
   int last=v.path[v.level];
   int bound=0;
   for(int i=0; i<v.level; i++)
   {
      bound=bound+W[v.path[i]][v.path[i+1]];
   }
   int min=-1;
   for(int i=1; (i<n); i++)   //-1이거나(무한대) 0이거나(대각행렬) 첨자가 1인(바로 노드1로 돌아가는 경우) 경우는 걸러주기
   {
      if(W[last][i]>0)
      {
         if(min==-1)
         {
            min=W[last][i];
         }
         else
         {
            if(min>W[last][i])
            {
               min=W[last][i];
            }
         }
      }
   }
   bound=bound+min;
   for(int i=0; (i<n-v.level-1); i++)
   {
      int mini=-1;
      int go=get_bound_array(n,v)[i];
      for(int j=0; j<n; j++)
      {
         if((W[go][j]>0)&&(j==0||!isthere(j,v.path)))
         {
            if(mini==-1)
            {
               mini=W[go][j];
            }
            else
            {
               if(mini>W[go][j])
               {
                  mini=W[go][j];
               }
            }
         }
      }
      bound=bound+mini;
   }
   return bound;
}
int length(node v,int n,int* W[])
{
   int length=0;
   for(int i=0; i<n; i++)
   {
	  if(W[v.path[i]][v.path[i+1]]==-1)
	  {
		  return -1;
	  }
	  else
	  {
		  length=length+W[v.path[i]][v.path[i+1]];
	  }
   }
   return length;
}
void arr_cpy(int a[], int b[], int n)
{
   for(int i=0; i<n; i++)
   {
      a[i]=b[i];
   }
}
void node_cpy(node &n1, node &n2, int n)
{
   n1.bound=n2.bound;
   n1.level=n2.level;
   for(int i=0; i<n; i++)
   {
      n1.path[i]=n2.path[i];
   }
   n1.pathlen=n2.pathlen;
}
void travel (int n, int *W[])
{
   node u,v;
   int* opttour;
   opttour=(int*)malloc(sizeof(int)*(n+1));
   priority_queue<node,vector<node>,cmp> pq;
   v.level=0;
   v.path=(int*)malloc(sizeof(int)*(n+1));
   v.pathlen=0;
   u.path=(int*)malloc(sizeof(int)*(n+1));
   u.pathlen=0;
   u.level=0;
   v.path[0]=0;
   v.pathlen++;
   v.bound=bound(v, n, W);
   int minlength=-1;
   pq.emplace(v);
   while(!pq.empty())
   {
	  node v;
	  v.path=(int*)malloc(sizeof(int)*(n+1));
      node_cpy(v,pq.top(),n+1);
	  pq.pop();
      if((minlength==-1)||(v.bound<minlength))
      {
         node u;
         u.level=v.level+1;
         for(int i=1; i<n; i++)
         {
            if(!isthere(i,v.path))
            {
               u.path=(int*)malloc(sizeof(int)*(n+1));
               arr_cpy(u.path, v.path, n+1);   //u.path=v.path;
               u.pathlen=v.pathlen;
               u.path[u.pathlen]=i;
               u.pathlen++;
               if(u.level==n-1)
               {
                  for(int i=1; i<n; i++)
                  {
                     if(!isthere(i,u.path))
                     {
                        u.path[n-1]=i;
                        u.pathlen++;
                     }
                  }
                  u.path[n]=0;
                  u.pathlen++;
                  if((minlength==-1)||(length(u,n,W)<minlength))
                  {
                     minlength=length(u,n,W);
                     
                     arr_cpy(opttour,u.path,n+1);
                  }
               }
               else
               {
                  u.bound=bound(u,n,W);
                  if((minlength<0)||(u.bound<minlength))
                  {
                     pq.emplace(u);      
                  }
               }
            }
         }
      }
	  
   }
   FILE *tspf;
   tspf = fopen("out.txt","w");

   cout<<endl;
   cout<<"최단 경로는: "<<endl;
   for(int i=0;i<n;i++)
   {
      cout<<opttour[i]+1<<"->";
	  fprintf(tspf, "%d -> ",opttour[i]+1);
   }
   cout<<1;
   fprintf(tspf, "1");
   cout<<endl;
   fprintf(tspf, "\n");

   cout<<"그 거리는: "<<endl;
   cout<<minlength<<endl;
   fprintf(tspf, "%d",minlength);
   fclose(tspf);
}
void main()
{
   int **W;
   int n;
   
   FILE* file;
   try
   {
      fopen_s(&file, "input.txt","r");
   }
   catch(...)   //파일 여는데 오류 발생시 예외처리
   {
      cout<<"파일 열기 오류, 이름 확인 요망"<<endl;
   }   
   fscanf_s(file, "%d", &n);   //파일로부터 행렬 크기 n을 읽어오기
   
   W=make_array(n);   //n*n크기의 2차원 행렬들 생성해놓기
   
   
   for(int i=0; i<n; i++)   //txt에 저장된 값을 W배열에 저장시키기
   {
      for(int j=0; j<n; j++)
      {
         fscanf_s(file, "%d", &W[i][j]);
         
      }
   }

   cout<<"W행렬 출력"<<endl;   //읽어온 W행렬 출력하기
   print_console(W,n);
   travel(n,W);

}