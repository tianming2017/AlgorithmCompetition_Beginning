//����������k �ҵ����������� x>=y, 1/k = 1/x + 1/y
//k+1 <= y <= 2k
//yȡ��Сֵ(k+1)ʱ xȡ�����ֵ
//y <= x <= k*(k+1)

#include<stdio.h>
int main()
{
	int k,x,y;
	while(scanf_s("%d",&k)==1 && k>0)
	{
		for(y=k+1; y<=2*k; y++)
		{
			for(x = k*(k+1);x>=y;x--)
				if(k*(x+y) == x*y)
				{
					printf("1/%d = 1/%d + 1/%d\n",k,x,y);
				}
		}
	}
	getchar();
	return 0;
}