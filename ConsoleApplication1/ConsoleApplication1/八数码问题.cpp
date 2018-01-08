//编号1-8的8个正方形摆成3行3列
//0表示空格
//给 初始局面和目标局面 给出最少移动步数
#include<cstdio>
#include<memory.h>
#include<set>
using namespace std;
typedef int State[9];//定义 状态 类型
const int MAXSTATE = 1000000;
State st[MAXSTATE],goal;//状态数组
int dist[MAXSTATE];//距离数组
int fa[MAXSTATE];//打印方案 父亲编号 数组
int dir[MAXSTATE];//记录空格操作

const int dx[] = {-1,1,0,0};//上下左右 x行(↓) y列(→) 
const int dy[] = {0,0,-1,1};
char direction[4][4] = {"↑","↓","←","→"};

//1.编码 把0~8全排列和0~362879的整数一一对应起来
//362880 = 9!
int vis[362880], fact[9];
void init_lookup_table()
{
	fact[0] = 1;
	for(int i=1;i<9;i++)
		fact[i] = fact[i-1] * i;
}

//避免同一结点访问多次
int try_to_insert(int s)
{
	int code = 0;//把st[s] 映射到整数 code
	for(int i=0;i<9;i++)
	{
		int cnt=0;
		for(int j=i+1;j<9;j++)
			if(st[s][j] < st[s][i])
				cnt++;
		code += fact[8-i] * cnt;
	}
	if(vis[code])
		return 0;
	return vis[code] = 1;
}

//2.哈希
const int MAXHASHSIZE = 1000003;
int head[MAXHASHSIZE],mynext[MAXSTATE];
void init_lookup_table_2()
{
	memset(head,0,sizeof(head));
}

int myhash(State& s)
{
	int v = 0;
	for(int i=0;i<9;i++)
		v = v*10 + s[i];//随便算 例如把9个数字组合成9位数
	return v%MAXHASHSIZE;//确保hash函数值是不超过hash表的大小的非负整数
}

int try_to_insert_2(int s)
{
	int h = myhash(st[s]);
	int u = head[h];
	while(u)//从表头开始查找链表
	{
		if(memcpy(st[u],st[s],sizeof(st[s])) == 0)
			return 0;//找到了 插入失败
		u = mynext[u];
	}
	mynext[s] = head[h];//插入到链表中
	head[h] = s;
	return 1;
}

//3.STL set
set<int> vis_3;
void init_lookup_table_3()
{
	vis_3.clear();
}
int try_to_insert_3(int s)
{
	int v=0;
	for(int i=0;i<9;i++)
		v = v*10 + st[s][i];
	if(vis_3.count(v))// vis_3.find(s) == vis.end() means not find, if not equal means contains at least 1
		return 0;
	vis_3.insert(v);
	return 1;
}



//BFS 返回目标状态在st数组下标
int bfs()
{
	init_lookup_table();//初始化查找表
	int front = 1,rear = 2;//不使用下标0 因为0被看做 不存在
	while (front < rear)
	{
		State& s = st[front];//用 引用 简化代码
		if(memcmp(goal,s,sizeof(s)) == 0)
			return front;//找到目标状态 成功返回

		int z;
		for(z=0;z<9;z++)
			if(!s[z])
				break;//找到 0 的位置

		int x = z/3;//行编号
		int y = z%3;//列编号
		for(int d=0;d<4;d++)
		{
			int newx = x + dx[d];
			int newy = y + dy[d];
			int newz = newx * 3 + newy;
			if(newx >=0 && newx<3 && newy>=0 && newy<3)//如果移动合法
			{
				State& t = st[rear];
				memcpy(&t,&s,sizeof(s));//扩展新结点 在front基础上变动
				t[newz] = s[z];//0
				t[z] = s[newz];//和0交换的值
				dist[rear] = dist[front] + 1;//更新 新结点的距离值
				fa[rear] = front;
				dir[rear] = d;
				if(try_to_insert(rear))
					rear++;//如果成功插入查找表 修改队尾指针
			}
		}
		front++;
	}
	return 0;//失败
}

void printPath(int find)
{
	if(fa[find] != 0)
		printPath(fa[find]);
	if(dir[find] >=0 && dir[find] <4)
		printf("%s\n",direction[dir[find]]);
	printf("%d %d %d\n",st[find][0],st[find][1],st[find][2]);
	printf("%d %d %d\n",st[find][3],st[find][4],st[find][5]);
	printf("%d %d %d\n",st[find][6],st[find][7],st[find][8]);
	printf("\n");
	return ;
}

int main()
{
	memset(st,0,sizeof(int) * MAXSTATE * 9);
	memset(dist,0,sizeof(dist));
	memset(fa,0,sizeof(fa));
	memset(vis,0,sizeof(vis));
	memset(fact,0,sizeof(fact));
	memset(head,0,sizeof(head));
	memset(mynext,0,sizeof(mynext));
	memset(dir,0,sizeof(dir));

	dir[1] = -1;//上次空格 移动方向 起点没有
	for(int i=0;i<9;i++)
		scanf_s("%d",&st[1][i]);
	for(int i=0;i<9;i++)
		scanf_s("%d",&goal[i]);
	int find;
	find = bfs();
	if(find)
	{
		printf("%d\n",dist[find]);
		//输出每个步骤后的九宫格
		printPath(find);
	}
	else
	{
		printf("-1\n");
	}
	getchar();
	getchar();
	return 0;
}
//input 
//2 6 4 1 3 7 0 5 8
//8 1 5 7 3 6 4 0 2
////2 6 4 1 3 7 0 5 8 8 1 5 7 3 6 4 0 2
//output
//31

//2 6 4 1 3 7 0 5 8 2 6 4 3 0 7 1 5 8
//2 6 4 3 0 7 1 5 8