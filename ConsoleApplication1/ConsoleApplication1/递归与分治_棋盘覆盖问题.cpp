//2^k * 2^k 方格棋盘 只有1个黑色  其余白色
//用包含三个方格的L型覆盖所有的白色方格
//黑色不能被覆盖 任意白色方格不能同时被两个或以上牌覆盖
//  *	* 	 **	  **
// **	**    *	  *
//  1	2 	 33	  44
// 11	22	  3	  4 
//黑色 0
//-1表示尚未填充
#include<iostream>
#include<string>
using namespace std;
const int MAXK = 10;
int chess[1<<MAXK][1<<MAXK];

//x,y确定棋盘左上角
//k决定棋盘大小 2^k
//i,j表示 当前棋盘中的 一个黑块(或假想黑块)
//只保证输入参数合法情况下运行
void fillChess(int k,int x,int y,int i,int j)
{
	//may add valid process

	if(k==1)//这是棋盘是2*2的
	{
		//chess[][] >=0 表示已经填充(黑块 假想黑块(即白块) 白块); -1表示为填充
		if(chess[x][y] >= 0)
		{
			chess[x][y+1] = chess[x+1][y] = chess[x+1][y+1] = 1;//1型
		}
		else if (chess[x][y+1] >= 0)
		{
			chess[x][y] = chess[x+1][y] = chess[x+1][y+1] = 2;//2型
		}
		else if (chess[x+1][y] >= 0)
		{
			chess[x][y] = chess[x][y+1] = chess[x+1][y+1] = 3;//3型
		}
		else//chess[x+1][y+1] >=0
		{
			chess[x][y] = chess[x][y+1] = chess[x+1][y] = 4;//4型
		}
		return;//递归出口
	}
	//判断黑块落在4个区域中的哪一个区域?
	//求当前棋盘 四分之一块大小的(左上块) 的 右下角坐标(x+2^(k-1)-1, y+2^(k-1)-1)
	int p = x + (1<<(k-1)) -1;
	int q = y + (1<<(k-1)) -1;
	if(i<=p && j<=q)//黑块在 左上 1/4 块
	{
		//1.设置假想黑块 在另外3个 1/4块的 和 (p,q) 相邻的 角落里 设置
		chess[p][q+1] = chess[p+1][q] = chess[p+1][q+1] = 1;//1型
		//2.递归调用
		fillChess(k-1,x,y,i,j);
		fillChess(k-1,x,q+1,p,q+1);
		fillChess(k-1,p+1,y,p+1,q);
		fillChess(k-1,p+1,q+1,p+1,q+1);
	}
	else if (i<=p && j>q)//右上
	{
		chess[p][q] = chess[p+1][q] = chess[p+1][q+1] = 2;

		fillChess(k-1,x,y,p,q);
		fillChess(k-1,x,q+1,i,j);
		fillChess(k-1,p+1,y,p+1,q);
		fillChess(k-1,p+1,q+1,p+1,q+1);
	}
	else if (i>p && j<=q)//左下
	{
		chess[p][q] = chess[p][q+1] = chess[p+1][q+1] = 3;

		fillChess(k-1,x,y,p,q);
		fillChess(k-1,x,q+1,p,q+1);
		fillChess(k-1,p+1,y,i,j);
		fillChess(k-1,p+1,q+1,p+1,q+1);
	}
	else//右下
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

//最终显示效果一般般
//如果同一种型号的L 相邻了 看起来就不太舒服

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