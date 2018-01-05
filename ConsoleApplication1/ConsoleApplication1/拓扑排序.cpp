//n个变量(结点)
//m个二元组(u,v)---u 到 v存在一条有向边
//给出任意一种拓扑排序(有向无环图 前提之下)
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include<queue>

#define MAXN 100
using namespace std;
//c[u]=0 从未访问;
//c[u]=1已经访问,而且递归访问过它的子孙;
//c[u]=-1表示正在访问(递归调用dfs(u)正在栈帧中,尚未返回) 存在有向环
int c[MAXN];
int topo[MAXN],t;//结果数组 以及 下标,直接从0遍历n就是要的排序
int G[MAXN][MAXN];//邻接矩阵 表示的图
int n,m;//n个结点 m条边

int Indegree[MAXN];//入度
int topoNum[MAXN];//第i结点的拓扑序号 根据拓扑序号输出 值为0,1,2,3...

//递归的dfs
//结果数组是逆向构成的
bool dfs(int u)
{
	c[u] = -1;
	for(int v=0;v<n;v++)
	{
		if(G[u][v])//u -> v
		{
			if(c[v]<0) return false;//存在有向环 失败退出
			else if(c[v]==0 && !dfs(v)) return false;//从未访问过v;递归访问v;但是v的dfs 失败的话
			//假如c[v]=1 do Nothing
		}
	}
	c[u] = 1;
	topo[--t] = u;
	return true;
}

//借助dfs实现拓扑排序
//从0号结点开始dfs
bool toposort()
{
	t = n;
	memset(c,0,sizeof(c));//初始化为 未访问
	for(int u=0;u<n;u++)//对每一个结点 如果没有排序过 就排序
	{
		if(c[u]==0)
		{
			if(!dfs(u)) return false;	
		}	
	}
	return true;
}

//用邻接矩阵算入度 
void calculateIndegree()
{
	memset(Indegree,0,sizeof(Indegree));
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(G[i][j]!=0)
			{
				Indegree[j]++;
			}
		}
	}

}

//数据结构书上的算法 有点BFS的感觉
//找到任意一个入度为0的顶点 编号 其相邻结点入度减少1
bool toposort_2()
{
	calculateIndegree();
	queue<int> q;
	int count = 0;
	//把入度=0的顶点 放到队列中 队列初始化
	for(int i=0;i<n;i++)
	{
		if(Indegree[i]==0)
		{
			q.push(i);
		}
	}
	while(!q.empty())
	{
		int v = q.front();
		q.pop();
		topoNum[v] = count;
		topo[count] = v;
		count++;
		//与v相邻的每个顶点
		for(int w=0;w<n;w++)
		{
			if(G[v][w]!=0)//v->w 相邻
			{
				if(--Indegree[w]==0)//减一后 入度为0
				{
					q.push(w);
				}
			}
		}
	}
	if(count != n) return false;//环
	return true;
}

int main()
{
	scanf_s("%d%d",&n,&m);
	//构造G[][]
	memset(G,0,sizeof(G));
	memset(topo,-1,sizeof(topo));
	memset(topoNum,-1,sizeof(topoNum));


	//0 'a'; 1 'b';...
	char s1,s2;
	for(int i=0;i<m;i++)
	{
		//(1)用getchar()清除 
		//(2)用"%1s"来限制 
		//(3)用格式串中空格或"%*c"来"吃掉" 
		//(4)用函数fflush(stdin)清除全部剩余内容 
		scanf("%*c%c,%c",&s1,&s2);
		int j,k;
		j = s1 - 'a';
		k = s2 - 'a';
		if(j<0 || j>=n || k<0 || k>=n)
		{
			i--;
			printf("Invalid input! Retry...\n");
			continue;
		}
		G[j][k] = 1;
	}
	//toposort
	//bool success = toposort();
	bool success = toposort_2();
	if(success)
	{
		//output
		printf("TopoSort: ");
		for(int i=0;i<n;i++)
		{
			if(i==0)
			{
				printf("%c",topo[i] + 'a');
			}
			else
			{
				printf("->%c",topo[i] + 'a');	
			}	
		}
		printf("\n");
	}
	else
	{
		printf("Not DAG!\n");
	}


	getchar();
	getchar();
	return 0;
}
//input
//4 3 a,b c,b d,c
//output
//d->c->a->b
//a->d->c->b