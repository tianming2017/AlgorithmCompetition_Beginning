//输入正整数n;abcde/fghij = n; a---j 0---9排列; 2<=n<=79
#include<stdio.h>
#include<memory.h>
#include<algorithm>

using namespace std;

int check(int i,int j)
{
	int a[10];
	a[0] = i%10;
	a[1] = i/10%10;
	a[2] = i/100%10;
	a[3] = i/1000%10;
	a[4] = i/10000%10;
	a[5] = j%10;
	a[6] = j/10%10;
	a[7] = j/100%10;
	a[8] = j/1000%10;
	a[9] = j/10000%10;
	sort(a,a+10);
	for(int i=0;i<10;i++)
	{
		if(i!=a[i])		return 0;
	}
	return 1;
}

int check_2(int i,int j)
{
	int a[10];
	a[0] = i%10;
	a[1] = i/10%10;
	a[2] = i/100%10;
	a[3] = i/1000%10;
	a[4] = i/10000%10;
	a[5] = j%10;
	a[6] = j/10%10;
	a[7] = j/100%10;
	a[8] = j/1000%10;
	a[9] = j/10000%10;

	for(int u=0;u<10;u++)
		for(int v=u+1;v<10;v++)
		{
			if(a[u]==a[v])
				return 0;
		}

	return 1;
}



//遍历分母的所有可能取值 得到分子的值
//再判断 分子 分母
//别从 一个数的各个位数的值组成这个数的角度  来考虑了...
int main()
{
	int n;
	int i,j;

	while(scanf_s("%d",&n)==1)
	{
		if(n<2 || n>79)
		{
			printf("Invalid input! Retry......\n");
			continue;
		}
		for(j=1234;j<=98765;j++)//分母可能取值
		{
			i = j*n;
			if(i>=10234&&i<=98765)//限制分子范围
			{
				int success = check_2(i,j);
				if(success)
				{
					if(j<10234)
					{
						printf("%d / 0%d = %d\n",i,j,n);
					}
					else
					{
						printf("%d / %d = %d\n",i,j,n);
					}
				}
			}
		}
	}
	getchar();

	return 0;
}