//给一个数组 要求对其中的数字进行全排列
#include<cstdio>
#include<algorithm>

const int MAXN = 100;
using namespace std;

//对 已排序的数组 中的元素进行全排列
void print_permutation(int n,int* P,int *A,int cur)
{
	if(n == cur)
	{
		for(int i=0;i<n;i++)
			printf("%d ",A[i]);
		printf("\n");
	}
	else
	{
		for(int i=0;i<n;i++)//P[] 的下标  取P[i] 放到A[cur]
		{
			if(!i || P[i] != P[i-1])//不重复
			{
				int c1=0, c2=0;
				for(int j=0;j<cur;j++)//已有次数
					if(A[j] ==P[i])
						c1++;
				for(int k=0;k<n;k++)//P数组中这个值出现的次数
					if(P[k] == P[i])
						c2++;
				if(c1<c2)
				{
					A[cur] = P[i];
					print_permutation(n,P,A,cur+1);
				}
			}
		}
	}
}

int main()
{
	int A[MAXN];
	int P[MAXN];
	int n;
	while(scanf_s("%d",&n) == 1 && n>0)
	{
		for(int i=0;i<n;i++)
		{
			scanf_s("%d",P+i);
		}
		sort(P,P+n);
		print_permutation(n,P,A,0);
	}
	getchar();
	return 0;
}
