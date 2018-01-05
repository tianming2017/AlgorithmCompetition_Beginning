#include<stdio.h>
#include<stdlib.h>
const int MAXN = 500000+10;
const int MAXM = 100000+10;

int find(int value,int * arr,int len)
{
	for(int i=0;i<len;i++)
	{
		if(arr[i]==value)
		{
			return i;
		}
	}
	return -1;
}

void shift_circular_left(int index1,int index2,int * arr,int len)
{
	if(index1>=index2 || index1>len || index2>len ||arr==nullptr) return;

	//index1位置的值 移动到 index2位置
	//index1+1 到 index2的值 向左移动一格

	int temp = arr[index1];
	for(int i=index1+1;i<=index2;i++)
	{
		arr[i-1] = arr[i];
	}
	arr[index2] = temp;
}

void shift_circular_right(int index1,int index2,int * arr,int len)
{
	if(index1>=index2|| index1>len || index2>len || arr==nullptr) return;
	//index2位置的值 移动到 index1位置
	//index1到 index2-1的值向右移动一格

	int temp = arr[index2];
	for(int i=index2-1;i>=index1;i--)
	{
		arr[i+1] = arr[i];
	}
	arr[index1] = temp;

}

int main()
{
	int n;//n balls
	int m;
	scanf_s("%d%d",&n,&m);
	int *arr = nullptr;
	arr = (int *)malloc(sizeof(int)*n);//need free
	char type[10];
	int X,Y,p,q;

	for(int i=0;i<n;i++)
	{
		arr[i] = i+1;
	}
	for(int i=0;i<m;i++)
	{
		scanf("%1s%d%d",type,&X,&Y);
		p = find(X,arr,n);
		q = find(Y,arr,n);
		if(p<0||q<0||p==q)
		{
			printf("ERROR!");
			return 0;
		}
		if(type[0] == 'A')
		{
			if(q>p) shift_circular_left(p,q-1,arr,n);
			else shift_circular_right(q,p,arr,n);
		
		}
		else if(type[0] == 'B')
		{
			if(q>p) shift_circular_left(p,q,arr,n);
			else shift_circular_right(q+1,p,arr,n);
		}
	}
	for(int i=0;i<n;i++)
	{
		printf("%d ",arr[i]);
	}
	free(arr);
	system("pause");
	return 0;

}
