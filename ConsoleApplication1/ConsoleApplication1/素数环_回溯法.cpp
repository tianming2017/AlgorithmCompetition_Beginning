#include<cstdio>
#include<algorithm>
#include<assert.h>

using namespace std;
const int MAXN = 16 + 10;
int isp[MAXN*2];//������
int vis[MAXN];//���
int A[MAXN];//���
int n;

int is_prime(int n)
{
	assert(n>0);
	if(n==1)	return 0;
	int m;
	m = (int)(floor(sqrt(n) + 0.5));
	for(int i=2;i<=m;i++)
		if(n%i==0)	return 0;
	return 1;
}

void constructIsp(int n)
{
	for(int i=2;i<n*2;i++)
		isp[i] = is_prime(i);
}

void init()
{
	memset(isp,0,sizeof(isp));
	memset(vis,0,sizeof(vis));
	memset(A,0,sizeof(A));
}

void dfs(int cur)
{
	if(cur == n && isp[A[0] + A[n-1]])//�ݹ�߽� �����˲��Ե�һ���������һ����
	{
		for(int i=0;i<n;i++)
			printf("%d ",A[i]);
		printf("\n");
	}
	else
	{
		for(int i=2;i<=n;i++)//���� 2 -- n�� ÿһ����
			if(!vis[i] && isp[A[cur-1] + i])//����û�б����� ���� �����+������cur-1���� �ĺ�������
			{
				vis[i] = 1;
				A[cur] = i;
				dfs(cur+1);//�ݹ�
				vis[i] = 0;//!!!������
			}
	}
}



int main()
{
	while (scanf_s("%d",&n) == 1 && n>0 && n<MAXN)
	{
		init();
		constructIsp(n);
		A[0] = 1;
		dfs(1);//��A[1]��ʼ�ݹ�
		printf("---End---\n");
	}
	getchar();
	return 0;

}