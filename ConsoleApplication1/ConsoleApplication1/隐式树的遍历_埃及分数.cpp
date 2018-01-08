//��λ���� ��������ͬ
//give a/b �����ٵıȼ�����ĺ� ������������ͬ ��С�ķ���Խ��Խ��
// 2/3 = 1/2 + 1/6
// 19/45 = 1/3 + 1/12 + 1/180
//		 = 1/3 + 1/15 + 1/45
//		 = 1/3 + 1/18 + 1/30
//		 = 1/4 + 1/6 + 1/180
//		 = 1/5 + 1/6 + 1/18(best)
//		 = 1/4 + 1/7 + 1/35 + 1/1260
//0 < a < b < 1000

#include<cstdio>
#include<memory.h>
#include<algorithm>
using namespace std;
const int MAXN = 100;
int ans[MAXN];//���
int v[MAXN];//��ʱ
int maxd;//ö���������

//a<b 
//�õ�cʹ�� a/b > 1/c ; c����С
int get_first(int a,int b)
{
	return b/a+1;
}

//�������
int gcd(int a,int b)
{
	return b==0 ? a : gcd(b,a%b);
}

//��С�ķ��� Խ��Խ�� (��ĸԽСԽ��)
int better(int d)
{
	for(int i=d;i>=0;i--)
		if(v[i]!=ans[i])
			return (ans[i] == 0 || v[i] < ans[i]);
	return 0;
}

//��ǰ��� ��ĸ��Сֵ ��ʽ��ߵķ�ʽa/b
//ÿ�δ�С��x/y���������Ӵ�С��ʼö�� ��ʽ�ұߵķ�ʽ�� �𽥱�С��
int dfs(int depth,int c,int a,int b)
{
	if(depth == maxd)
	{
		if(b%a)//���Ӳ���1
			return 0;
		v[depth] = b/a;
		if(better(depth))//������С�ķ��� ����
		{
			memcpy(ans,v,sizeof(v));//v copy to ans
		}
		return 1;//���ķ�ʽ ������1
	}
	int ok = 0;//��maxd�������� �ܷ��ҵ�һ����
	c = max(c,get_first(a,b));
	for(int i=c;;i++)//��ĸ��С���,������С С��һ���̶�ʱ �����d��Ȼ����ʹ �ܺ�==a/b  
	{
		if((maxd-depth+1)*b <= a*i)  //(maxd-depth+1)*(1/i) <= a/b ��֦
			break;
		v[depth] = i;//  a/b - 1/i
		int a2 = a*i-b;	//�µķ�������
		int b2 = b*i;
		int g = gcd(a2,b2);//�������
		if(dfs(depth+1,i+1,a2/g,b2/g))
			ok = 1;
	}
	return ok;
}

//-------Ĭд---------
// a/b > 1/c ; c min; 1/c max
int get_first_2(int a,int b)
{
	return b/a+1;
}

int gcd_2(int a,int b)
{
	return b==0 ? a : gcd(b,a%b);
}

//��С�������  ��ĸ С
int better_2(int d)
{
	for(int i = d; d>=0; d--)
		if(v[i]!=ans[i])
			return (ans[i] == 0 || v[d] < ans[d]);
	return 0;
}

//d: depth
//c: 1/c < a/b ; 1/c max ; c min
//a/b  = ? + ? + ..
int dfs_2(int d,int c,int a,int b)
{
	if(d==maxd)
	{
		if(b%a)
			return 0;
		v[d] = b/a;
		if(better_2(d))
		{
			memcpy(ans,v,sizeof(v));
		}
		return 1;//is 1/?
	}
	int ok = 0;
	c = max(c,get_first_2(a,b));//�״ε�������������ȵ� ֮��Ҫȷ�� ��һ����ʽ�ķ�ĸ ���� ǰһ����ʽ�ķ�ĸ ������� 1/��ĸ < a/b
	for(int i=c;;i++)
	{
		//�ü�֦��ʽ break ѭ��
		//(maxd - d + 1) * 1/i <= a/b; break;
		if((maxd-d+1)*b<=a*i)
			break;
		v[d] = i;
		//���� a/b - 1/i = (ai-b)/bi
		int a2 = a*i-b;
		int b2 = b*i;
		int g = gcd_2(a2,b2);
		if(dfs_2(d+1,c+1,a2/g,b2/g))
			ok = 1;//ָ��maxdepth��(��ʽ�ұ� ��������) �����ҵ�һ��ʹ�� �������� 
	}
	return ok;
}











int main()
{
	int a,b,c;
	while (scanf_s("%d%d",&a,&b) == 2 && a>0 && b>a && b<1000)
	{

		//2/3 = 1/2 + 1/6
		//���������Ϊ1/2�������0  1/6�����1
		//�����ȴ�0��ʼ  ������ֱ������1/2�����
		//������һ�ı� ��Ҫ��ͷ��һ��
		for(maxd = 0;;maxd++)
		{
			memset(ans,0,sizeof(ans));
			memset(v,0,sizeof(v));
			c = get_first_2(a,b);
			if(dfs_2(0,c,a,b))//�ҵ� ���� ���ٵ�
				break;
		}
		//output
		printf("%d/%d = ",a,b);
		for(int i=0;i<=maxd;i++)
		{
			if(i)
				printf(" + ");
			printf("1/%d",ans[i]);
		}
		printf("\n");
	}
	getchar();
	return 0;
}