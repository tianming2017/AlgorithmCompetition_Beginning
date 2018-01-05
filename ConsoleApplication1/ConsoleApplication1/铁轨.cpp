#include<cstdio>
#include<stack>
using namespace std;
const int MAXN = 1000 + 10;

int n, target[MAXN];

int main()
{
	while(scanf_s("%d",&n) == 1)//������ ��
	{
		stack<int> s;
		int A=1,B=1;//A����ĳ� Ĭ��Ϊ 1~n//ĳ������ڼ�����
		for(int i=1;i<=n;i++)
		{
			scanf_s("%d",&target[i]);//B���� �뿪�ĳ��ı��
		}
		int ok = 1;
		while(B<=n)
		{
			if(A==target[B]){A++; B++;}//����Ҫ��ջ
			else if(!s.empty() && s.top() == target[B])//������ջ���ǲ�����Ҫ��
			{
				s.pop();
				B++;
			}
			else if(A<=n){s.push(A++);}//��ջ
			else {ok = 0; break;}//���ֳ���˳�򲻴���
		}
		printf("%s\n",ok?"Yes":"No");
	}
	return 0;
}