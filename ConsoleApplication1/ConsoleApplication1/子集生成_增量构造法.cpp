//����һ������ ö�������п��ܵ��Ӽ�
#include<stdio.h>

#define MAXN 100

//����Ĭ�ϸ���������0,1,2,3,...n-1 ��n����
//������ΪA[]�д����һ�� ����õ������ �±�
void print_subset(int n,int* A, int cur)
{
	//��ӡ��ǰ����
	for(int i=0;i<cur;i++)
		printf("%d ",A[i]);
	printf("\n");

	int s = cur ? A[cur-1] + 1 : 0;//ȷ����ǰԪ�ص���С����ֵ
	for(int i=s; i<n; i++)
	{
		A[cur] = i;
		print_subset(n,A,cur+1);//�ݹ鹹���Ӽ�
	}
}

int main()
{
	int n;
	int A[MAXN];
	while(scanf_s("%d",&n) == 1 && n>0)
	{
		print_subset(n,A,0);
	}
	getchar();
	return 0;

}