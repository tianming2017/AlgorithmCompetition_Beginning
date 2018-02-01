//n������ n���� û��������ͬһֱ����
//������� �������� Ҫ��������������
//�������½� ��ʱ������ 
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN = 100;
struct point
{
	int id;
	int x;
	int y;
	int type;
	double angle;
};

point A[2*MAXN];//������
int B[2*MAXN];//��¼��һ���id

//[,]
void match(int left,int right)
{
	if (left >= right)
	{
		return;
	}

	//1. find ���½�
	int pos = left;
	for(int i=left; i<=right; i++)
	{
		if(A[i].y < A[pos].y || (A[i].y == A[pos].y && A[i].x < A[pos].x))
		{
			pos = i;
		}
	}

	//���½ǵĵ� ����A[left]
	point tmp = A[left];
	A[left] = A[pos];
	A[pos] = tmp;
	int minX = A[left].x;
	int minY = A[left].y;
	//2.angle 
	for (int i = left+1; i <= right; i++)
	{
		A[i].angle = atan2(A[i].y - minY,A[i].x - minX);//atan2
	}
	A[left].angle = 0; 
	//3.����angle���� ��A[left]��ʼ A[left],A[left+1]...A[right]
	int j;
	for (int i = left+1; i <= right; i++)
	{
		point temp = A[i];
		for(j=i; j-1>=left && A[j-1].angle > temp.angle; j--)
		{
			A[j] = A[j-1];
		}
		A[j] = temp;
	}
	//4.���� ֱ�� �������� == ��
	int type = 0;
	for (int i = left; i <= right; i++)
	{
		type += A[i].type;
		if(!type) //������ == �� ��ʱA[left]��A[i]��� ��¼�����Ϣ
		{
			B[A[left].id] = A[i].id;
			B[A[i].id] = A[left].id;
			match(left+1,i-1);
			match(i+1,right);
			return;
		}
	}

}

//������n������ ������n����
//�������id
int main()
{
	int n;
	cin >> n;
	int id;//������˳���ID
	if(n>0 && n<=MAXN)
	{
		id = 0;
		for (int i = 0; i < n; i++)//����
		{
			cin >> A[i].x >> A[i].y;
			A[i].type = 1;
			A[i].id = id++;
		}

		for (int i = 0; i < n; i++)//��
		{
			cin >> A[n+i].x >> A[n+i].y;
			A[n+i].type = -1;
			A[n+i].id = id++;
		}
		match(0,2*n-1);
	}
	for(int i = 0; i<2*n; i++)
	{
		cout << i << "---" << B[i] << endl;
	}
	getchar();
	getchar();
	return 0;

}