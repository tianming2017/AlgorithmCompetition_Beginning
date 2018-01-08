//copy from Baidu
#include<cstdio>
#include<string>
using namespace std;
const int MAXN = 1000;//ˮ���������
int cap[3],x;
int vis[MAXN][MAXN];//�±��� �б� �� С���ĵ�ǰˮ��

//state���� 0,1,2�浱ǰˮ��;
//3�游�ڵ��±�;4�沽����;5���ϲ���Ĳ���
//��0<=i,j<=2 i������j���ӵ�ˮ ��Ѳ�����Ϊ i*10+j
//st�ĵ�һά�ȿ���Ϊ����
int st[MAXN*MAXN][6];

void printPath(int index)
{
	if(st[index][3]!=-1)//��ʼ״̬�ĸ��ڵ���Ϊ-1 �����жϵݹ����
		printPath(st[index][3]);
	printf("(%d,%d,%d) ",st[index][0],st[index][1],st[index][2]);
}

int bfs()
{
	int front = 0;
	int rear = 1;//ʵ�����һ����ֵ���±� +1
	vis[st[front][1]][st[front][2]] = 1;
	int ok=0;
	int tmpstate[6];
	while(front < rear)//top pop��ȡfront����; дrear����push; front���ݲ�Ӧ�ñ��ı�
	{
		//top 
		if(st[front][0] == x || st[front][1] == x || st[front][2] == x)//find
		{
			ok = 1;
			//bfs breakʱ�� front��û++ ��û�г��� front��Ϊ��Ҫ���±�
			//���·��
			printPath(front);
			printf("\n");
			break;
		}

		//���Ǹ��ֵ�ˮ��� push 
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
			{
				if(i!=j)//�Լ��������Լ���ˮ
				{
					//copy state from front(queue top) ��Ӧ�ı�ǰһ״̬
					for(int k=0;k<6;k++)
						tmpstate[k] = st[front][k];//��ˮ��ʱ�� ֻ������ˮ��ı�ˮ��  ��������ˮ������

					//i��j��ˮ ����i��ˮ j û��
					if(tmpstate[i] > 0 && tmpstate[j] < cap[j])
					{
						//Ҳ���Լ���ˮ�ı� ��amount ���⸳ֵ˳��Ӱ��
						if(tmpstate[i] + tmpstate[j] >= cap[j])//j full
						{
							tmpstate[i] = tmpstate[i] - (cap[j] - tmpstate[j]);//ע�����
							tmpstate[j] = cap[j];
						}
						else//i empty
						{
							tmpstate[j] = tmpstate[i] + tmpstate[j];//ע�����
							tmpstate[i] = 0;
						}
						//����һ����״̬
						//�����״̬��δ���� ���
						if(!vis[tmpstate[1]][tmpstate[2]])
						{
							//visit
							vis[tmpstate[1]][tmpstate[2]] = 1;
							tmpstate[3] = front;
							tmpstate[4]++;
							tmpstate[5] = i*10 + j;
							//push
							for(int k=0;k<6;k++)
								st[rear][k] = tmpstate[k];
							rear++;
						}
					}
				}
			}
		}//end ͬһ��front״̬�µĸ��ֵ�ˮ���
		//
		front++;//pop front
	}
	return ok;
}

int main()
{
	while(scanf_s("%d%d%d%d",&cap[0],&cap[1],&cap[2],&x) == 4 && cap[0]<MAXN && cap[1]<cap[0] && cap[2]<cap[1] && cap[2]>0 && x>0 && x<cap[0])
	{
		memset(vis,0,sizeof(vis));
		memset(st,0,sizeof(st));
		//�趨��ʼ״̬
		st[0][0] = cap[0];
		st[0][1] = 0;
		st[0][2] = 0;
		st[0][3] = -1;//�Լ����ǳ�ʼ״̬�� ���ڵ�
		st[0][4] = 0;//steps = 0
		st[0][5] = -1;//no previous step
		if(!bfs())//�ɹ��Ļ� ����bfs���
			printf("Can not find Path!\n");
	}
	getchar();
	return 0;
}