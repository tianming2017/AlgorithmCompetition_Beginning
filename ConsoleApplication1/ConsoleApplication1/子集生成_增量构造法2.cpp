//��������(���ظ�Ԫ��) ���������Ӽ�
#include<cstdio>
#include<algorithm>

using namespace std;
const int MAXN = 100;
//P�Ѿ����� ��С���� 
//A����ʹ�P���±� ����ֵ
//��Ϊ �޶���A�мӵ�ֵ��������еĴ� ==> P������,ֻҪ�ӽ�ȥ��(P��)�±��A�е������±��
void print_subset(int n,int* P,int* A,int cur)
{
	for(int i=0;i<cur;i++)
		printf("%d ",P[A[i]]);
	printf("\n");
	//�޶�����A������Ԫ�ش�С��������

	for(int i=0;i<n;i++)//P�����п��ܵ��±�
	{
		if(!cur || i>A[cur-1])//�ӽ�ȥ��(P��)�±��A�е������±��
		{
			A[cur] = i;//A�еĵ�cur�� �� P���±�
			print_subset(n,P,A,cur+1);
		}
	}
	
}

int main()
{
	int n;
	int A[MAXN];
	int P[MAXN];
	while(scanf_s("%d",&n) == 1 && n>0)
	{
		for(int i=0;i<n;i++)
			scanf_s("%d",P+i);
		sort(P,P+n);
		print_subset(n,P,A,0);
	}
	getchar();
	return 0;
}