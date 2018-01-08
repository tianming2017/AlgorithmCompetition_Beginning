//2^k * 2^k �������� ֻ��1����ɫ  �����ɫ
//�ð������������L�͸������еİ�ɫ����
//��ɫ���ܱ����� �����ɫ������ͬʱ�������������Ƹ���
//  *	* 	 **	  **
// **	**    *	  *
//  1	2 	 33	  44
// 11	22	  3	  4 
//��ɫ 0
//-1��ʾ��δ���
#include<iostream>
#include<string>
using namespace std;
const int MAXK = 10;
int chess[1<<MAXK][1<<MAXK];

//x,yȷ���������Ͻ�
//k�������̴�С 2^k
//i,j��ʾ ��ǰ�����е� һ���ڿ�(�����ڿ�)
//ֻ��֤��������Ϸ����������
void fillChess(int k,int x,int y,int i,int j)
{
	//may add valid process

	if(k==1)//����������2*2��
	{
		//chess[][] >=0 ��ʾ�Ѿ����(�ڿ� ����ڿ�(���׿�) �׿�); -1��ʾΪ���
		if(chess[x][y] >= 0)
		{
			chess[x][y+1] = chess[x+1][y] = chess[x+1][y+1] = 1;//1��
		}
		else if (chess[x][y+1] >= 0)
		{
			chess[x][y] = chess[x+1][y] = chess[x+1][y+1] = 2;//2��
		}
		else if (chess[x+1][y] >= 0)
		{
			chess[x][y] = chess[x][y+1] = chess[x+1][y+1] = 3;//3��
		}
		else//chess[x+1][y+1] >=0
		{
			chess[x][y] = chess[x][y+1] = chess[x+1][y] = 4;//4��
		}
		return;//�ݹ����
	}
	//�жϺڿ�����4�������е���һ������?
	//��ǰ���� �ķ�֮һ���С��(���Ͽ�) �� ���½�����(x+2^(k-1)-1, y+2^(k-1)-1)
	int p = x + (1<<(k-1)) -1;
	int q = y + (1<<(k-1)) -1;
	if(i<=p && j<=q)//�ڿ��� ���� 1/4 ��
	{
		//1.���ü���ڿ� ������3�� 1/4��� �� (p,q) ���ڵ� ������ ����
		chess[p][q+1] = chess[p+1][q] = chess[p+1][q+1] = 1;//1��
		//2.�ݹ����
		fillChess(k-1,x,y,i,j);
		fillChess(k-1,x,q+1,p,q+1);
		fillChess(k-1,p+1,y,p+1,q);
		fillChess(k-1,p+1,q+1,p+1,q+1);
	}
	else if (i<=p && j>q)//����
	{
		chess[p][q] = chess[p+1][q] = chess[p+1][q+1] = 2;

		fillChess(k-1,x,y,p,q);
		fillChess(k-1,x,q+1,i,j);
		fillChess(k-1,p+1,y,p+1,q);
		fillChess(k-1,p+1,q+1,p+1,q+1);
	}
	else if (i>p && j<=q)//����
	{
		chess[p][q] = chess[p][q+1] = chess[p+1][q+1] = 3;

		fillChess(k-1,x,y,p,q);
		fillChess(k-1,x,q+1,p,q+1);
		fillChess(k-1,p+1,y,i,j);
		fillChess(k-1,p+1,q+1,p+1,q+1);
	}
	else//����
	{
		chess[p][q] = chess[p][q+1] = chess[p+1][q] = 4;

		fillChess(k-1,x,y,p,q);
		fillChess(k-1,x,q+1,p,q+1);
		fillChess(k-1,p+1,y,p+1,q);
		fillChess(k-1,p+1,q+1,i,j);
	}
}

void printChess(int k)
{
	int maxn = 1<<k;
	for (int i = 0; i < maxn; i++)
	{
		for (int j = 0; j < maxn; j++)
		{
			cout << chess[i][j] << " ";
		}
		cout << endl;
	}
}

//������ʾЧ��һ���
//���ͬһ���ͺŵ�L ������ �������Ͳ�̫���

int main()
{
	int k;
	int i,j;
	cin >> k;
	if(k>0 && k<=MAXK)
	{
		int maxn = 1<<k;//2^k
		while(scanf_s("%d%d",&i,&j) == 2 && i>=0 && i<maxn && j>=0 && j<maxn)
		{
			memset(chess,-1,sizeof(chess));

			//set black point
			chess[i][j] = 0;

			fillChess(k,0,0,i,j);

			printChess(k);	
		}
	}
	getchar();
	return 0;
}