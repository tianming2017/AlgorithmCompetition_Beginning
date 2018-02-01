//贷款
//一次向银行借a元钱 分b月还清 如果需要每月还c元 则月利率x是多少(复利) x<=100%
//a=2000 b=4 c=510 x=0.797% 
//f(x) = (((2000(1+x)-c)(1+x)-c)(1+x)-c)(1+x)-c=0
#include<cstdio>
int main()
{
	double a,c,x=0,y=100;
	int b;
	scanf_s("%lf%d%lf",&a,&b,&c);
	while(y-x > 1e-5)
	{
		double m = x + (y-x)/2;//猜的利率 二分方法
		double f = a;
		for (int i = 0; i < b; i++)
		{
			f = f*(1+m/100.0) - c;
		}
		if(f < 0)
		{
			x = m;
		}
		else
		{
			y = m;
		}
	}
	printf("%.3lf%%\n",x);
	getchar();
	getchar();
	return 0;
}