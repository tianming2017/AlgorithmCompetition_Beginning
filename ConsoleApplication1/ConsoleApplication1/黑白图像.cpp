//黑色1 白色0 找相邻的黑色块(顶点或边相邻)
//n*n
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>

#define MAXN 100
int mat[MAXN][MAXN],vis[MAXN][MAXN];

void dfs(int x,int y)
{
	if(!mat[x][y] || vis[x][y]) return;//白色或者已访问
	vis[x][y] = 1;//visit

	//递归访问周围8个格子
	dfs(x-1,y-1);	dfs(x-1,y);		dfs(x-1,y+1);
	dfs(x,y-1);						dfs(x,y+1);
	dfs(x+1,y-1);	dfs(x+1,y);		dfs(x+1,y+1);
}

int main()
{
	//init
	memset(mat,0,sizeof(mat));
	memset(vis,0,sizeof(vis));
	int n;
	scanf_s("%d",&n);//n must < MAXN
	char s[MAXN];
	//read data
	for(int i=0;i<n;i++)
	{
		scanf("%s",s);
		for(int j=0;j<n;j++)
		{
			mat[i+1][j+1] = s[j] - '0';//假想在n*n外面有一圈虚拟的白格子,数字字符 转 数字
		}
	}
	//compute dfs
	int count = 0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(!vis[i][j] && mat[i][j])//未访问且黑色
			{
				count++;
				dfs(i,j);
			}
		}
	}

	printf("%d\n",count);

	getchar();
	getchar();
	return 0;
}
//input
//6
//100100
//001010
//000000
//110000
//111000
//010100
//or
//6 100100 001010 000000 110000 111000 010100
//output
//3