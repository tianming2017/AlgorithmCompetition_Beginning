//n个数 组成序列S 求最大乘积 若不是正数 输出-1
//1<=n<=18; -10<=Si<=10

#include<stdio.h>
#define MAXN 18

int main()
{
	int n;
	int a[MAXN];
	long s = 0,smax = 0;
	while(scanf_s("%d",&n)==1 && n>=1 && n<=18)//filts invalid input
	{
		smax = 0;//reset for each S
		for(int i=0;i<n;i++)
		{
			scanf("%d",a+i);
			if(a[i]<-10 || a[i]>10)//filts invalid input
			{
				i--;
				continue;
			}
		}

		for(int i=0;i<n;i++)//起点
		{
			s = a[i];
			for(int j=i+1;j<n;j++)//终点
			{
				s = s * a[j];
				if(s > smax) smax = s;
			}
		}
		if(smax > 0)
		{
			printf("%ld\n",smax);
		}
		else
		{
			printf("-1\n");
		}
	
	
	
	}
	getchar();
	return 0;
}