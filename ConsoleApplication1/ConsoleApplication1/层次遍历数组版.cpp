#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXN 256
//没有结构体了吧
int have_value[MAXN];
int value[MAXN];
int left[MAXN];
int right[MAXN];
int cnt = 0;//已存在的结点编号最大值
char s[MAXN+10];
int failed = 0;
int n = 0,ans[MAXN];//结点总数 输出序列
const int root = 1;//root

void newtree()
{
	left[root] = right[root] = 0;
	cnt = root;
}

//得到新结点的编号
int newnode()
{
	int u = ++cnt;
	left[u] = right[u] = 0;
	return u;
}

void addnode(int v,char* s)
{
	int n = strlen(s);
	int u = root;
	for(int i=0;i<n;i++)
	{
		if(s[i] == 'L')
		{
			if(left[u] == 0)
			{
				left[u] = newnode();
			}
			u = left[u];
		}
		else if(s[i] == 'R')
		{
			if(right[u] == 0)
			{
				right[u] = newnode();
			}
			u = right[u];
		}
	}
	if(have_value[u])
	{
		failed++;
	}
	value[u] = v;
	have_value[u] = 1;
}

int read_input()
{
	failed = 0;
	newtree();
	while(true)
	{
		if(scanf("%s",s)!=1) return 0;
		if(!strcmp(s,"()")) break;
		int v;
		sscanf_s(&s[1],"%d",&v);
		addnode(v,strchr(s,',')+1);
	}
	return 1;
}

int bfs()
{
	int front = 0,rear = 1;
	int q[MAXN];//结点队列
	q[0] = root;
	while(front<rear)
	{
		int u = q[front++];
		if(!have_value[u]) return 0;
		ans[n++] = value[u];
		if(left[u]) q[rear++] = left[u];
		if(right[u]) q[rear++] = right[u];
	}
	return 1;
}

void init()
{
	memset(have_value,0,MAXN*sizeof(int));
	memset(value,0,MAXN*sizeof(int));
	memset(left,0,MAXN*sizeof(int));
	memset(right,0,MAXN*sizeof(int));
	memset(ans,0,MAXN*sizeof(int));
	cnt = 0;
	failed = 0;
	n = 0;
}

int main()
{
	init();
	read_input();
	int flag = bfs();
	if(failed >0 || flag==0)
	{
		printf("%d",-1);
	}
	else
	{
		for(int i=0;i<n;i++)
			printf("%d ",ans[i]);
	}
	getchar();
	getchar();
	return 0;
}

//input 
//(11,LL) (7,LLL) (8,R) (5,) (4,L) (13,RL) (2,LLR) (1,RRR) (4,RR) ()
//ouput
//5 4 8 11 13 4 7 2 1

