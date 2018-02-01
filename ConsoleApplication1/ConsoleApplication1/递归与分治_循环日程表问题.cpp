//n = 2^k 选手 每个选手与N-1个选手各比赛一次
//每个选手一天比赛一场
//则比赛N-1天
//设计日程表 N行N-1列 (i,j)第i选手在第j天遇到的选手
//
#include<iostream>
#include<string>
using namespace std;
const int MAXK = 10;
int calendar[1<<MAXK][1<<MAXK];
int vis[1<<MAXK][1<<MAXK];//记录i,j成为对手的第day天 day=0表示没有成为对手 直接 0 1 标记也行
//选手编号从0 到 n-1
//天数编号从1 到 n-1(只比赛n-1天)
//其中第0列存 0到 n-1 
//输出时从第0行 第1列开始  且值+1 这样结果选手编号就是1开始了

//方法1 递归 只求出一种排法
//划分成4块 计算左边的2块 然后右下 = 左上,右上 = 左下
//k 数组大小
//x,y 数组块的左上角
void getCalendar(int k,int x,int y)
{
	int halfsize = 1<<(k-1);
	if(k==1)//2 people
	{
		calendar[x][y+1] = x+1;
		calendar[x+1][y+1] = x;
		return;
	}
	//左下块的 左上坐标
	int p = x + halfsize;// x+2^(k-1);
	int q = y;
	
	getCalendar(k-1,x,y);//递归左上块
	getCalendar(k-1,p,q);//递归左下块

	//右上块 左上坐标
	int u = x;
	int v = y + halfsize;
	for(int i=0;i<halfsize;i++)
	{
		for (int j = 0; j < halfsize; j++)
		{
			calendar[u+i][v+j] = calendar[p+i][q+j];//复制左下块 到 右上块
		}
	}

	//右下块 左上坐标
	int s = x + halfsize;
	int t = y + halfsize;

	for(int i=0;i<halfsize;i++)
	{
		for (int j = 0; j < halfsize; j++)
		{
			calendar[s+i][t+j] = calendar[x+i][y+j];//复制左下块 到 右上块
		}
	}
	return;
}

void computeCalendar(int k)
{
	//init
	int size = 1<<k;
	for (int i = 0; i < size; i++)
	{
		calendar[i][0] = i;
	}
	//call method
	getCalendar(k,0,0);
}

//方法2
//这里用vis记录 ij是否成为过对手 跑出的结果就一种排法 跟递归出来的一样 
void computeCalendar2(int k)
{
	//init
	int size = 1<<k;
	for (int i = 0; i < size; i++)
	{
		calendar[i][0] = i;
	}
	memset(vis,0,sizeof(vis));
	for (int i = 0; i < size; i++)
	{
		vis[i][i] = -1;//自己不跟自己打 vis[][]==0 才是未访问
	}
	
	for(int day = 1; day < size; day++)// n-1 days
	{
		for(int player = 0; player < size; player++)//安排选手的 对手
		{
			if(calendar[player][day] == -1)//假如这一天还没有安排对手
			{
				//找一个 还没有 被安排的 对手,并且这个对手之前没遇到过 // 此时 0 到 player-1 都被安排对手了
				for(int opponent = player+1; opponent < size; opponent++)
				{
					if(calendar[opponent][day] == -1 && !vis[player][opponent])
					{
						calendar[player][day] = opponent;
						calendar[opponent][day] = player;
						vis[player][opponent] = vis[opponent][player] = day;
						break;
					}
				}
			}
		}
	}
}


//打印数组信息
void printCalendar(int k)
{
	int size = 1<<k;
	for(int i=0;i<size;i++)
	{
		for (int j = 0; j < size; j++)//之后再从第一列输出
		{
			cout << calendar[i][j] << " ";
		}	
		cout << endl;
	}
}

//打印数组信息 在原数组原样输出基础上 第0列舍去 值+1
void printCalendar_2(int k)
{
	int size = 1<<k;
	for(int i=0;i<size;i++)
	{
		for (int j = 1; j < size; j++)//之后再从第一列输出
		{
			cout << calendar[i][j] + 1 << " ";
		}	
		cout << endl;
	}
}


int main()
{
	int k;
	cin >> k;
	if(k>0 && k<MAXK)
	{
		memset(calendar,-1,sizeof(calendar));
		//computeCalendar(k);
		computeCalendar2(k);
		printCalendar(k);
	}
	getchar();
	getchar();
	return 0;


}
