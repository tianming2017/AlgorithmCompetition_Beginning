#include<cstdio>
#include<memory.h>

const int MAXN = 10;
int n;
int A[MAXN];
int vis[MAXN];
//0 ╣╫ n-1 ╣дееап
void dfs(int cur)
{
	if(cur == n)
	{
		for(int i=0;i<n;i++)
			printf("%d ",A[i]);
		printf("\n");
		return;
	}
	for(int i=0;i<n;i++)
	{
		if(!vis[i])
		{
			vis[i] = 1;
			A[cur] = i;
			dfs(cur+1);
			vis[i] = 0;
		}	
	}
}


int main()
{
	while(scanf_s("%d",&n) == 1 && n>0 && n<=MAXN)
	{
		memset(A,0,sizeof(A));
		memset(vis,0,sizeof(vis));
		dfs(0);
	}
	getchar();
	return 0;


}
