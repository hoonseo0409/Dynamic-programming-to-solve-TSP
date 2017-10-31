#include <stdio.h>
#include <malloc.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <cstdio>
#include <queue>


using namespace std;


int** make_array(int n)   //n*n 2���� �迭 ����
{
   int** array;
   array=(int**)malloc(sizeof(int*)*n);
   for(int i=0; i<n; i++)
   {
      array[i]=(int*)malloc(sizeof(int)*n);
   }
   return array;
}

void print_console(int* W[], int n)   //�ܼ� â�� �迭 ������ִ� �Լ�(�ɼ�)
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
   for(int i=1; (i<n); i++)   //-1�̰ų�(���Ѵ�) 0�̰ų�(�밢���) ÷�ڰ� 1��(�ٷ� ���1�� ���ư��� ���) ���� �ɷ��ֱ�
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
   cout<<"�ִ� ��δ�: "<<endl;
   for(int i=0;i<n;i++)
   {
      cout<<opttour[i]+1<<"->";
	  fprintf(tspf, "%d -> ",opttour[i]+1);
   }
   cout<<1;
   fprintf(tspf, "1");
   cout<<endl;
   fprintf(tspf, "\n");

   cout<<"�� �Ÿ���: "<<endl;
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
   catch(...)   //���� ���µ� ���� �߻��� ����ó��
   {
      cout<<"���� ���� ����, �̸� Ȯ�� ���"<<endl;
   }   
   fscanf_s(file, "%d", &n);   //���Ϸκ��� ��� ũ�� n�� �о����
   
   W=make_array(n);   //n*nũ���� 2���� ��ĵ� �����س���
   
   
   for(int i=0; i<n; i++)   //txt�� ����� ���� W�迭�� �����Ű��
   {
      for(int j=0; j<n; j++)
      {
         fscanf_s(file, "%d", &W[i][j]);
         
      }
   }

   cout<<"W��� ���"<<endl;   //�о�� W��� ����ϱ�
   print_console(W,n);
   travel(n,W);

}