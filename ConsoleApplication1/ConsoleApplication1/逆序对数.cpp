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
	if(y-x>1)//个数y-x; 2个及以上就拆分递归合并
	{
		int m = x + (y-x)/2;
		int p = x;//[x,m)
		int q = m;//[m,y)
		int i = x;
		int cnt1 = merge_count(A,x,m,T);
		int cnt2 = merge_count(A,m,y,T);
		//考虑i在[x,m) j在[m,y)情况
		while(p<m || q<y)//左边 右边都已经排序了
		{
			if(q>=y || (p<m && A[p] <= A[q]))
				T[i++] = A[p++];
			else
			{
				T[i++] = A[q++];
				cnt += m-p;//由于合并操作是从小到大进行的， 当右边的A[q]复制到T中时 左边还没来得及复制到T的那些数就是左边 所有比A[q]大的数
			}
		}
		for(i=x; i<y; i++)
			A[i] = T[i];
		cnt += cnt1 + cnt2;	
	}
	return cnt;
}

//下面这个肯定是对的
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