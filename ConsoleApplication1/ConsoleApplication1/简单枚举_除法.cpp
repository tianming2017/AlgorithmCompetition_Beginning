//����������n;abcde/fghij = n; a---j 0---9����; 2<=n<=79
#include<stdio.h>
#include<memory.h>
#include<algorithm>

using namespace std;

int check(int i,int j)
{
	int a[10];
	a[0] = i%10;
	a[1] = i/10%10;
	a[2] = i/100%10;
	a[3] = i/1000%10;
	a[4] = i/10000%10;
	a[5] = j%10;
	a[6] = j/10%10;
	a[7] = j/100%10;
	a[8] = j/1000%10;
	a[9] = j/10000%10;
	sort(a,a+10);
	for(int i=0;i<10;i++)
	{
		if(i!=a[i])		return 0;
	}
	return 1;
}

int check_2(int i,int j)
{
	int a[10];
	a[0] = i%10;
	a[1] = i/10%10;
	a[2] = i/100%10;
	a[3] = i/1000%10;
	a[4] = i/10000%10;
	a[5] = j%10;
	a[6] = j/10%10;
	a[7] = j/100%10;
	a[8] = j/1000%10;
	a[9] = j/10000%10;

	for(int u=0;u<10;u++)
		for(int v=u+1;v<10;v++)
		{
			if(a[u]==a[v])
				return 0;
		}

	return 1;
}



//������ĸ�����п���ȡֵ �õ����ӵ�ֵ
//���ж� ���� ��ĸ
//��� һ�����ĸ���λ����ֵ���������ĽǶ�  ��������...
int main()
{
	int n;
	int i,j;

	while(scanf_s("%d",&n)==1)
	{
		if(n<2 || n>79)
		{
			printf("Invalid input! Retry......\n");
			continue;
		}
		for(j=1234;j<=98765;j++)//��ĸ����ȡֵ
		{
			i = j*n;
			if(i>=10234&&i<=98765)//���Ʒ��ӷ�Χ
			{
				int success = check_2(i,j);
				if(success)
				{
					if(j<10234)
					{
						printf("%d / 0%d = %d\n",i,j,n);
					}
					else
					{
						printf("%d / %d = %d\n",i,j,n);
					}
				}
			}
		}
	}
	getchar();

	return 0;
}