#include<cstdio>
#include<algorithm>
#include<assert.h>

using namespace std;
const int MAXN = 16 + 10;
int isp[MAXN*2];//素数表
int vis[MAXN];//标记
int A[MAXN];//结果
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
	if(cur == n && isp[A[0] + A[n-1]])//递归边界 别忘了测试第一个数和最后一个数
	{
		for(int i=0;i<n;i++)
			printf("%d ",A[i]);
		printf("\n");
	}
	else
	{
		for(int i=2;i<=n;i++)//尝试 2 -- n中 每一个数
			if(!vis[i] && isp[A[cur-1] + i])//假如没有被访问 并且 这个数+数组中cur-1的数 的和是素数
			{
				vis[i] = 1;
				A[cur] = i;
				dfs(cur+1);//递归
				vis[i] = 0;//!!!清除标记
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
		dfs(1);//从A[1]开始递归
		printf("---End---\n");
	}
	getchar();
	return 0;

}