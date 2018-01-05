//0,1,2,3,...n-1 子集合总数2^n 含有空集
#include<stdio.h>

//给定子集s和子集长度n
//若s	0 1 1 1
//		3 2 1 0
//输出 0 1 2
void print_subset(int n,int s)
{
	for(int i=0;i<n;i++)
		if(s&(1<<i))//取每个二进制位
			printf("%d ",i);
	printf("\n");
}

int main()
{
	int n;
	while(scanf_s("%d",&n) == 1 && n>0)
	{
		for(int i=0;i < (1<<n);i++)//枚举各个子集对应的编码 0,1,2,3,...,2^n - 1; 一共2^n 子集
			print_subset(n,i);
	}


}