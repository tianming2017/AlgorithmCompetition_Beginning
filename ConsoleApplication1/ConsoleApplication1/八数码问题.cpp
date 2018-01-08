//���1-8��8�������ΰڳ�3��3��
//0��ʾ�ո�
//�� ��ʼ�����Ŀ����� ���������ƶ�����
#include<cstdio>
#include<memory.h>
#include<set>
using namespace std;
typedef int State[9];//���� ״̬ ����
const int MAXSTATE = 1000000;
State st[MAXSTATE],goal;//״̬����
int dist[MAXSTATE];//��������
int fa[MAXSTATE];//��ӡ���� ���ױ�� ����
int dir[MAXSTATE];//��¼�ո����

const int dx[] = {-1,1,0,0};//�������� x��(��) y��(��) 
const int dy[] = {0,0,-1,1};
char direction[4][4] = {"��","��","��","��"};

//1.���� ��0~8ȫ���к�0~362879������һһ��Ӧ����
//362880 = 9!
int vis[362880], fact[9];
void init_lookup_table()
{
	fact[0] = 1;
	for(int i=1;i<9;i++)
		fact[i] = fact[i-1] * i;
}

//����ͬһ�����ʶ��
int try_to_insert(int s)
{
	int code = 0;//��st[s] ӳ�䵽���� code
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

//2.��ϣ
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
		v = v*10 + s[i];//����� �����9��������ϳ�9λ��
	return v%MAXHASHSIZE;//ȷ��hash����ֵ�ǲ�����hash��Ĵ�С�ķǸ�����
}

int try_to_insert_2(int s)
{
	int h = myhash(st[s]);
	int u = head[h];
	while(u)//�ӱ�ͷ��ʼ��������
	{
		if(memcpy(st[u],st[s],sizeof(st[s])) == 0)
			return 0;//�ҵ��� ����ʧ��
		u = mynext[u];
	}
	mynext[s] = head[h];//���뵽������
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



//BFS ����Ŀ��״̬��st�����±�
int bfs()
{
	init_lookup_table();//��ʼ�����ұ�
	int front = 1,rear = 2;//��ʹ���±�0 ��Ϊ0������ ������
	while (front < rear)
	{
		State& s = st[front];//�� ���� �򻯴���
		if(memcmp(goal,s,sizeof(s)) == 0)
			return front;//�ҵ�Ŀ��״̬ �ɹ�����

		int z;
		for(z=0;z<9;z++)
			if(!s[z])
				break;//�ҵ� 0 ��λ��

		int x = z/3;//�б��
		int y = z%3;//�б��
		for(int d=0;d<4;d++)
		{
			int newx = x + dx[d];
			int newy = y + dy[d];
			int newz = newx * 3 + newy;
			if(newx >=0 && newx<3 && newy>=0 && newy<3)//����ƶ��Ϸ�
			{
				State& t = st[rear];
				memcpy(&t,&s,sizeof(s));//��չ�½�� ��front�����ϱ䶯
				t[newz] = s[z];//0
				t[z] = s[newz];//��0������ֵ
				dist[rear] = dist[front] + 1;//���� �½��ľ���ֵ
				fa[rear] = front;
				dir[rear] = d;
				if(try_to_insert(rear))
					rear++;//����ɹ�������ұ� �޸Ķ�βָ��
			}
		}
		front++;
	}
	return 0;//ʧ��
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

	dir[1] = -1;//�ϴοո� �ƶ����� ���û��
	for(int i=0;i<9;i++)
		scanf_s("%d",&st[1][i]);
	for(int i=0;i<9;i++)
		scanf_s("%d",&goal[i]);
	int find;
	find = bfs();
	if(find)
	{
		printf("%d\n",dist[find]);
		//���ÿ�������ľŹ���
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