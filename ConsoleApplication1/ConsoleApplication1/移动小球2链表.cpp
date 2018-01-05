#include<stdio.h>
#include<stdlib.h>

void link(int X, int Y,int* left,int* right)
{
	right[X] = Y;
	left[Y] = X;
}



int main()
{
	int n,m;
	int X,Y;
	char type[10];
	int* left = nullptr;
	int* right = nullptr;
	scanf_s("%d%d",&n,&m);
	left = (int*)malloc(sizeof(int)*(n+2));
	right = (int*)malloc(sizeof(int)*(n+2));
	//1-n的小球 对应 1-n的下标

	for(int i=1;i<=n;i++)
	{
		left[i] = i-1;
		right[i] = i+1;
	}
	//0号球是假想的,n+1球假想
	left[0] = 0;
	right[0] = 1;
	//init end

	//A X Y 把X放到Y左边
	//B X Y 把X放到Y右边

	for(int i=0;i<m;i++)//m 次操作 A X Y  or   B X Y
	{
		scanf("%1s%d%d",type,&X,&Y);
		link(left[X],right[X],left,right);
		if(type[0] == 'A')
		{
			link(left[Y],X,left,right);;
			link(X,Y,left,right);//语句顺序
		}
		else if(type[0] == 'B')
		{
			link(X,right[Y],left,right);
			link(Y,X,left,right);//语句顺序
		}
	}

	int result = right[0];
	while(result!=n+1)
	{
		printf("%d ",result);
		result = right[result];
	}

	system("pause");

	return 0;
}