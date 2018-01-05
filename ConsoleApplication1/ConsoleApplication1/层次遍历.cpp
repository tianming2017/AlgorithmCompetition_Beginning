#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXN 256
typedef struct TNode
{
	int have_value;
	int v;
	struct TNode *left, *right;
}Node;

//glbal variables
Node* root;
char s[MAXN + 10];//保存读入结点(1)
int failed = 0;//addnode
int n = 0,ans[MAXN];//结点总数 输出序列 bfs

Node* newnode()
{
	Node* u = (Node*)malloc(sizeof(Node));
	if(u!=NULL)
	{
		u->have_value = 0;//显示初始化为0 因为malloc申请内存时并不清零
		u->left = u->right = NULL;
	}
	return u;
}

//s like LL)
//每次从根节点走到对应位置 赋值
//走的路上 假如没有结点 则创建
void addnode(int v,char* s)
{
	int n = strlen(s);
	Node* u = root;
	for(int i=0;i<n;i++)
	{
		if(s[i]=='L')
		{
			if(u->left == NULL)
			{
				u->left = newnode();
			}
			u = u->left;
		}
		else if(s[i]=='R')
		{
			if(u->right == NULL)
			{
				u->right = newnode();
			}
			u = u->right;
		}//忽略其他情况，即最后那个多余的右括号
	}
	if(u->have_value)//已经赋值，输入有误
	{
		failed++;//break or not? choose one
	}
	u->v = v;
	u->have_value = 1;//marker
}

void remove_tree(Node* u)
{
	if(u==NULL) return;
	remove_tree(u->left);
	remove_tree(u->right);
	free(u);
}

int read_input()
{
	failed = 0;
	remove_tree(root);
	root = newnode();
	while(true)
	{
		if(scanf("%s",s)!=1)//scanf遇到空格会停下来 用scanf_s 就报错?
		{
			return 0;//end of file,读到空括号之前文件结束
		}
		if(!strcmp(s,"()"))
		{
			break;//s == "()"
		}
		int v;
		sscanf_s(&s[1],"%d",&v);//node value
		addnode(v,strchr(s,',')+1);//11,LL)
	}
	return 1;
}

int bfs()
{
	int front = 0, rear = 1;
	Node* q[MAXN];//队列
	q[0] = root;
	while(front<rear)
	{
		Node* u = q[front++];
		if(!u->have_value)
		{
			return 0;//有结点没有赋值，表面输入有误
		}
		ans[n++] = u->v;//增加到输出序列尾部
		if(u->left != NULL)
		{
			q[rear++] = u->left;//enqueue
		}
		if(u->right != NULL)
		{
			q[rear++] = u->right;//enqueue
		}
	}
	return 1;//输入正确
}



int main()
{
	read_input();
	int flag = bfs();
	if(failed>0 || flag==0)
	{
		printf("%d",-1);//error
	}
	else
	{
		for(int i=0;i<n;i++)
		{
			printf("%d ",ans[i]);
		}
	}
	getchar();
	getchar();
	return 0;
}
//input 
//(11,LL) (7,LLL) (8,R) (5,) (4,L) (13,RL) (2,LLR) (1,RRR) (4,RR) ()
//ouput
//5 4 8 11 13 4 7 2 1