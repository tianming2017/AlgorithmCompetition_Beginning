//构造一个位向量B[i] B[i] = 1 意味着 i 在子集中
#include<stdio.h>
#define MAXN 100

void print_subset(int n,int* B,int cur)
{
	if(cur == n)
	{
		for(int i=0;i<cur;i++)
			if(B[i])
				printf("%d ",i);//打印当前集合
		printf("\n");
		return;
	}
	else
	{
		B[cur] = 1;//选第cur个元素
		print_subset(n,B,cur+1);
		B[cur] = 0;//不选第cur个元素
		print_subset(n,B,cur+1);
	}
}


int main()
{
	int n;
	int B[MAXN];
	while(scanf_s("%d",&n) && n>0)
	{
		print_subset(n,B,0);
	}

}