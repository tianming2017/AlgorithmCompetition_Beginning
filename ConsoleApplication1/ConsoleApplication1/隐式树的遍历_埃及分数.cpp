//单位分数 不允许相同
//give a/b 加数少的比加数多的好 若加数个数相同 最小的分数越大越好
// 2/3 = 1/2 + 1/6
// 19/45 = 1/3 + 1/12 + 1/180
//		 = 1/3 + 1/15 + 1/45
//		 = 1/3 + 1/18 + 1/30
//		 = 1/4 + 1/6 + 1/180
//		 = 1/5 + 1/6 + 1/18(best)
//		 = 1/4 + 1/7 + 1/35 + 1/1260
//0 < a < b < 1000

#include<cstdio>
#include<memory.h>
#include<algorithm>
using namespace std;
const int MAXN = 100;
int ans[MAXN];//结果
int v[MAXN];//临时
int maxd;//枚举深度上限

//a<b 
//得到c使得 a/b > 1/c ; c尽量小
int get_first(int a,int b)
{
	return b/a+1;
}

//最大公因数
int gcd(int a,int b)
{
	return b==0 ? a : gcd(b,a%b);
}

//最小的分数 越大越好 (分母越小越好)
int better(int d)
{
	for(int i=d;i>=0;i--)
		if(v[i]!=ans[i])
			return (ans[i] == 0 || v[i] < ans[i]);
	return 0;
}

//当前深度 分母最小值 等式左边的分式a/b
//每次从小于x/y的最大分数从大到小开始枚举 等式右边的分式是 逐渐变小的
int dfs(int depth,int c,int a,int b)
{
	if(depth == maxd)
	{
		if(b%a)//分子不是1
			return 0;
		v[depth] = b/a;
		if(better(depth))//假如最小的分数 更大
		{
			memcpy(ans,v,sizeof(v));//v copy to ans
		}
		return 1;//最后的分式 分子是1
	}
	int ok = 0;//在maxd最大深度下 能否找到一个解
	c = max(c,get_first(a,b));
	for(int i=c;;i++)//分母从小变大,分数变小 小到一定程度时 到深度d仍然不能使 总和==a/b  
	{
		if((maxd-depth+1)*b <= a*i)  //(maxd-depth+1)*(1/i) <= a/b 剪枝
			break;
		v[depth] = i;//  a/b - 1/i
		int a2 = a*i-b;	//新的分数分子
		int b2 = b*i;
		int g = gcd(a2,b2);//最大公因数
		if(dfs(depth+1,i+1,a2/g,b2/g))
			ok = 1;
	}
	return ok;
}

//-------默写---------
// a/b > 1/c ; c min; 1/c max
int get_first_2(int a,int b)
{
	return b/a+1;
}

int gcd_2(int a,int b)
{
	return b==0 ? a : gcd(b,a%b);
}

//最小分数最大  分母 小
int better_2(int d)
{
	for(int i = d; d>=0; d--)
		if(v[i]!=ans[i])
			return (ans[i] == 0 || v[d] < ans[d]);
	return 0;
}

//d: depth
//c: 1/c < a/b ; 1/c max ; c min
//a/b  = ? + ? + ..
int dfs_2(int d,int c,int a,int b)
{
	if(d==maxd)
	{
		if(b%a)
			return 0;
		v[d] = b/a;
		if(better_2(d))
		{
			memcpy(ans,v,sizeof(v));
		}
		return 1;//is 1/?
	}
	int ok = 0;
	c = max(c,get_first_2(a,b));//首次调用这两个是相等的 之后要确保 后一个分式的分母 大于 前一个分式的分母 而且这个 1/分母 < a/b
	for(int i=c;;i++)
	{
		//用剪枝方式 break 循环
		//(maxd - d + 1) * 1/i <= a/b; break;
		if((maxd-d+1)*b<=a*i)
			break;
		v[d] = i;
		//计算 a/b - 1/i = (ai-b)/bi
		int a2 = a*i-b;
		int b2 = b*i;
		int g = gcd_2(a2,b2);
		if(dfs_2(d+1,c+1,a2/g,b2/g))
			ok = 1;//指定maxdepth下(等式右边 分数个数) 可以找到一组使得 与左边相等 
	}
	return ok;
}











int main()
{
	int a,b,c;
	while (scanf_s("%d%d",&a,&b) == 2 && a>0 && b>a && b<1000)
	{

		//2/3 = 1/2 + 1/6
		//这里代码认为1/2的深度是0  1/6深度是1
		//最大深度从0开始  包含了直接输入1/2的情况
		//最大深度一改变 就要从头跑一遍
		for(maxd = 0;;maxd++)
		{
			memset(ans,0,sizeof(ans));
			memset(v,0,sizeof(v));
			c = get_first_2(a,b);
			if(dfs_2(0,c,a,b))//找到 加数 最少的
				break;
		}
		//output
		printf("%d/%d = ",a,b);
		for(int i=0;i<=maxd;i++)
		{
			if(i)
				printf(" + ");
			printf("1/%d",ans[i]);
		}
		printf("\n");
	}
	getchar();
	return 0;
}