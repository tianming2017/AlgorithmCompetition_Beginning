//����n������ͼG  ��һ����������
//define ���i����b(i) = i �����ڽ���������е���Զ���� 
//ͼ�Ĵ��� = max(b(i),0<=i<n)
//����ͼG ����ô�����С�Ľ������
//�ݹ�ö��ȫ���� + ��֦(��¼�µ�ǰ��С����k)
//��֦1 ĳ�������ľ��� dis>= k
//��֦2 ���u��ʣ�����ڽ����� m>=k
#include<cstdio>
#include<memory.h>
#include<algorithm>
using namespace std;
const int MAXN = 10;
int G[MAXN][MAXN];//�ڽӾ���
int n;//������
int b[MAXN];//�� ���п�������
int res[MAXN];//�� ���
//---------
//copy from CSDN
int vis[MAXN];
int deg[MAXN];//���ڽ�����
int perm[MAXN];
int bestperm[MAXN];
int bestw = MAXN;//ĿǰΪֹ��С�Ĵ���
int maxw = -1;//ĿǰΪֹ�Ĵ���

//��֪���Բ���...����
//��дһ��n!��low�㷨
int findIndex(int x)
{
	for(int i=0;i<n;i++)
		if(b[i] == x)
			return i;
	return -1;
}
void bandwidth()
{
	int k = MAXN;//��ʼֵ���һ��
	do
	{
		int bi = 0;//���i�Ŀ�� max
		int bg = 0;//ͼ
		int tmp = 0;

		for(int i=0;i<n;i++)//���i
		{
			for(int j=0;j<n;j++)
			{
				if(G[i][j])//���i�����ڵ�
				{
					//��b[]��ֵΪi,j֮��ľ���
					int ii = findIndex(i);
					int jj = findIndex(j);
					if(ii!=-1 && jj!=-1)
					{
						tmp = abs(ii-jj);
					}
					if(tmp > bi)
						bi = tmp;
				}
			}
			if(bi>bg)
				bg = bi;
		}
		if(k>bg)
		{
			k = bg;
			for(int i=0;i<n;i++)
				res[i] = b[i];
		}
	}while(next_permutation(b,b+n));

}


//CSDN
void search_width(int cur)
{
	if(cur >= n)
	{
		if(maxw < bestw)
		{
			for(int i=0;i<n;i++)
				bestperm[i] = perm[i];
			bestw = maxw;
		}
		return;
	}
	for(int i=0;i<n;i++)//��������
	{
		if(!vis[i])
		{
			int tmp = maxw;
			vis[i] = 1;
			perm[cur] = i;//curλ�� ��i
			int left = deg[i];
			for(int k=0;k<cur;++k)
			{
				if(G[i][perm[k]])
				{
					if(cur-k > maxw)
						maxw = cur-k;//���ڽ�����Զ����
					if(maxw < bestw)
						--left;
					else
						break;//�����������ڽ��ľ��� >= ��С����   ��֦ 
				}
			}
			if(maxw<bestw)
			{
				if(left < bestw)//���i��ʣ�����ڽ�����  < ��С����
				{
					search_width(cur+1);
				}
			
			}
			vis[i] = 0;
			maxw = tmp;
		}
	}
}

//�ճ�Ĭд
void search_width_2(int cur)
{
	if(cur >= n)
	{
		if(maxw<bestw)
		{
			bestw = maxw;
			for(int i=0;i<n;i++)
				bestperm[i] = perm[i];
		}
		return;
	}
	for (int i = 0; i < n; i++)//����ȡֵ ��i���
	{
		if(!vis[i])
		{
			vis[i] = 1;
			perm[cur] = i;
			int tmp = maxw;
			int left = deg[i];
			//�ж�curλ�÷�i �ɲ�����
			for (int j = 0; j < cur; j++)//�Ѿ��е�ֵ���±�
			{
				if(G[i][perm[j]])
				{
					left--;
					if(cur - j > maxw)
						maxw = cur - j;//����ÿ����� �� ���ڽ�� ȡ������Զ��
					if(maxw >= bestw)
						break;
				}
			}
			if(maxw<bestw && left<bestw)
				search_width_2(cur+1);

			maxw = tmp;
			vis[i] = 0;
		}
	}
}


int main()
{

	while(scanf_s("%d",&n) == 1 && n>0 && n<=MAXN)
	{
		//init
		memset(G,0,sizeof(G));
		memset(b,0,sizeof(b));
		memset(vis,0,sizeof(vis));
		memset(deg,0,sizeof(deg));
		bestw = MAXN;
		maxw = -1;


		//read G
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
			{
				scanf_s("%d",&G[i][j]);
				deg[i] += G[i][j];
			}
		//may check G valid
		////init b[] 0,1,2,3,...,n-1
		//for(int i=0;i<n;i++)
		//	b[i] = i;

		//bandwidth();
		search_width_2(0);
		for(int i=0;i<n;i++)
			printf("%d ",bestperm[i]);
		printf("\n%d\n",bestw);

	}
	getchar();
	return 0;
}