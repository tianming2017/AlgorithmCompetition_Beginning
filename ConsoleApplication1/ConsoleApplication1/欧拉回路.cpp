//欧拉道路 无向图中从一个结点出发 每条边恰好经过一次 "一笔画"
//条件 除了起点和终点外 其他点的度数应该是偶数
//充分条件 连通的无向图 最多二个 奇点
//-----
//欧拉回路 联通的无向图 不存在奇点 从任意点出发即可

#include<stdio.h>
#include<stack>
#define MAXN 100

using namespace std;
int n;
int G[MAXN][MAXN];
int vis[MAXN][MAXN];
stack<int> s;

//无向图 
//若需要打印欧拉道路 需要传入 道路起点
void euler(int u)
{
	for(int v=0;v<n;v++)
	{
		if(G[u][v] && !vis[u][v])//存在边且未访问   u -> v
		{
			vis[u][v] = vis[v][u] = 1;//若为有向图 vis[u][v] = 1
			euler(v);
			printf("%d %d\n",u,v);//打印的顺序是逆序的
		}
	}
}

int main()
{

	return 0;
}