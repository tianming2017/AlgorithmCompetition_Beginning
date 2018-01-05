//输入先序遍历和中序遍历
//输出后序遍历
//递归实现 不构建树
#include<stdio.h>
#include<string.h>

//n 长度
//s1 先序遍历 根左右
//s2 中序遍历 左根右
//s 结果的后序遍历 左右根
//先序遍历不仅仅是根节点的先序遍历，也是其子树的先序遍历 三种遍历本身就是通过递归定义的
void build(int n,char* s1,char* s2,char* s)
{
	if(n<=0) return;
	int p = strchr(s2,s1[0]) - s2;//找到根节点在中序遍历中的位置,同时也是左子树的字符串长度
	build(p,s1+1,s2,s);//递归 左子树 的后序遍历
	build(n-p-1,s1+p+1,s2+p+1,s+p);//递归 右子树 的后序遍历
	s[n-1] = s1[0];//把根节点添加到最后
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