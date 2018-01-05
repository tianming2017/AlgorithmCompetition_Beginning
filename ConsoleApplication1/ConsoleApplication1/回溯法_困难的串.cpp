//如果一个字符串 包含 两个相邻的 重复子串 则称为 容易的串
//否则 为 困难的串
//input n,L
//输出由前L个字符组成 的 第n小的困难的串
//先写 给一个字符串 判断是不是困难的串

#include<cstdio>
#include<memory.h>
const int MAXN = 80+10;
int cnt;//计数
int n,L;
int S[MAXN];//保存结果


//返回0 表示已经得到解 无须继续搜索
int dfs(int cur)
{
	if(cnt++ == n)
	{
		for(int i=0;i<cur;i++)
			printf("%c",'A' + S[i]);//输出方案
		printf("\n");
		return 0;
	}
	for(int i=0;i<L;i++)//所有可能值 
	{
		S[cur] = i;
		int ok = 1;
		for(int j=1;j*2<=cur+1;j++)//尝试长度为j*2的后缀
		{
			int equal = 1;
			for(int k=0;k<j;k++)//检查后一半是否等于前一半
				if(S[cur-k] != S[cur-k-j])
				{
					equal = 0;
					break;
				}
			if(equal)//假如后一半等于前一半 简单的串 方案不合法
			{
				ok = 0;
				break;
			}
		}
		if(ok)//先把可能值放好 判断放在那里行不行 只有通过才会递归 可能值才成立 否则那个位置的值会在下次循环中改变
		{
			if(!dfs(cur+1))//递归搜索 如果已经找到解 则直接退出
				return 0;
		}
	}
	return 1;
}

//默写一遍
int dfs_2(int cur)
{
	if(cnt++ == n)//找到第n个困难的串 输出 递归结束
	{
		for(int i=0;i<cur;i++)
			printf("%c",'A' + S[i]);
		printf("\n");
		return 0;
	}
	else
	{
		for(int i=0;i<L;i++)//可能值0--L
		{
			S[cur] = i;
			int ok=1;
			//验证是否OK 判断是不是困难的串
			for(int j=1;j*2<=cur+1;j++)//j 子串长度 不同长度的子串
			{
				//相邻子串是否相同?
				int equal = 1;
				for(int k=0;k<j;k++)  // ...[cur-j],[cur-j+1],...,[cur]
				{
					if(S[cur-k] != S[cur-j-k])
					{
						equal = 0;
						break;
					}
				}
				if(equal)
				{
					ok = 0;
					break;
				}
			}
			if(ok)
			{
				if(!dfs(cur+1))//递归
					return 0;
			}
		}
		return 1;
	}
}

int main()
{
	while(scanf_s("%d%d",&n,&L) == 2 && n>0 && n<=80 && L>0)
	{
		cnt = 0;
		memset(S,0,sizeof(S));
		dfs_2(0);
	}


}

