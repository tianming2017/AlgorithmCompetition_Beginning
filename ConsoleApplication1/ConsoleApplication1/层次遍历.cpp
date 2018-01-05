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
char s[MAXN + 10];//���������(1)
int failed = 0;//addnode
int n = 0,ans[MAXN];//������� ������� bfs

Node* newnode()
{
	Node* u = (Node*)malloc(sizeof(Node));
	if(u!=NULL)
	{
		u->have_value = 0;//��ʾ��ʼ��Ϊ0 ��Ϊmalloc�����ڴ�ʱ��������
		u->left = u->right = NULL;
	}
	return u;
}

//s like LL)
//ÿ�δӸ��ڵ��ߵ���Ӧλ�� ��ֵ
//�ߵ�·�� ����û�н�� �򴴽�
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
		}//�������������������Ǹ������������
	}
	if(u->have_value)//�Ѿ���ֵ����������
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
		if(scanf("%s",s)!=1)//scanf�����ո��ͣ���� ��scanf_s �ͱ���?
		{
			return 0;//end of file,����������֮ǰ�ļ�����
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
	Node* q[MAXN];//����
	q[0] = root;
	while(front<rear)
	{
		Node* u = q[front++];
		if(!u->have_value)
		{
			return 0;//�н��û�и�ֵ��������������
		}
		ans[n++] = u->v;//���ӵ��������β��
		if(u->left != NULL)
		{
			q[rear++] = u->left;//enqueue
		}
		if(u->right != NULL)
		{
			q[rear++] = u->right;//enqueue
		}
	}
	return 1;//������ȷ
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