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
	//1-n��С�� ��Ӧ 1-n���±�

	for(int i=1;i<=n;i++)
	{
		left[i] = i-1;
		right[i] = i+1;
	}
	//0�����Ǽ����,n+1�����
	left[0] = 0;
	right[0] = 1;
	//init end

	//A X Y ��X�ŵ�Y���
	//B X Y ��X�ŵ�Y�ұ�

	for(int i=0;i<m;i++)//m �β��� A X Y  or   B X Y
	{
		scanf("%1s%d%d",type,&X,&Y);
		link(left[X],right[X],left,right);
		if(type[0] == 'A')
		{
			link(left[Y],X,left,right);;
			link(X,Y,left,right);//���˳��
		}
		else if(type[0] == 'B')
		{
			link(X,right[Y],left,right);
			link(Y,X,left,right);//���˳��
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