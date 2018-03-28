//有n个人 第i个人重量为wi 每艘船最大载重为C 且最多只能乘坐2人
//用最少的船装载所有人
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN = 100;
const int C = 200;//假定载重为200
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
			//找一个与当前最轻的i 能配对的 最重的j
			//排除太重的人 同时让这些人 一个人坐船
			while(i<j && A[i]+A[j] > C)
			{
				j--;
				count++;//太重的 一个人坐船 
				//i不断变大 j不断变小 既然某个j不能和当前最轻的i配对 那以后更重的i显然不能配对
			}
			if(i==j)//配对失败 或者只剩下一个人
			{
				count++;//i一个人坐船
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
//输入n 和 n个人的重量
//输出 船的数量