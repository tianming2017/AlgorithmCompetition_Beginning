//����n�� �� ���������л��ֳ�m������������(ÿ��������ǡ������һ������)
//���i�����еĸ���֮��ΪS(i) ʹ��S(i)���ֵ����С
//1 2 3 2 5 4 ����3�� 1 2 3 | 2 5 | 4
#include<iostream>
using namespace std;
const int MAXN = 100;
const int MAXSUM = 1e9;
int A[MAXN];
int n,m;

//�ܷ��������л��ֳ�m�������������� ʹ������S(i)��������z?
//�������溯������Сzֵ ���������
//ÿ�λ��־������һ���
int is_ok(int z)
{
	int sum=0;
	int count = 1;
	for (int i = 0; i < n; i++)
	{
		if(sum + A[i] <= z)
		{
			sum += A[i];
		}
		else
		{
			sum = A[i];
			count++;
		}
	}
	if(count <= m)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}


int main()
{
	int sum=0;
	cin >> n >> m;
	if(n>0 && n<MAXN && m>0)
	{
		for (int i = 0; i < n; i++)
		{
			cin >> A[i];
			sum += A[i];
		}

		int x=0,y=sum;//������ ������
		while(y-x>1)
		{
			int z = x + (y-x)/2;//���ַ� ������
			if(is_ok(z))
			{
				y = z;//y always ok, finally output y
			}
			else
			{
				x = z;
			}
		}
		cout << y <<endl;
	}
	getchar();
	getchar();
	return 0;

}
//6 3
//1 2 3 2 5 4
//output 7