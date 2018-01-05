//�����ȹ�������Ȼ��ִ�б����õ����
//�Ƽ� ͨ��ǰ������� ֱ�� ��������
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


//n length �������Ĵ�С
//s1 ǰ����� ������
//s2 ������� �����
//return root
//�������ڵ� ��ֵ Ȼ��ݹ���ø� ����������ֵ
Node* buildtree(int n,char* s1,char* s2)
{
	//����ݹ鷵��
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

//�������
void root_L_R(const Node* const root,queue<char>& q)
{
	if(root == NULL) return;
	q.push(root->value);
	root_L_R(root->left,q);
	root_L_R(root->right,q);
}

//������� �ǵݹ�
//����T->value��,T��ջ,���������� ��������������ʱ ջ��Ԫ��ӦΪT ��ջ ���������T��������
void root_L_R_2(const Node* const root,queue<char>& q)
{
	stack<const Node*> stack;//����ȳ�
	const Node* u = root;//u ����ָ��
	while (u || !stack.empty())
	{
		if(u!=NULL)
		{
			q.push(u->value);//���ʽ��ֵ
			stack.push(u);//��ջ
			u = u->left;//������
		}
		else
		{
			u = stack.top();
			stack.pop();
			u = u->right;//��
		}
	}
}

//�������
void L_root_R(const Node* const root,queue<char>& q)
{
	if(root == NULL) return;
	L_root_R(root->left,q);
	q.push(root->value);
	L_root_R(root->right,q);
}

//������� �ǵݹ�
//T��ջ ���������� ��������������ʱջ��Ԫ��ΪT ��ջ ����T->value ���������T������
void L_root_R_2(const Node* const root,queue<char>& q)
{
	stack<const Node*> stack;
	const Node* u = root;
	while (u || !stack.empty())
	{
		if(u!=NULL)
		{
			stack.push(u);
			u = u->left;//����
		}
		else//u == NULL and stack is not empty
		{
			u = stack.top();
			stack.pop();
			q.push(u->value);//���ʽ��ֵ
			u = u->right;//����
		}
	}

}

//�������
void L_R_root(const Node* const root,queue<char>& q)
{
	if(root == NULL) return;
	L_R_root(root->left,q);
	L_R_root(root->right,q);
	q.push(root->value);
}


//�൱����ԭ��node������ �ְ�װ��һ��
typedef struct TNodePost{
	const Node* biTree;
	char tag;
}NodePost;

//������� �ǵݹ� copy from CSDN
//T ��ջ ���������� ��������������ջ��Ԫ��T ����ջ ���������� ��������������ջ��Ԫ��T ����T->value
//��Ҫ������������Ƿ����
void L_R_root_2(const Node* const root,queue<char>& q)
{
	stack<NodePost*> stack;//��ջ����� ��װ��tag�Ľ��
	const Node* u = root;//����ָ��
	NodePost* v;//v��װ��u
	while (u!=NULL || !stack.empty())
	{
		//����������
		while(u!=NULL)
		{
			v = (NodePost*)malloc(sizeof(NodePost));
			v->biTree = u;
			v->tag = 'L';//������������
			stack.push(v);
			u = u->left;
		}
		//��������������Ϻ� ���ʸ����
		while(!stack.empty() && stack.top()->tag == 'R')
		{
			v = stack.top();
			stack.pop();
			q.push(v->biTree->value);
			free(v);//free
		}
		//����������
		if(!stack.empty()){
			v = stack.top();
			v->tag = 'R';
			u = v->biTree->right;
		}
	}
}

//������� �ǵݹ� �Լ�д
//T ��ջ ���������� ��������������ջ��Ԫ��T ����ջ ���������� ��������������ջ��Ԫ��T ����T->value
//��Ҫ������������Ƿ����
void L_R_root_3(const Node* const root,queue<char>& q)
{
	stack<NodePost*> stack;
	const Node* u = root;
	NodePost* v;
	while(u!=NULL || !stack.empty())
	{
		//����������
		if(u!=NULL)
		{
			v = (NodePost*)malloc(sizeof(NodePost));
			v->biTree = u;
			v->tag = 'L';
			stack.push(v);
			u = u->left;
		}
		else if(stack.top()->tag=='L')//u == NULL and stack is not empty ����������
		{
			v = stack.top();
			v->tag = 'R';
			u = v->biTree->right;
		}
		else//u == NULL and stack is not empty and tag is R �����Ϣ
		{
			v = stack.top();
			q.push(v->biTree->value);
			stack.pop();
			free(v);
		}
	}


}


//��ȡ���н�����
//��ȡ�������
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

//����������Ҷ�ڵ�
void getLeafNodes(const Node* const root,queue<char>& q)
{
	if(root == NULL) return;
	if(root->left==NULL && root->right==NULL)
	{
		q.push(root->value);//Ҷ���
	}
	getLeafNodes(root->left,q);
	getLeafNodes(root->right,q);
}

//�ǵݹ���������õ�Ҷ�ڵ�
void getLeafNodes2(const Node* const root,queue<char>& q)
{
	const Node* u = root;
	stack<const Node*> stack;
	while(u!=NULL || !stack.empty())
	{
		if(u!=NULL)
		{
			//���ʸ�
			//�ǲ���Ҷ�ڵ�
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

//�������ĸ߶� �������
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

		printf("ǰ�����\t");
		getQueueData(q1);
		printf("�������\t");
		getQueueData(q2);
		printf("�������\t");
		getQueueData(q3);
		printf("\n");

		size = 0;
		getTreeSize(root);
		printf("�������: %d\n",size);
		printf("�������: %d\n",getTreeSize2(root));

		printf("���߶�: %d\n",getTreeHeight(root));

		printf("Ҷ�ڵ�:\n");
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