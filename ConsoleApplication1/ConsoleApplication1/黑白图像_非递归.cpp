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
//����ջ��ʱ��ȥ��һЩ������ ���Լ��ٶ�ջ��С
//���ô˺���,ֱ����ջҲ�ǿ��Ե�,����ѡ�����dfs����continue��
void pushBlackUnvisitedPointToStack(Point& p)
{
	if(mat[p.x][p.y] && !vis[p.x][p.y])
	{
		s.push(p);
	}
}

//�ѵ�ǰ�� ��ջ, ��ջ���յĻ�,ȡջ��Ԫ�� �����ж� ͨ���жϺ���� ��������8����ջ
void dfs(int x,int y)
{
	Point current = {x,y};
	s.push(current);
	while(!s.empty())
	{
		Point p = s.top();//ջ���ĵ�
		s.pop();
		if(vis[p.x][p.y] || !mat[p.x][p.y])//�ѷ��� ��ɫ0
		{
			//������� ��һλ
			continue;
		}
		vis[p.x][p.y] = 1;//����

		//����Χ8�������ջ
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
