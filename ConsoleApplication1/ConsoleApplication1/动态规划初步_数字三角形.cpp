#include<iostream>
#include<algorithm>
using namespace std;
const int depth = 4;
int a[depth][depth];
int dis[depth][depth];
//从第一行数开始 每次可以往左下或右下走一格 直到走到最下行 把沿途的数字加起来 如何走才能使得和最大
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
//递归计算 重复了子树
int d(int i,int j)
{
	if(i == depth - 1)//递归出口
	{
		return a[i][j];
	}
	return a[i][j] + max(d(i+1,j), d(i+1,j+1));
}

//递推计算
int d2()
{
	int i,j;
	for(j=0;j<depth;j++)
	{
		dis[depth-1][j] = a[depth-1][j];//边界
	}
	for(i=depth-2; i>=0; i--)//逆序枚举 行数
	{
		for(j=0; j<=i; j++)
		{
			dis[i][j] = a[i][j] + max(dis[i+1][j],dis[i+1][j+1]);
		}
	}
	return dis[0][0];
}

//记忆化搜索 
//不必实现确定各状态的计算顺序
//需要记录每个状态的“是否已经计算过”
int d3(int i,int j)
{
	if(i == depth-1)//递归出口
	{
		return dis[i][j] = a[i][j];//赋值语句本身有返回值
	}
	if(dis[i][j] >= 0)
	{
		return dis[i][j];//已经计算过了
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
