//����һ��λ����B[i] B[i] = 1 ��ζ�� i ���Ӽ���
#include<stdio.h>
#define MAXN 100

void print_subset(int n,int* B,int cur)
{
	if(cur == n)
	{
		for(int i=0;i<cur;i++)
			if(B[i])
				printf("%d ",i);//��ӡ��ǰ����
		printf("\n");
		return;
	}
	else
	{
		B[cur] = 1;//ѡ��cur��Ԫ��
		print_subset(n,B,cur+1);
		B[cur] = 0;//��ѡ��cur��Ԫ��
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