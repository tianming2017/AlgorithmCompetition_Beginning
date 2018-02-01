//包含n个 正 整数的序列划分成m个连续子序列(每个正整数恰好属于一个序列)
//设第i个序列的各数之和为S(i) 使得S(i)最大值尽量小
//1 2 3 2 5 4 划分3份 1 2 3 | 2 5 | 4
#include<iostream>
using namespace std;
const int MAXN = 100;
const int MAXSUM = 1e9;
int A[MAXN];
int n,m;

//能否将输入序列划分成m个连续的子序列 使得所有S(i)均不超过z?
//满足下面函数的最小z值 就是所求答案
//每次划分尽量向右划分
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

		int x=0,y=sum;//上下限 闭区间
		while(y-x>1)
		{
			int z = x + (y-x)/2;//二分法 猜数字
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