//正整数n 至少两个不同进制下(2<=b1,b2<=10)回文 则是双基回文数 
//输入s<10e6 输出比s大的最小双基回文数
#include<stdio.h>

//计算 十进制表示的数在 i进制 下面的表示
//逆序表示的 进制数
void compute(int n,int i,char* s,int* len)
{
	int count = 0;//记录长度
	while (n)
	{
		s[count++] = (n % i) + '0';//数字转字符
		n = n / i;
	}
	*len = count;
}

//计算 十进制表示的数在 i进制 下面的表示
//逆序表示的 进制数
void compute_2(int n,int i,int* s,int* len)
{
	int count = 0;//记录长度
	while (n)
	{
		s[count++] = n % i;
		n = n / i;
	}
	*len = count;
}

//判断回文字符串
//起点i 终点len-1-i
int isPalindrome(char* s,int len)
{
	for(int i=0;i<=len-1;i++)
	{
		if(s[i]!=s[len-1-i]) return 0;
	}
	return 1;
}

//判断回文字符串
//起点i 终点len-1-i
int isPalindrome_2(int* s,int len)
{
	for(int i=0;i<=len-1;i++)
	{
		if(s[i]!=s[len-1-i]) return 0;
	}
	return 1;
}

//1.计算每个数的各种进制表示
//2.看这个进制表示是否回文
int main()
{
	int n;//32bit 
	//char s[32];//保存各种进制下面的数
	int s2[32];//似乎不需要char数组 直接用int存试试
	int len;//记录 进制数字长度
	int count = 0;//成功回文次数

	while(scanf_s("%d",&n) == 1)
	{
		for(int num=n+1;;num++)
		{
			count = 0;//every num, reset count
			for(int i=2;i<=10;i++)
			{
				/*version1: 用了字符数组*/
				//compute(num,i,s,&len);
				////输出一下各种进制下的表示 就看看
				//printf("%d 的 %d进制: ",num,i);
				//for(int j=len-1;j>=0;j--)//逆序输出
				//	printf("%c ",s[j]);
				//printf("\n");

				//if(isPalindrome(s,len)) count++;

				compute_2(num,i,s2,&len);
				/*version2: 用int数组存数字不就完事了?何必跟字符转来转去
				debug的时候可以看下
				//输出一下各种进制下的表示 就看看
				printf("%d 的 %d进制: ",num,i);
				for(int j=len-1;j>=0;j--)//逆序输出
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