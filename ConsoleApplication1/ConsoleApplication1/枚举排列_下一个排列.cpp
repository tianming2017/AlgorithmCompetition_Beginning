#include<cstdio>
#include<algorithm>
using namespace std;
int main()
{
	int n,p[10];
	scanf_s("%d",&n);
	for(int i=0;i<n;i++)
		scanf_s("%d",&p[i]);
	sort(p,p+n);
	do
	{
		for(int i=0;i<n;i++)
			printf("%d ",p[i]);//�������p
		printf("\n");
	}while(next_permutation(p,p+n));
	getchar();
	getchar();
	return 0;
}