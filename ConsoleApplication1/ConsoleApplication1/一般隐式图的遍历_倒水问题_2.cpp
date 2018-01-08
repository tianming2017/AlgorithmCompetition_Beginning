//copy from Baidu
#include<cstdio>
#include<string>
using namespace std;
const int MAXN = 1000;//水量最大上限
int cap[3],x;
int vis[MAXN][MAXN];//下标是 中杯 和 小杯的当前水量

//state数组 0,1,2存当前水量;
//3存父节点下标;4存步骤数;5存上步骤的操作
//若0<=i,j<=2 i杯子向j杯子倒水 则把操作记为 i*10+j
//st的第一维度可作为队列
int st[MAXN*MAXN][6];

void printPath(int index)
{
	if(st[index][3]!=-1)//初始状态的父节点设为-1 用于判断递归结束
		printPath(st[index][3]);
	printf("(%d,%d,%d) ",st[index][0],st[index][1],st[index][2]);
}

int bfs()
{
	int front = 0;
	int rear = 1;//实际最后一个有值的下标 +1
	vis[st[front][1]][st[front][2]] = 1;
	int ok=0;
	int tmpstate[6];
	while(front < rear)//top pop读取front数据; 写rear数据push; front数据不应该被改变
	{
		//top 
		if(st[front][0] == x || st[front][1] == x || st[front][2] == x)//find
		{
			ok = 1;
			//bfs break时候 front还没++ 还没有出队 front即为需要的下标
			//输出路径
			printPath(front);
			printf("\n");
			break;
		}

		//考虑各种倒水情况 push 
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
			{
				if(i!=j)//自己不能向自己倒水
				{
					//copy state from front(queue top) 不应改变前一状态
					for(int k=0;k<6;k++)
						tmpstate[k] = st[front][k];//倒水的时候 只有两杯水会改变水量  其他杯子水量不变

					//i向j倒水 首先i有水 j 没满
					if(tmpstate[i] > 0 && tmpstate[j] < cap[j])
					{
						//也可以计算水改变 量amount 避免赋值顺序影响
						if(tmpstate[i] + tmpstate[j] >= cap[j])//j full
						{
							tmpstate[i] = tmpstate[i] - (cap[j] - tmpstate[j]);//注意次序
							tmpstate[j] = cap[j];
						}
						else//i empty
						{
							tmpstate[j] = tmpstate[i] + tmpstate[j];//注意次序
							tmpstate[i] = 0;
						}
						//产生一种新状态
						//如果此状态从未出现 入队
						if(!vis[tmpstate[1]][tmpstate[2]])
						{
							//visit
							vis[tmpstate[1]][tmpstate[2]] = 1;
							tmpstate[3] = front;
							tmpstate[4]++;
							tmpstate[5] = i*10 + j;
							//push
							for(int k=0;k<6;k++)
								st[rear][k] = tmpstate[k];
							rear++;
						}
					}
				}
			}
		}//end 同一个front状态下的各种倒水情况
		//
		front++;//pop front
	}
	return ok;
}

int main()
{
	while(scanf_s("%d%d%d%d",&cap[0],&cap[1],&cap[2],&x) == 4 && cap[0]<MAXN && cap[1]<cap[0] && cap[2]<cap[1] && cap[2]>0 && x>0 && x<cap[0])
	{
		memset(vis,0,sizeof(vis));
		memset(st,0,sizeof(st));
		//设定初始状态
		st[0][0] = cap[0];
		st[0][1] = 0;
		st[0][2] = 0;
		st[0][3] = -1;//自己就是初始状态了 父节点
		st[0][4] = 0;//steps = 0
		st[0][5] = -1;//no previous step
		if(!bfs())//成功的话 会在bfs输出
			printf("Can not find Path!\n");
	}
	getchar();
	return 0;
}