//�����Թ�����㡢�յ� Ҫ���������ƶ�����BFS
//�յ�1 �ϰ���0 
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include<queue>

#define MAXN 100
using namespace std;

int maze[MAXN][MAXN];//�յ�1 �ϰ���0 
int vis[MAXN][MAXN];//�Ƿ���ʹ�
int fa[MAXN][MAXN];//���ڵ�
int dist[MAXN][MAXN];//����
int last_dir[MAXN][MAXN];//�ƶ����� 0,1,2,3 ��������  X���� Y ���� X��Y��
int dx[4] = {-1,1,0,0};
int dy[4] = {0,0,-1,1};
char name[4] = {'U','D','L','R'};
int q[MAXN*MAXN];//queue
int dir[MAXN*MAXN];//record path

//��֤��ʼ�����ֹ�������
int isValidPoint(int x,int y,int n,int m)
{
	if(x<0 || x>=n || y<0 || y>=m)
	{
		return 0;
	}
	if(!maze[x][y])//�ϰ���
	{
		return 0;
	}
	return 1;
}

//����vis dist fa last_dir����
void bfs(int x,int y,int n,int m)
{
	int front = 0, rear = 0,d,u;//d:direction	u:index number
	u = x*m+y;
	vis[x][y] = 1;
	fa[x][y] = u;//���ĸ��ڵ� ����Ϊ���
	dist[x][y] = 0;
	q[rear++] = u;//enqueue ��ʼ������
	while(front<rear)//ÿ�δӶ�����ȡ��һ��u,����u���ĸ������ �ϸ� �ھ� ���
	{
		u = q[front++];
		x = u/m;
		y = u%m;
		for(d=0;d<4;d++)//�ĸ�����
		{
			int nx = x+dx[d];
			int ny = y+dy[d];
			if(nx>=0 && nx<n && ny>=0 && ny<m && maze[nx][ny] && !vis[nx][ny])//�����ϰ�
			{
				int v = nx*m+ny;
				q[rear++] = v;
				vis[nx][ny] = 1;
				fa[nx][ny] = u;//�ϼ�
				dist[nx][ny] = dist[x][y] + 1;
				last_dir[nx][ny] = d;
			}
		}
	}
}

//use C++ queue, dist fa last_dir vis
void bfs_2(int x,int y,int n,int m)
{
	//0. x,y->index 
	int u = x*m+y;
	dist[x][y] = 0;
	fa[x][y] = u;
	last_dir[x][y] = -1;
	vis[x][y] = 1;

	//1.�����ջ
	queue<int> q;
	q.push(u);//Ҳ����дһ��point ��struct Ȼ��push point
	//2.ջ���� ѭ�� ��ջ ջ��Ԫ�ص�4���ھ� ��ջ
	while(!q.empty())
	{
		int v = q.front();//dequeue
		q.pop();
		x = v/m;
		y = v%m;
		for(int d=0;d<4;d++)
		{
			int nx = x + dx[d];
			int ny = y + dy[d];
			if(nx>=0 && nx<n && ny>=0 && ny<m && maze[nx][ny] && !vis[nx][ny])
			{
				dist[nx][ny] = dist[x][y] + 1;
				fa[nx][ny] = v;
				last_dir[nx][ny] = d;
				vis[nx][ny] = 1;
				q.push(nx*m+ny);//enqueue
			
			}
		}
	}
}

void print_path(int x,int y,int n,int m)
{
	int fx = fa[x][y]/m;
	int fy = fa[x][y]%m;
	if(fx == -1 && fy == -1)//specific situation
	{
		printf("Unreachable!\n");
		return;
	}
	if(fx != x || fy != y)
	{
		print_path(fx,fy,n,m);//�ݹ���� �������㵽���ڵ��·��
		putchar(name[last_dir[x][y]]);//������ڵ㵽���ڵ��·��
	}
}

//non recursive method
//use array to record path part
void print_path_2(int x,int y,int n,int m)
{
	int c = 0;
	while (true)
	{
		int fx = fa[x][y]/m;
		int fy = fa[x][y]%m;
		if(fx == -1 && fy == -1)//specific situation
		{
			printf("Unreachable!\n");
			return;
		}
		if(fx == x && fy == y) break;
		dir[c++] = last_dir[x][y];
		x = fx;
		y = fy;
	}
	while(c--)
	{
		putchar(name[dir[c]]);
	}


}


int main()
{
	int n,m;//n��m��
	scanf_s("%d%d",&n,&m);
	char s[MAXN];//��¼һ�е�ͼ����
	//1.��ʼ������
	memset(maze,0,sizeof(maze));
	memset(vis,0,sizeof(vis));
	memset(fa,-1,sizeof(fa));
	memset(dist,-1,sizeof(dist));
	memset(last_dir,-1,sizeof(last_dir));

	//2.��ȡ��ͼ
	for(int i=0;i<n;i++)
	{
		scanf("%s",s);
		for(int j=0;j<m;j++)
		{
			maze[i][j] = s[j] - '0';
		}
	}
	//3.userָ����ڡ�����
	int fromX,fromY,toX,toY;
	scanf_s("%d%d%d%d",&fromX,&fromY,&toX,&toY);
	//check is valid? note:x must < n, y must < m
	while(!isValidPoint(fromX,fromY,n,m) || !isValidPoint(toX,toY,n,m))
	{
		printf("Invalid source or target point! Retry......\n");
		scanf_s("%d%d%d%d",&fromX,&fromY,&toX,&toY);
	}
	//4.bfs to set dis, fa, last_dir, vis []
	bfs_2(fromX,fromY,n,m);

	//5.print_path
	//print_path(toX,toY,n,m);
	//printf("\n");
	print_path_2(toX,toY,n,m);
	printf("\n");

	//6.print distance
	printf("Distance: %d",dist[toX][toY]);

	getchar();
	getchar();
	return 0;
}
//input 
//6 5
//11011
//10111
//10100
//10111
//11101
//11111
//or just
//6 5 11011 10111 10100 10111 11101 11111 0 0 5 4
//output
//DDDDDRRRR