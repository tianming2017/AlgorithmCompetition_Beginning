//给定集合(无重复元素) 给出所有子集
#include<cstdio>
#include<algorithm>

using namespace std;
const int MAXN = 100;
//P已经排序 从小到大 
//A这里就存P的下标 不存值
//因为 限定往A中加的值必须比已有的大 ==> P已排序,只要加进去的(P的)下标比A中的已有下标大。
void print_subset(int n,int* P,int* A,int cur)
{
	for(int i=0;i<cur;i++)
		printf("%d ",P[A[i]]);
	printf("\n");
	//限定集合A中所有元素从小到大排序

	for(int i=0;i<n;i++)//P的所有可能的下标
	{
		if(!cur || i>A[cur-1])//加进去的(P的)下标比A中的已有下标大
		{
			A[cur] = i;//A中的第cur个 存 P的下标
			print_subset(n,P,A,cur+1);
		}
	}
	
}

int main()
{
	int n;
	int A[MAXN];
	int P[MAXN];
	while(scanf_s("%d",&n) == 1 && n>0)
	{
		for(int i=0;i<n;i++)
			scanf_s("%d",P+i);
		sort(P,P+n);
		print_subset(n,P,A,0);
	}
	getchar();
	return 0;
}