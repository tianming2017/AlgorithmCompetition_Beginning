#include<cstdio>
#include<stack>
using namespace std;
const int MAXN = 1000 + 10;

int n, target[MAXN];

int main()
{
	while(scanf_s("%d",&n) == 1)//多少辆 车
	{
		stack<int> s;
		int A=1,B=1;//A方向的车 默认为 1~n//某个方向第几辆车
		for(int i=1;i<=n;i++)
		{
			scanf_s("%d",&target[i]);//B方向 离开的车的编号
		}
		int ok = 1;
		while(B<=n)
		{
			if(A==target[B]){A++; B++;}//不需要堆栈
			else if(!s.empty() && s.top() == target[B])//看看堆栈顶是不是想要的
			{
				s.pop();
				B++;
			}
			else if(A<=n){s.push(A++);}//入栈
			else {ok = 0; break;}//这种出车顺序不存在
		}
		printf("%s\n",ok?"Yes":"No");
	}
	return 0;
}