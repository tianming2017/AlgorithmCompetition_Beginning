#include<cstdio>
#include<queue>
using namespace std;

queue<int> q;
int main()
{
	int n;
	scanf_s("%d",&n);
	for(int i=0;i<n;i++)
	{
		q.push(i+1);//init
	}

	while(q.size()>=2)
	{
		printf("%d ",q.front());
		q.pop();
		q.push(q.front());
		q.pop();
	}
	
	printf("%d ",q.front());
	system("pause");
	return 0;
}