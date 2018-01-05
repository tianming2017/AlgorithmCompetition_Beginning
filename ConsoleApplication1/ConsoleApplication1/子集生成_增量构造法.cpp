//给定一个集合 枚举它所有可能的子集
#include<stdio.h>

#define MAXN 100

//这里默认给定集合是0,1,2,3,...n-1 共n个数
//可以认为A[]中存的是一个 排序好的数组的 下标
void print_subset(int n,int* A, int cur)
{
	//打印当前集合
	for(int i=0;i<cur;i++)
		printf("%d ",A[i]);
	printf("\n");

	int s = cur ? A[cur-1] + 1 : 0;//确定当前元素的最小可能值
	for(int i=s; i<n; i++)
	{
		A[cur] = i;
		print_subset(n,A,cur+1);//递归构造子集
	}
}

int main()
{
	int n;
	int A[MAXN];
	while(scanf_s("%d",&n) == 1 && n>0)
	{
		print_subset(n,A,0);
	}
	getchar();
	return 0;

}