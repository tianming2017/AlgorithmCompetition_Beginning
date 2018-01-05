#include<stdio.h>
#include<math.h>

//有向面积的2倍 逆时针为正
double area2(double x0,double y0, double x1,double y1, double x2,double y2)
{
	return x0*y1+x2*y0+x1*y2-x2*y1-x0*y2-x1*y0;
}

//三角形面积 一定为正
double area(double x0,double y0, double x1,double y1, double x2,double y2)
{
	double area_2 = area2(x0,y0,x1,y1,x2,y2);
	return fabs(area_2/2.0);
}

//点O是否在三角形ABC的内部或边界上
bool IsInTriangle(double ax,double ay,double bx,double by,double cx,double cy,double ox,double oy)
{
	//S(abc) = S(oab) + S(obc) + S(oca)
	double S_abc = area(ax,ay,bx,by,cx,cy);
	double S_oab = area(ox,oy,ax,ay,bx,by);
	double S_obc = area(ox,oy,bx,by,cx,cy);
	double S_oca = area(ox,oy,cx,cy,ax,ay);
	double static eps = 1e-9;
	if(fabs(S_abc-S_oab-S_obc-S_oca)<eps)
	{
		return true;
	}
	return false;
}

int main()
{
	double ax,ay,bx,by,cx,cy;
	int count;
	while(scanf_s("%lf%lf%lf%lf%lf%lf",&ax,&ay,&bx,&by,&cx,&cy) == 6)
	{
		count = 0;
		for(int i=1;i<=99;i++)
		{
			for(int j=1;j<=99;j++)
			{
				if(IsInTriangle(ax,ay,bx,by,cx,cy,i,j))
				{
					count++;
				}
			
			}
		}
		printf("%d\n",count);
	
	}

}