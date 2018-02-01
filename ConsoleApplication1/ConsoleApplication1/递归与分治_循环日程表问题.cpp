//n = 2^k ѡ�� ÿ��ѡ����N-1��ѡ�ָ�����һ��
//ÿ��ѡ��һ�����һ��
//�����N-1��
//����ճ̱� N��N-1�� (i,j)��iѡ���ڵ�j��������ѡ��
//
#include<iostream>
#include<string>
using namespace std;
const int MAXK = 10;
int calendar[1<<MAXK][1<<MAXK];
int vis[1<<MAXK][1<<MAXK];//��¼i,j��Ϊ���ֵĵ�day�� day=0��ʾû�г�Ϊ���� ֱ�� 0 1 ���Ҳ��
//ѡ�ֱ�Ŵ�0 �� n-1
//������Ŵ�1 �� n-1(ֻ����n-1��)
//���е�0�д� 0�� n-1 
//���ʱ�ӵ�0�� ��1�п�ʼ  ��ֵ+1 �������ѡ�ֱ�ž���1��ʼ��

//����1 �ݹ� ֻ���һ���ŷ�
//���ֳ�4�� ������ߵ�2�� Ȼ������ = ����,���� = ����
//k �����С
//x,y ���������Ͻ�
void getCalendar(int k,int x,int y)
{
	int halfsize = 1<<(k-1);
	if(k==1)//2 people
	{
		calendar[x][y+1] = x+1;
		calendar[x+1][y+1] = x;
		return;
	}
	//���¿�� ��������
	int p = x + halfsize;// x+2^(k-1);
	int q = y;
	
	getCalendar(k-1,x,y);//�ݹ����Ͽ�
	getCalendar(k-1,p,q);//�ݹ����¿�

	//���Ͽ� ��������
	int u = x;
	int v = y + halfsize;
	for(int i=0;i<halfsize;i++)
	{
		for (int j = 0; j < halfsize; j++)
		{
			calendar[u+i][v+j] = calendar[p+i][q+j];//�������¿� �� ���Ͽ�
		}
	}

	//���¿� ��������
	int s = x + halfsize;
	int t = y + halfsize;

	for(int i=0;i<halfsize;i++)
	{
		for (int j = 0; j < halfsize; j++)
		{
			calendar[s+i][t+j] = calendar[x+i][y+j];//�������¿� �� ���Ͽ�
		}
	}
	return;
}

void computeCalendar(int k)
{
	//init
	int size = 1<<k;
	for (int i = 0; i < size; i++)
	{
		calendar[i][0] = i;
	}
	//call method
	getCalendar(k,0,0);
}

//����2
//������vis��¼ ij�Ƿ��Ϊ������ �ܳ��Ľ����һ���ŷ� ���ݹ������һ�� 
void computeCalendar2(int k)
{
	//init
	int size = 1<<k;
	for (int i = 0; i < size; i++)
	{
		calendar[i][0] = i;
	}
	memset(vis,0,sizeof(vis));
	for (int i = 0; i < size; i++)
	{
		vis[i][i] = -1;//�Լ������Լ��� vis[][]==0 ����δ����
	}
	
	for(int day = 1; day < size; day++)// n-1 days
	{
		for(int player = 0; player < size; player++)//����ѡ�ֵ� ����
		{
			if(calendar[player][day] == -1)//������һ�컹û�а��Ŷ���
			{
				//��һ�� ��û�� �����ŵ� ����,�����������֮ǰû������ // ��ʱ 0 �� player-1 �������Ŷ�����
				for(int opponent = player+1; opponent < size; opponent++)
				{
					if(calendar[opponent][day] == -1 && !vis[player][opponent])
					{
						calendar[player][day] = opponent;
						calendar[opponent][day] = player;
						vis[player][opponent] = vis[opponent][player] = day;
						break;
					}
				}
			}
		}
	}
}


//��ӡ������Ϣ
void printCalendar(int k)
{
	int size = 1<<k;
	for(int i=0;i<size;i++)
	{
		for (int j = 0; j < size; j++)//֮���ٴӵ�һ�����
		{
			cout << calendar[i][j] << " ";
		}	
		cout << endl;
	}
}

//��ӡ������Ϣ ��ԭ����ԭ����������� ��0����ȥ ֵ+1
void printCalendar_2(int k)
{
	int size = 1<<k;
	for(int i=0;i<size;i++)
	{
		for (int j = 1; j < size; j++)//֮���ٴӵ�һ�����
		{
			cout << calendar[i][j] + 1 << " ";
		}	
		cout << endl;
	}
}


int main()
{
	int k;
	cin >> k;
	if(k>0 && k<MAXK)
	{
		memset(calendar,-1,sizeof(calendar));
		//computeCalendar(k);
		computeCalendar2(k);
		printCalendar(k);
	}
	getchar();
	getchar();
	return 0;


}
