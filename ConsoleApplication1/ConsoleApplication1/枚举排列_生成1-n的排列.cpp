//�����ֵ������n��ȫ����
#include<stdio.h>
#include<memory.h>

#define MAXN 100
void print_permutation(int n,int* A,int cur)
{
	int i,j;
	if(cur == n)//�ݹ�߽�
	{
		for(int i=0;i<n;i++)	printf("%d ",A[i]);
		printf("\n");
	}
	else
	{
		for(i=1;i<=n;i++)//������A[cur]�����������i (1,2,3,..n)
		{
			int ok=1;
			for(j=0;j<cur;j++)
			{
				if(A[j] == i) ok = 0;//���i�Ѿ���A[0]-A[cur-1]���ֹ� ������ѡ
			}
			if(ok)
			{
				A[cur] = i;
				print_permulation(n,A,cur+1);//�ݹ����
			}
		}
	}
}

//Ĭд��һ��
void print_permutation_2(int n,int* A,int cur)
{
	if(cur==n)
	{
		for(int i=0;i<n;i++)
			printf("%d ",A[i]);
		printf("\n");
	}
	else
	{
		for(int i=1;i<=n;i++)//ע������ ȡ 1,2,3,..n; n����ȡ��!
		{
			int ok=1;
			//test i ok?
			for(int j=0;j<cur;j++)
			{
				if(i == A[j]) ok = 0;
			}
			if(ok)
			{
				A[cur] = i;
				print_permulation_2(n,A,cur+1);
			}
		}
	}
}


int main()
{
	int A[MAXN];
	int n;
	while(scanf_s("%d",&n)==1 && n>0)
	{
		memset(A,0,sizeof(A));
		print_permutation(n,A,0);
	}
	getchar();
	return 0;
}