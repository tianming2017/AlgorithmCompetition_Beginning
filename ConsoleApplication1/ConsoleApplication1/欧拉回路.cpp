//ŷ����· ����ͼ�д�һ�������� ÿ����ǡ�þ���һ�� "һ�ʻ�"
//���� ���������յ��� ������Ķ���Ӧ����ż��
//������� ��ͨ������ͼ ������ ���
//-----
//ŷ����· ��ͨ������ͼ ��������� ��������������

#include<stdio.h>
#include<stack>
#define MAXN 100

using namespace std;
int n;
int G[MAXN][MAXN];
int vis[MAXN][MAXN];
stack<int> s;

//����ͼ 
//����Ҫ��ӡŷ����· ��Ҫ���� ��·���
void euler(int u)
{
	for(int v=0;v<n;v++)
	{
		if(G[u][v] && !vis[u][v])//���ڱ���δ����   u -> v
		{
			vis[u][v] = vis[v][u] = 1;//��Ϊ����ͼ vis[u][v] = 1
			euler(v);
			printf("%d %d\n",u,v);//��ӡ��˳���������
		}
	}
}

int main()
{

	return 0;
}