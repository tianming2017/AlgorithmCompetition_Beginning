//��������������������
//����������
//�ݹ�ʵ�� ��������
#include<stdio.h>
#include<string.h>

//n ����
//s1 ������� ������
//s2 ������� �����
//s ����ĺ������ ���Ҹ�
//��������������Ǹ��ڵ�����������Ҳ����������������� ���ֱ����������ͨ���ݹ鶨���
void build(int n,char* s1,char* s2,char* s)
{
	if(n<=0) return;
	int p = strchr(s2,s1[0]) - s2;//�ҵ����ڵ�����������е�λ��,ͬʱҲ�����������ַ�������
	build(p,s1+1,s2,s);//�ݹ� ������ �ĺ������
	build(n-p-1,s1+p+1,s2+p+1,s+p);//�ݹ� ������ �ĺ������
	s[n-1] = s1[0];//�Ѹ��ڵ���ӵ����
}

int main()
{
	char s1[100];
	char s2[100];
	char ans[100];
	while (scanf("%s%s",s1,s2) == 2)
	{
		int n = strlen(s1);
		build(n,s1,s2,ans);
		ans[n] = '\0';
		printf("%s\n",ans);
	}
	getchar();
	return 0;
}
//input 
//DBACEGF ABCDEFG
//output
//ACBFGED

//input
//BCAD CBAD
//output
//CDAB