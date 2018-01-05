#include<stdio.h>
#include<string.h>
#include<stdlib.h>

const int MAXD = 20;
int s[1<<MAXD];//最大结点个数2^MAXD-1

int main()
{
	int D,I;
	while(scanf_s("%d%d",&D,&I) == 2)
	{
		memset(s,0,sizeof(s));//开关 0开 1关
		int k;
		int n = (1<<D)-1;//最大结点编号
		//第i球
		for(int i=0;i<I;i++)
		{
			k = 1;
			for(;;)
			{
				s[k] = !s[k];
				k = s[k] ? k*2:k*2+1;//根据开关状态选择下落方向
				if(k>n) break;
			}
		}
		printf("%d\n",k/2);
	}
	system("pause");
	return 0;
}