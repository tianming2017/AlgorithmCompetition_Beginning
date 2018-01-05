#include<stdio.h>
#include<memory.h>
#include<stack>
#define MAXN 100
using namespace std;

int mat[MAXN][MAXN], vis[MAXN][MAXN];
typedef struct Point
{
	int x;
	int y;
}Point;

stack<Point> s;

//only push black unvisited point!
//在入栈的时候去除一些错误项 可以减少堆栈大小
//不用此函数,直接入栈也是可以的,错误选项会在dfs里面continue掉
void pushBlackUnvisitedPointToStack(Point& p)
{
	if(mat[p.x][p.y] && !vis[p.x][p.y])
	{
		s.push(p);
	}
}

//把当前点 入栈, 堆栈不空的话,取栈顶元素 进行判断 通过判断后访问 并将相邻8个入栈
void dfs(int x,int y)
{
	Point current = {x,y};
	s.push(current);
	while(!s.empty())
	{
		Point p = s.top();//栈顶的点
		s.pop();
		if(vis[p.x][p.y] || !mat[p.x][p.y])//已访问 白色0
		{
			//这个不行 下一位
			continue;
		}
		vis[p.x][p.y] = 1;//访问

		//把周围8个加入堆栈
		Point p1 = {p.x-1,p.y-1};
		Point p2 = {p.x-1,p.y};
		Point p3 = {p.x-1,p.y+1};
		Point p4 = {p.x,p.y-1};
		Point p5 = {p.x,p.y+1};
		Point p6 = {p.x+1,p.y-1};
		Point p7 = {p.x+1,p.y};
		Point p8 = {p.x+1,p.y+1};
		//s.push(p1);
		//s.push(p2);
		//s.push(p3);
		//s.push(p4);
		//s.push(p5);
		//s.push(p6);
		//s.push(p7);
		//s.push(p8);
		pushBlackUnvisitedPointToStack(p1);
		pushBlackUnvisitedPointToStack(p2);
		pushBlackUnvisitedPointToStack(p3);
		pushBlackUnvisitedPointToStack(p4);
		pushBlackUnvisitedPointToStack(p5);
		pushBlackUnvisitedPointToStack(p6);
		pushBlackUnvisitedPointToStack(p7);
		pushBlackUnvisitedPointToStack(p8);
	}
}


int main()
{
	int n;
	scanf_s("%d",&n);
	char s[MAXN];
	int count = 0;

	memset(mat,0,sizeof(mat));
	memset(vis,0,sizeof(vis));

	for(int i=0;i<n;i++)
	{
		scanf("%s",s);
		for(int j=0;j<n;j++)
		{
			mat[i+1][j+1] = s[j] - '0';
		}
	}

	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(!vis[i][j] && mat[i][j])
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
