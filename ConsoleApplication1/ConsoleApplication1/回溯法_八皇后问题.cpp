#include<stdio.h>
#include<memory.h>
#define MAXN 40
int n;
int tot = 0;//解的个数
int tot2 = 0;
int C[MAXN];
int vis[2][MAXN*2];

//cur 当前行
void search(int cur)
{
	int i,j;
	if(cur == n)//递归边界 只要走到这里 所有皇后必然不冲突
	{
		tot++;
		////输出结果
		//for(i=0;i<n;i++)
		//	printf("%d ",C[i]);
		//printf("\n");
	}
	else
	{
		for(i=0;i<n;i++)//遍历列
		{
			int ok = 1;
			C[cur] = i;//尝试把第cur行的皇后放在第i列
			for(j = 0;j<cur;j++)//验证是否冲突
			{
				if(C[cur] == C[j] || cur-C[cur] == j-C[j] || cur+C[cur] == j+C[j])//一列 主对角线 副对角线
				{
					ok = 0;
					break;
				}
			}
			if(ok)
				search(cur+1);
		}
	}
}

//利用二维数组vis[2][] 存取已经被占用的行 副对角线 主对角线
void search2(int cur)
{
	int i;
	if(cur == n)
		tot2++;
	else
	{
		for(i=0;i<n;i++)
		{
			if(!vis[0][i] && !vis[1][cur+i] && !vis[2][cur-i+n])//列 副对角线 主对角线 都没有被访问
			{
				C[cur] = i;//cur行的皇后 放在第i列
				vis[0][i] = vis[1][cur+i] = vis[2][cur-i+n] = 1;//修改全局变量, 占个坑
				search2(cur+1);
				vis[0][i] = vis[1][cur+i] = vis[2][cur-i+n] = 0;//复原!!!
			}
		}
	}	
}

//一行一行放皇后
int main()
{
	while(scanf_s("%d",&n)==1 && n>0 && n<MAXN)
	{
		memset(C,0,sizeof(C));
		memset(vis,0,sizeof(vis));

		tot = 0;
		tot2 = 0;
		search(0);
		search2(0);
		printf("解的总数: %d\n",tot);
		printf("解的总数: %d\n",tot2);
	}
	getchar();
	return 0;
}