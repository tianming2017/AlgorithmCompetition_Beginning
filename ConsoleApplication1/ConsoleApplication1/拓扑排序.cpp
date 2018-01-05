//n������(���)
//m����Ԫ��(u,v)---u �� v����һ�������
//��������һ����������(�����޻�ͼ ǰ��֮��)
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include<queue>

#define MAXN 100
using namespace std;
//c[u]=0 ��δ����;
//c[u]=1�Ѿ�����,���ҵݹ���ʹ���������;
//c[u]=-1��ʾ���ڷ���(�ݹ����dfs(u)����ջ֡��,��δ����) ��������
int c[MAXN];
int topo[MAXN],t;//������� �Լ� �±�,ֱ�Ӵ�0����n����Ҫ������
int G[MAXN][MAXN];//�ڽӾ��� ��ʾ��ͼ
int n,m;//n����� m����

int Indegree[MAXN];//���
int topoNum[MAXN];//��i����������� �������������� ֵΪ0,1,2,3...

//�ݹ��dfs
//������������򹹳ɵ�
bool dfs(int u)
{
	c[u] = -1;
	for(int v=0;v<n;v++)
	{
		if(G[u][v])//u -> v
		{
			if(c[v]<0) return false;//�������� ʧ���˳�
			else if(c[v]==0 && !dfs(v)) return false;//��δ���ʹ�v;�ݹ����v;����v��dfs ʧ�ܵĻ�
			//����c[v]=1 do Nothing
		}
	}
	c[u] = 1;
	topo[--t] = u;
	return true;
}

//����dfsʵ����������
//��0�Ž�㿪ʼdfs
bool toposort()
{
	t = n;
	memset(c,0,sizeof(c));//��ʼ��Ϊ δ����
	for(int u=0;u<n;u++)//��ÿһ����� ���û������� ������
	{
		if(c[u]==0)
		{
			if(!dfs(u)) return false;	
		}	
	}
	return true;
}

//���ڽӾ�������� 
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

//���ݽṹ���ϵ��㷨 �е�BFS�ĸо�
//�ҵ�����һ�����Ϊ0�Ķ��� ��� �����ڽ����ȼ���1
bool toposort_2()
{
	calculateIndegree();
	queue<int> q;
	int count = 0;
	//�����=0�Ķ��� �ŵ������� ���г�ʼ��
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
		//��v���ڵ�ÿ������
		for(int w=0;w<n;w++)
		{
			if(G[v][w]!=0)//v->w ����
			{
				if(--Indegree[w]==0)//��һ�� ���Ϊ0
				{
					q.push(w);
				}
			}
		}
	}
	if(count != n) return false;//��
	return true;
}

int main()
{
	scanf_s("%d%d",&n,&m);
	//����G[][]
	memset(G,0,sizeof(G));
	memset(topo,-1,sizeof(topo));
	memset(topoNum,-1,sizeof(topoNum));


	//0 'a'; 1 'b';...
	char s1,s2;
	for(int i=0;i<m;i++)
	{
		//(1)��getchar()��� 
		//(2)��"%1s"������ 
		//(3)�ø�ʽ���пո��"%*c"��"�Ե�" 
		//(4)�ú���fflush(stdin)���ȫ��ʣ������ 
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