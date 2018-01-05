//尝试先构建树，然后执行遍历得到结果
//推荐 通过前序和中序 直接 构建后序
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<queue>
#include<stack>
using namespace std;

typedef struct TNode
{
	char value;
	struct TNode* left;
	struct TNode* right;
}Node;

Node* newnode(char v)
{
	Node* u = (Node*)malloc(sizeof(Node));
	u->left = NULL;
	u->right = NULL;
	u->value = v;
	return u;
}


//n length 整个树的大小
//s1 前序遍历 根左右
//s2 中序遍历 左根右
//return root
//新增根节点 赋值 然后递归调用给 左右子树赋值
Node* buildtree(int n,char* s1,char* s2)
{
	//这里递归返回
	if(n<=0) return NULL;
	//get root value and build root
	char rootValue = s1[0];
	Node * u = newnode(rootValue);
	//get left son tree size
	int leftTreeSize = strchr(s2,rootValue) - s2;
	//recursive buildtree
	u->left = buildtree(leftTreeSize,s1+1,s2);
	u->right = buildtree(n-leftTreeSize-1,s1+1+leftTreeSize,s2+leftTreeSize+1);
	return u;
}

void removeTree(Node* root)
{
	if(root == NULL) return;
	removeTree(root->left);
	removeTree(root->right);
	free(root);
}

//先序遍历
void root_L_R(const Node* const root,queue<char>& q)
{
	if(root == NULL) return;
	q.push(root->value);
	root_L_R(root->left,q);
	root_L_R(root->right,q);
}

//先序遍历 非递归
//访问T->value后,T入栈,遍历左子树 遍历左子树返回时 栈顶元素应为T 出栈 再先序遍历T的右子树
void root_L_R_2(const Node* const root,queue<char>& q)
{
	stack<const Node*> stack;//后进先出
	const Node* u = root;//u 遍历指针
	while (u || !stack.empty())
	{
		if(u!=NULL)
		{
			q.push(u->value);//访问结点值
			stack.push(u);//入栈
			u = u->left;//往左走
		}
		else
		{
			u = stack.top();
			stack.pop();
			u = u->right;//右
		}
	}
}

//中序遍历
void L_root_R(const Node* const root,queue<char>& q)
{
	if(root == NULL) return;
	L_root_R(root->left,q);
	q.push(root->value);
	L_root_R(root->right,q);
}

//中序遍历 非递归
//T入栈 遍历左子树 遍历左子树返回时栈顶元素为T 出栈 访问T->value 再中序遍历T右子树
void L_root_R_2(const Node* const root,queue<char>& q)
{
	stack<const Node*> stack;
	const Node* u = root;
	while (u || !stack.empty())
	{
		if(u!=NULL)
		{
			stack.push(u);
			u = u->left;//左走
		}
		else//u == NULL and stack is not empty
		{
			u = stack.top();
			stack.pop();
			q.push(u->value);//访问结点值
			u = u->right;//右走
		}
	}

}

//后序遍历
void L_R_root(const Node* const root,queue<char>& q)
{
	if(root == NULL) return;
	L_R_root(root->left,q);
	L_R_root(root->right,q);
	q.push(root->value);
}


//相当于在原先node定义上 又包装了一层
typedef struct TNodePost{
	const Node* biTree;
	char tag;
}NodePost;

//后序遍历 非递归 copy from CSDN
//T 入栈 遍历左子树 遍历左子树返回栈顶元素T 不出栈 遍历右子树 遍历右子树返回栈顶元素T 访问T->value
//需要标记左右子树是否遍历
void L_R_root_2(const Node* const root,queue<char>& q)
{
	stack<NodePost*> stack;//堆栈里面放 包装了tag的结点
	const Node* u = root;//遍历指针
	NodePost* v;//v包装了u
	while (u!=NULL || !stack.empty())
	{
		//遍历左子树
		while(u!=NULL)
		{
			v = (NodePost*)malloc(sizeof(NodePost));
			v->biTree = u;
			v->tag = 'L';//访问了左子树
			stack.push(v);
			u = u->left;
		}
		//左右子树访问完毕后 访问根结点
		while(!stack.empty() && stack.top()->tag == 'R')
		{
			v = stack.top();
			stack.pop();
			q.push(v->biTree->value);
			free(v);//free
		}
		//遍历右子树
		if(!stack.empty()){
			v = stack.top();
			v->tag = 'R';
			u = v->biTree->right;
		}
	}
}

//后序遍历 非递归 自己写
//T 入栈 遍历左子树 遍历左子树返回栈顶元素T 不出栈 遍历右子树 遍历右子树返回栈顶元素T 访问T->value
//需要标记左右子树是否遍历
void L_R_root_3(const Node* const root,queue<char>& q)
{
	stack<NodePost*> stack;
	const Node* u = root;
	NodePost* v;
	while(u!=NULL || !stack.empty())
	{
		//遍历左子树
		if(u!=NULL)
		{
			v = (NodePost*)malloc(sizeof(NodePost));
			v->biTree = u;
			v->tag = 'L';
			stack.push(v);
			u = u->left;
		}
		else if(stack.top()->tag=='L')//u == NULL and stack is not empty 遍历右子树
		{
			v = stack.top();
			v->tag = 'R';
			u = v->biTree->right;
		}
		else//u == NULL and stack is not empty and tag is R 结点信息
		{
			v = stack.top();
			q.push(v->biTree->value);
			stack.pop();
			free(v);
		}
	}


}


//获取树中结点个数
//采取后序遍历
int size = 0;
void getTreeSize(const Node* const root)
{
	if(root == NULL) return;
	getTreeSize(root->left);
	getTreeSize(root->right);
	size++;
}

int getTreeSize2(const Node* const root)
{
	if(root == NULL) return 0;
	int size = 0;
	size += getTreeSize2(root->left);
	size += getTreeSize2(root->right);
	size++;
	return size;
}

//先序遍历获得叶节点
void getLeafNodes(const Node* const root,queue<char>& q)
{
	if(root == NULL) return;
	if(root->left==NULL && root->right==NULL)
	{
		q.push(root->value);//叶结点
	}
	getLeafNodes(root->left,q);
	getLeafNodes(root->right,q);
}

//非递归先序遍历得到叶节点
void getLeafNodes2(const Node* const root,queue<char>& q)
{
	const Node* u = root;
	stack<const Node*> stack;
	while(u!=NULL || !stack.empty())
	{
		if(u!=NULL)
		{
			//访问根
			//是不是叶节点
			if(u->left==NULL&&u->right==NULL)
			{
				q.push(u->value);
			}
			stack.push(u);
			u = u->left;
		}
		else
		{
			u = stack.top();
			stack.pop();
			u = u->right;		
		}
	}
}

//二叉树的高度 后序遍历
int getTreeHeight(const Node* const root)
{
	if(root == NULL) return 0;
	int height = 0, leftHeight = 0, rightHeight = 0;
	leftHeight = getTreeHeight(root->left);
	rightHeight = getTreeHeight(root->right);
	height = (leftHeight>rightHeight)? leftHeight:rightHeight;
	return height+1;
}


void getQueueData(queue<char>& q)
{
	while(!q.empty())
	{
		printf("%c",q.front());
		q.pop();
	}
	printf("\n");
}

void emptyQueue(queue<char>& q)
{
	while(!q.empty())
	{
		q.pop();
	}
}



int main()
{
	char s1[100],s2[100];
	Node* root = NULL;
	queue<char> q1;
	queue<char> q2;
	queue<char> q3;
	queue<char> q4;
	queue<char> q5;

	while(scanf("%s%s",s1,s2) == 2)
	{
		int n = strlen(s1);
		removeTree(root);//deal memory leak
		emptyQueue(q1);
		emptyQueue(q2);
		emptyQueue(q3);
		emptyQueue(q4);
		emptyQueue(q5);
		root = buildtree(n,s1,s2);//1.buildtree

		root_L_R_2(root,q1);
		L_root_R_2(root,q2);
		L_R_root_3(root,q3);

		printf("前序遍历\t");
		getQueueData(q1);
		printf("中序遍历\t");
		getQueueData(q2);
		printf("后序遍历\t");
		getQueueData(q3);
		printf("\n");

		size = 0;
		getTreeSize(root);
		printf("结点总数: %d\n",size);
		printf("结点总数: %d\n",getTreeSize2(root));

		printf("树高度: %d\n",getTreeHeight(root));

		printf("叶节点:\n");
		getLeafNodes(root,q4);
		getLeafNodes2(root,q5);
		getQueueData(q4);
		getQueueData(q5);
		printf("\n");



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