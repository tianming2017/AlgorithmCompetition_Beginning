#include<stdio.h>
#include<memory.h>
#define MAXN 40
int n;
int tot = 0;//��ĸ���
int tot2 = 0;
int C[MAXN];
int vis[2][MAXN*2];

//cur ��ǰ��
void search(int cur)
{
	int i,j;
	if(cur == n)//�ݹ�߽� ֻҪ�ߵ����� ���лʺ��Ȼ����ͻ
	{
		tot++;
		////������
		//for(i=0;i<n;i++)
		//	printf("%d ",C[i]);
		//printf("\n");
	}
	else
	{
		for(i=0;i<n;i++)//������
		{
			int ok = 1;
			C[cur] = i;//���԰ѵ�cur�еĻʺ���ڵ�i��
			for(j = 0;j<cur;j++)//��֤�Ƿ��ͻ
			{
				if(C[cur] == C[j] || cur-C[cur] == j-C[j] || cur+C[cur] == j+C[j])//һ�� ���Խ��� ���Խ���
				{
					ok = 0;
					break;
				}
			}
			if(ok)
				search(cur+1);
		}
	}
}

//���ö�ά����vis[2][] ��ȡ�Ѿ���ռ�õ��� ���Խ��� ���Խ���
void search2(int cur)
{
	int i;
	if(cur == n)
		tot2++;
	else
	{
		for(i=0;i<n;i++)
		{
			if(!vis[0][i] && !vis[1][cur+i] && !vis[2][cur-i+n])//�� ���Խ��� ���Խ��� ��û�б�����
			{
				C[cur] = i;//cur�еĻʺ� ���ڵ�i��
				vis[0][i] = vis[1][cur+i] = vis[2][cur-i+n] = 1;//�޸�ȫ�ֱ���, ռ����
				search2(cur+1);
				vis[0][i] = vis[1][cur+i] = vis[2][cur-i+n] = 0;//��ԭ!!!
			}
		}
	}	
}

//һ��һ�зŻʺ�
int main()
{
	while(scanf_s("%d",&n)==1 && n>0 && n<MAXN)
	{
		memset(C,0,sizeof(C));
		memset(vis,0,sizeof(vis));

		tot = 0;
		tot2 = 0;
		search(0);
		search2(0);
		printf("�������: %d\n",tot);
		printf("�������: %d\n",tot2);
	}
	getchar();
	return 0;
}