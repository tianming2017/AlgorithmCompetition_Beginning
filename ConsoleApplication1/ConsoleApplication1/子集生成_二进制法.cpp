//0,1,2,3,...n-1 �Ӽ�������2^n ���пռ�
#include<stdio.h>

//�����Ӽ�s���Ӽ�����n
//��s	0 1 1 1
//		3 2 1 0
//��� 0 1 2
void print_subset(int n,int s)
{
	for(int i=0;i<n;i++)
		if(s&(1<<i))//ȡÿ��������λ
			printf("%d ",i);
	printf("\n");
}

int main()
{
	int n;
	while(scanf_s("%d",&n) == 1 && n>0)
	{
		for(int i=0;i < (1<<n);i++)//ö�ٸ����Ӽ���Ӧ�ı��� 0,1,2,3,...,2^n - 1; һ��2^n �Ӽ�
			print_subset(n,i);
	}


}