//input n>0 ��1,2,3,...n ���һ���� ʹ��������������֮�;�Ϊ����
//���ʱ ������1��ʼ��ʱ������ ͬһ����ֻ���һ�� 
#include<cstdio>
#include<algorithm>
#include<memory.h>
#include<assert.h>
using namespace std;

const int MAXN = 16 + 10;
int isp[MAXN*2];//������

int is_prime(int n)
{
	int m;
	assert(n>0);
	if(n==1) return 0;
	m = int(floor(sqrt(n) + 0.5));//����ȡ��
	for(int i=2;i<=m;i++)
		if(n%i==0) return 0;
	return 1;
}

int main()
{
	int n;
	int A[MAXN];
	while(scanf_s("%d",&n) == 1 && n>0 && n<MAXN)
	{
		memset(isp,0,sizeof(isp));
		memset(A,0,sizeof(A));

		//���������� �ӿ�����ж�
		for(int i=2;i<=n*2;i++)
			isp[i] = is_prime(i);
		//��һ������ 1,2,3,...,n
		for(int i=0;i<n;i++)
			A[i] = i+1;
		do
		{
			int ok = 1;
			for(int i=0;i<n;i++)
				if(!isp[A[i] + A[(i+1)%n]])
				{
					ok = 0;
					break;
				}
			if(ok)
			{
				for(int i=0;i<n;i++)
					printf("%d ",A[i]);//�������
				printf("\n");
			}
		}while(next_permutation(A+1,A+n));//1 ��λ�ò���
	}
	getchar();
	return 0;
}
