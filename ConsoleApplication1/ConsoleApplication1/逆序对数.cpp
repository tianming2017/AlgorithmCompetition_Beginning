//a1,a2,a3,...,an (i,j) i<j, ai>aj, n can be 10e6
#include<cstdio>
#include<iostream>
//[x,y) [0,n)
//[x,m) [m,y)
using namespace std;
const int MAXN = 1000000;
int A[MAXN];
int B[MAXN];
int T[MAXN];
int merge_count(int* A,int x,int y,int* T)
{
	int cnt = 0;
	if(y-x>1)//����y-x; 2�������ϾͲ�ֵݹ�ϲ�
	{
		int m = x + (y-x)/2;
		int p = x;//[x,m)
		int q = m;//[m,y)
		int i = x;
		int cnt1 = merge_count(A,x,m,T);
		int cnt2 = merge_count(A,m,y,T);
		//����i��[x,m) j��[m,y)���
		while(p<m || q<y)//��� �ұ߶��Ѿ�������
		{
			if(q>=y || (p<m && A[p] <= A[q]))
				T[i++] = A[p++];
			else
			{
				T[i++] = A[q++];
				cnt += m-p;//���ںϲ������Ǵ�С������еģ� ���ұߵ�A[q]���Ƶ�T��ʱ ��߻�û���ü����Ƶ�T����Щ��������� ���б�A[q]�����
			}
		}
		for(i=x; i<y; i++)
			A[i] = T[i];
		cnt += cnt1 + cnt2;	
	}
	return cnt;
}

//��������϶��ǶԵ�
int reverseCount(int* A,int n)
{
	int cnt = 0;
	for(int i=0;i<n;i++)
		for(int j=i+1;j<n;j++)
			if(A[i] > A[j])
				cnt++;
	return cnt;
}


int main()
{
	int n;
	while(scanf_s("%d",&n) == 1)
	{
		for(int i=0;i<n;i++)
		scanf_s("%d",&A[i]);
		memcpy(B,A,sizeof(int)*n);

		int count;
		count = merge_count(A,0,n,T);
		cout << count << endl;
		count = reverseCount(B,n);
		cout << count << endl;

	}
	
	getchar();
	getchar();
	return 0;
}