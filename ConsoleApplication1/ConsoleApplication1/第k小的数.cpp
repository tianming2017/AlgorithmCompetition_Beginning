//n个整数 正整数1 <= k <= n 第K小的数字
//快排 A[p..r] = A[p..q] (q-p+1个数) + A[q+1,..r]
//q-p+1 k 比大小只在左边 / 右边递归

#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

//1.数据结构书上的快排
#define Cutoff (3)

void InsertSort(int A[],int n)
{
	int j,p;
	int tmp;
	for(p=1; p<n; p++)//一个数字肯定是排序好的 之后每次插入都是插入一个已经排序好的数组
	{
		tmp = A[p];
		for(j=p; j>0 && A[j-1] >tmp; j--)//j是想插入的地方 但是要保证j-1的数字 <= 要插入的数字
			A[j] = A[j-1];
		A[j] = tmp;
	}
}

void swap(int* a,int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
	return;
}

//pivot
int Median3(int A[],int left,int right)
{
	int center = (left + right) / 2;
	if(A[left] > A[center])
		swap(&A[left],&A[center]);
	if(A[left] > A[right])
		swap(&A[left],&A[right]);
	if(A[center] > A[right])
		swap(&A[center],&A[right]);
	//A[left] <= A[center] <= A[right]
	//hide pivot A[right-1]
	swap(&A[center],&A[right-1]);
	return A[right-1];
}

void Qsort(int A[],int left,int right)
{
	int i,j;
	int pivot;
	if(left + Cutoff <= right)
	{
		pivot = Median3(A,left,right);
		i = left;
		j = right-1;
		for(;;)
		{
			while(A[++i] < pivot){}
			while(A[--j] > pivot){}
			if(i<j)
				swap(&A[i],&A[j]);
			else
			{
				break;
			}
		}
		swap(&A[i],&A[right-1]);//restore pivot
		Qsort(A,left,i-1);
		Qsort(A,i+1,right);
	}
	else//insert sort
	{
		InsertSort(A+left,right-left+1);
	}
}

void Quicksort(int A[],int n)
{
	Qsort(A,0,n-1);
}

//2.百度上的快排 
void Qsort_2(int A[],int left,int right)
{
	if(left >= right)
		return;
	int i = left;
	int j = right;
	int key = A[left];//选第一个作为pivot
	while(i<j)
	{
		while(i<j && A[j] >= key)
		{
			--j;
		}
		A[i] = A[j];

		while(i<j && A[i] <= key)
		{
			++i;
		}
		A[j] = A[i];
	}
	A[i] = key;//pivot 记录到位
	Qsort_2(A,left,i-1);
	Qsort_2(A,i+1,right);
}

void Quicksort_2(int A[],int n)
{
	Qsort_2(A,0,n-1);
}

//3.在百度快排基础上写第k小
int Qsort_3(int A[],int left,int right,int k)
{
	if(left>=right)
		return A[left];
	int i = left;
	int j = right;
	int key = A[left];
	while(i<j)
	{
		while(i<j && A[j]>=key)
		{
			--j;
		}
		A[i] = A[j];
		
		while(i<j && A[i]<=key)
		{
			++i;
		}
		A[j] = A[i];
	}
	A[i] = key;
	//left...i-1, i , i+1...right
	//i-left,	  1,	right-i
	//-----right-left+1---------
	if(k == i-left+1)
	{
		return A[i];
	}
	else if(k < i-left+1)
	{
		return Qsort_3(A,left,i-1,k);
	}
	else
	{
		return Qsort_3(A,i+1,right,k-(i-left+1));
	}
}

int Quicksort_3(int A[],int n,int k)
{
	return Qsort_3(A,0,n-1,k);
}


int main()
{
	const int MAXN = 100;
	int n;
	int A[MAXN];
	int B[MAXN];
	int k = 5;

	while(scanf_s("%d%d",&n,&k) == 2 && k>0 && k<=n && n<=MAXN)
	{
		srand((unsigned int)time(NULL));
		for (int i = 0; i < n; i++)
		{
			A[i] = rand() % 101;//a + rand() % n
		}
		memcpy(B,A,sizeof(A));

		Quicksort_2(A,n);
		for(int i=0;i<n;i++)
			cout << A[i] << " ";
		cout << endl;

		cout << Quicksort_3(A,n,k) << endl;
	}

	getchar();
	return 0;
}