#include<stdio.h>
#include<string.h>
#include<stdlib.h>

const int MAXD = 20;
int s[1<<MAXD];//��������2^MAXD-1

int main()
{
	int D,I;
	while(scanf_s("%d%d",&D,&I) == 2)
	{
		memset(s,0,sizeof(s));//���� 0�� 1��
		int k;
		int n = (1<<D)-1;//�������
		//��i��
		for(int i=0;i<I;i++)
		{
			k = 1;
			for(;;)
			{
				s[k] = !s[k];
				k = s[k] ? k*2:k*2+1;//���ݿ���״̬ѡ�����䷽��
				if(k>n) break;
			}
		}
		printf("%d\n",k/2);
	}
	system("pause");
	return 0;
}