//��n���� ��i��������Ϊwi ÿ�Ҵ��������ΪC �����ֻ�ܳ���2��
//�����ٵĴ�װ��������
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN = 100;
const int C = 200;//�ٶ�����Ϊ200
int A[MAXN];

int main()
{
	int n;
	cin >> n;
	if(n>0 && n<MAXN)
	{
		for (int k = 0; k < n; k++)
		{
			cin >> A[k];
		}
		sort(A,A+n);
		int i,j,count;
		i = 0;
		j = n-1;
		count = 0;

		while(i<=j)
		{
			//��һ���뵱ǰ�����i ����Ե� ���ص�j
			//�ų�̫�ص��� ͬʱ����Щ�� һ��������
			while(i<j && A[i]+A[j] > C)
			{
				j--;
				count++;//̫�ص� һ�������� 
				//i���ϱ�� j���ϱ�С ��Ȼĳ��j���ܺ͵�ǰ�����i��� ���Ժ���ص�i��Ȼ�������
			}
			if(i==j)//���ʧ�� ����ֻʣ��һ����
			{
				count++;//iһ��������
				break;
			}
			else
			{
				count++;
				i++;
				j--;
			}

		}
		cout << count << endl;
	}
	getchar();
	getchar();
	return 0;

}
//����n �� n���˵�����
//��� ��������