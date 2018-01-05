//������n ����������ͬ������(2<=b1,b2<=10)���� ����˫�������� 
//����s<10e6 �����s�����С˫��������
#include<stdio.h>

//���� ʮ���Ʊ�ʾ������ i���� ����ı�ʾ
//�����ʾ�� ������
void compute(int n,int i,char* s,int* len)
{
	int count = 0;//��¼����
	while (n)
	{
		s[count++] = (n % i) + '0';//����ת�ַ�
		n = n / i;
	}
	*len = count;
}

//���� ʮ���Ʊ�ʾ������ i���� ����ı�ʾ
//�����ʾ�� ������
void compute_2(int n,int i,int* s,int* len)
{
	int count = 0;//��¼����
	while (n)
	{
		s[count++] = n % i;
		n = n / i;
	}
	*len = count;
}

//�жϻ����ַ���
//���i �յ�len-1-i
int isPalindrome(char* s,int len)
{
	for(int i=0;i<=len-1;i++)
	{
		if(s[i]!=s[len-1-i]) return 0;
	}
	return 1;
}

//�жϻ����ַ���
//���i �յ�len-1-i
int isPalindrome_2(int* s,int len)
{
	for(int i=0;i<=len-1;i++)
	{
		if(s[i]!=s[len-1-i]) return 0;
	}
	return 1;
}

//1.����ÿ�����ĸ��ֽ��Ʊ�ʾ
//2.��������Ʊ�ʾ�Ƿ����
int main()
{
	int n;//32bit 
	//char s[32];//������ֽ����������
	int s2[32];//�ƺ�����Ҫchar���� ֱ����int������
	int len;//��¼ �������ֳ���
	int count = 0;//�ɹ����Ĵ���

	while(scanf_s("%d",&n) == 1)
	{
		for(int num=n+1;;num++)
		{
			count = 0;//every num, reset count
			for(int i=2;i<=10;i++)
			{
				/*version1: �����ַ�����*/
				//compute(num,i,s,&len);
				////���һ�¸��ֽ����µı�ʾ �Ϳ���
				//printf("%d �� %d����: ",num,i);
				//for(int j=len-1;j>=0;j--)//�������
				//	printf("%c ",s[j]);
				//printf("\n");

				//if(isPalindrome(s,len)) count++;

				compute_2(num,i,s2,&len);
				/*version2: ��int��������ֲ���������?�αظ��ַ�ת��תȥ
				debug��ʱ����Կ���
				//���һ�¸��ֽ����µı�ʾ �Ϳ���
				printf("%d �� %d����: ",num,i);
				for(int j=len-1;j>=0;j--)//�������
					printf("%d ",s2[j]);
				printf("\n");
				*/
				if(isPalindrome_2(s2,len)) count++;


				if(count>=2) break;
			}
			if(count>=2)//find num,print,break
			{
				printf("%d\n",num);
				break;
			}
		}
	}
	getchar();
	return 0;
}