//给出n个结点的图G  和一个结点的排列
//define 结点i带宽b(i) = i 和相邻结点在排列中的最远距离 
//图的带宽 = max(b(i),0<=i<n)
//给定图G 求出让带宽最小的结点排列
//递归枚举全排列 + 剪枝(记录下当前最小带宽k)
//剪枝1 某两个结点的距离 dis>= k
//剪枝2 结点u的剩余相邻结点个数 m>=k
#include<cstdio>
#include<memory.h>
#include<algorithm>
using namespace std;
const int MAXN = 10;
int G[MAXN][MAXN];//邻接矩阵
int n;//结点个数
int b[MAXN];//存 所有可能序列
int res[MAXN];//存 结果
//---------
//copy from CSDN
int vis[MAXN];
int deg[MAXN];//相邻结点个数
int perm[MAXN];
int bestperm[MAXN];
int bestw = MAXN;//目前为止最小的带宽
int maxw = -1;//目前为止的带宽

//不知道对不对...放弃
//先写一个n!的low算法
int findIndex(int x)
{
	for(int i=0;i<n;i++)
		if(b[i] == x)
			return i;
	return -1;
}
void bandwidth()
{
	int k = MAXN;//初始值设大一点
	do
	{
		int bi = 0;//结点i的宽度 max
		int bg = 0;//图
		int tmp = 0;

		for(int i=0;i<n;i++)//结点i
		{
			for(int j=0;j<n;j++)
			{
				if(G[i][j])//结点i的相邻点
				{
					//找b[]中值为i,j之间的距离
					int ii = findIndex(i);
					int jj = findIndex(j);
					if(ii!=-1 && jj!=-1)
					{
						tmp = abs(ii-jj);
					}
					if(tmp > bi)
						bi = tmp;
				}
			}
			if(bi>bg)
				bg = bi;
		}
		if(k>bg)
		{
			k = bg;
			for(int i=0;i<n;i++)
				res[i] = b[i];
		}
	}while(next_permutation(b,b+n));

}


//CSDN
void search_width(int cur)
{
	if(cur >= n)
	{
		if(maxw < bestw)
		{
			for(int i=0;i<n;i++)
				bestperm[i] = perm[i];
			bestw = maxw;
		}
		return;
	}
	for(int i=0;i<n;i++)//生成序列
	{
		if(!vis[i])
		{
			int tmp = maxw;
			vis[i] = 1;
			perm[cur] = i;//cur位置 放i
			int left = deg[i];
			for(int k=0;k<cur;++k)
			{
				if(G[i][perm[k]])
				{
					if(cur-k > maxw)
						maxw = cur-k;//相邻结点的最远距离
					if(maxw < bestw)
						--left;
					else
						break;//存在两个相邻结点的距离 >= 最小带宽   剪枝 
				}
			}
			if(maxw<bestw)
			{
				if(left < bestw)//结点i的剩余相邻结点个数  < 最小带宽
				{
					search_width(cur+1);
				}
			
			}
			vis[i] = 0;
			maxw = tmp;
		}
	}
}

//日常默写
void search_width_2(int cur)
{
	if(cur >= n)
	{
		if(maxw<bestw)
		{
			bestw = maxw;
			for(int i=0;i<n;i++)
				bestperm[i] = perm[i];
		}
		return;
	}
	for (int i = 0; i < n; i++)//可能取值 第i结点
	{
		if(!vis[i])
		{
			vis[i] = 1;
			perm[cur] = i;
			int tmp = maxw;
			int left = deg[i];
			//判断cur位置放i 可不可以
			for (int j = 0; j < cur; j++)//已经有的值的下标
			{
				if(G[i][perm[j]])
				{
					left--;
					if(cur - j > maxw)
						maxw = cur - j;//对于每个结点 的 相邻结点 取距离最远的
					if(maxw >= bestw)
						break;
				}
			}
			if(maxw<bestw && left<bestw)
				search_width_2(cur+1);

			maxw = tmp;
			vis[i] = 0;
		}
	}
}


int main()
{

	while(scanf_s("%d",&n) == 1 && n>0 && n<=MAXN)
	{
		//init
		memset(G,0,sizeof(G));
		memset(b,0,sizeof(b));
		memset(vis,0,sizeof(vis));
		memset(deg,0,sizeof(deg));
		bestw = MAXN;
		maxw = -1;


		//read G
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
			{
				scanf_s("%d",&G[i][j]);
				deg[i] += G[i][j];
			}
		//may check G valid
		////init b[] 0,1,2,3,...,n-1
		//for(int i=0;i<n;i++)
		//	b[i] = i;

		//bandwidth();
		search_width_2(0);
		for(int i=0;i<n;i++)
			printf("%d ",bestperm[i]);
		printf("\n%d\n",bestw);

	}
	getchar();
	return 0;
}