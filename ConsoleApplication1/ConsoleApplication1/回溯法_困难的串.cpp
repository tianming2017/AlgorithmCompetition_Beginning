//���һ���ַ��� ���� �������ڵ� �ظ��Ӵ� ���Ϊ ���׵Ĵ�
//���� Ϊ ���ѵĴ�
//input n,L
//�����ǰL���ַ���� �� ��nС�����ѵĴ�
//��д ��һ���ַ��� �ж��ǲ������ѵĴ�

#include<cstdio>
#include<memory.h>
const int MAXN = 80+10;
int cnt;//����
int n,L;
int S[MAXN];//������


//����0 ��ʾ�Ѿ��õ��� �����������
int dfs(int cur)
{
	if(cnt++ == n)
	{
		for(int i=0;i<cur;i++)
			printf("%c",'A' + S[i]);//�������
		printf("\n");
		return 0;
	}
	for(int i=0;i<L;i++)//���п���ֵ 
	{
		S[cur] = i;
		int ok = 1;
		for(int j=1;j*2<=cur+1;j++)//���Գ���Ϊj*2�ĺ�׺
		{
			int equal = 1;
			for(int k=0;k<j;k++)//����һ���Ƿ����ǰһ��
				if(S[cur-k] != S[cur-k-j])
				{
					equal = 0;
					break;
				}
			if(equal)//�����һ�����ǰһ�� �򵥵Ĵ� �������Ϸ�
			{
				ok = 0;
				break;
			}
		}
		if(ok)//�Ȱѿ���ֵ�ź� �жϷ��������в��� ֻ��ͨ���Ż�ݹ� ����ֵ�ų��� �����Ǹ�λ�õ�ֵ�����´�ѭ���иı�
		{
			if(!dfs(cur+1))//�ݹ����� ����Ѿ��ҵ��� ��ֱ���˳�
				return 0;
		}
	}
	return 1;
}

//Ĭдһ��
int dfs_2(int cur)
{
	if(cnt++ == n)//�ҵ���n�����ѵĴ� ��� �ݹ����
	{
		for(int i=0;i<cur;i++)
			printf("%c",'A' + S[i]);
		printf("\n");
		return 0;
	}
	else
	{
		for(int i=0;i<L;i++)//����ֵ0--L
		{
			S[cur] = i;
			int ok=1;
			//��֤�Ƿ�OK �ж��ǲ������ѵĴ�
			for(int j=1;j*2<=cur+1;j++)//j �Ӵ����� ��ͬ���ȵ��Ӵ�
			{
				//�����Ӵ��Ƿ���ͬ?
				int equal = 1;
				for(int k=0;k<j;k++)  // ...[cur-j],[cur-j+1],...,[cur]
				{
					if(S[cur-k] != S[cur-j-k])
					{
						equal = 0;
						break;
					}
				}
				if(equal)
				{
					ok = 0;
					break;
				}
			}
			if(ok)
			{
				if(!dfs(cur+1))//�ݹ�
					return 0;
			}
		}
		return 1;
	}
}

int main()
{
	while(scanf_s("%d%d",&n,&L) == 2 && n>0 && n<=80 && L>0)
	{
		cnt = 0;
		memset(S,0,sizeof(S));
		dfs_2(0);
	}


}

