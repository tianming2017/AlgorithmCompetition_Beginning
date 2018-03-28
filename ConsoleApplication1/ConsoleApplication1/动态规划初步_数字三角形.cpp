#include<iostream>
#include<algorithm>
using namespace std;
const int depth = 4;
int a[depth][depth];
int dis[depth][depth];
//�ӵ�һ������ʼ ÿ�ο��������»�������һ�� ֱ���ߵ������� ����;�����ּ����� ����߲���ʹ�ú����
//d(i,j) = a(i,j) + max{d(i+1,j) , d(i+1,j+1)}


void initArray()
{
	memset(a,0,sizeof(a));
	a[0][0] = 1;
	a[1][0] = 3;
	a[1][1] = 2;
	a[2][0] = 4;
	a[2][1] = 10;
	a[2][2] = 1;
	a[3][0] = 4;
	a[3][1] = 3;
	a[3][2] = 2;
	a[3][3] = 20;
	memset(dis,-1,sizeof(dis));
}

//method1 
//�ݹ���� �ظ�������
int d(int i,int j)
{
	if(i == depth - 1)//�ݹ����
	{
		return a[i][j];
	}
	return a[i][j] + max(d(i+1,j), d(i+1,j+1));
}

//���Ƽ���
int d2()
{
	int i,j;
	for(j=0;j<depth;j++)
	{
		dis[depth-1][j] = a[depth-1][j];//�߽�
	}
	for(i=depth-2; i>=0; i--)//����ö�� ����
	{
		for(j=0; j<=i; j++)
		{
			dis[i][j] = a[i][j] + max(dis[i+1][j],dis[i+1][j+1]);
		}
	}
	return dis[0][0];
}

//���仯���� 
//����ʵ��ȷ����״̬�ļ���˳��
//��Ҫ��¼ÿ��״̬�ġ��Ƿ��Ѿ��������
int d3(int i,int j)
{
	if(i == depth-1)//�ݹ����
	{
		return dis[i][j] = a[i][j];//��ֵ��䱾���з���ֵ
	}
	if(dis[i][j] >= 0)
	{
		return dis[i][j];//�Ѿ��������
	}
	return dis[i][j] = a[i][j] + max(d3(i+1,j),d3(i+1,j+1));
}


int main()
{
	initArray();
	//int res = d(0,0);
	//int res = d2();
	int res = d3(0,0);
	cout << res << endl;
	getchar();
}
