//��һ������ Ҫ������е����ֽ���ȫ����
#include<cstdio>
#include<algorithm>

const int MAXN = 100;
using namespace std;

//�� ����������� �е�Ԫ�ؽ���ȫ����
void print_permutation(int n,int* P,int *A,int cur)
{
	if(n == cur)
	{
		for(int i=0;i<n;i++)
			printf("%d ",A[i]);
		printf("\n");
	}
	else
	{
		for(int i=0;i<n;i++)//P[] ���±�  ȡP[i] �ŵ�A[cur]
		{
			if(!i || P[i] != P[i-1])//���ظ�
			{
				int c1=0, c2=0;
				for(int j=0;j<cur;j++)//���д���
					if(A[j] ==P[i])
						c1++;
				for(int k=0;k<n;k++)//P���������ֵ���ֵĴ���
					if(P[k] == P[i])
						c2++;
				if(c1<c2)
				{
					A[cur] = P[i];
					print_permutation(n,P,A,cur+1);
				}
			}
		}
	}
}

int main()
{
	int A[MAXN];
	int P[MAXN];
	int n;
	while(scanf_s("%d",&n) == 1 && n>0)
	{
		for(int i=0;i<n;i++)
		{
			scanf_s("%d",P+i);
		}
		sort(P,P+n);
		print_permutation(n,P,A,0);
	}
	getchar();
	return 0;
}
