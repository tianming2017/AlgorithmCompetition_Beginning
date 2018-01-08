;//ջ��a,b,c 
//ADD a,b pop; push a+b
//SUB a,b pop; push b-a
//MUL a,b pop; push a*b
//DIV a,b pop; push int(b/a)
//DUP a pop; push a a
//����Ϊ0, ����������, ����������ֵ����30000 ����
//����a,b ����ִ��ǰ ջ��ֻ��a ִ�к�ջ����b ���� ������

//ԭ�Ȱ�Nodeд��struct ������滹����stack stack�ĳ�ʼ���е�����..
//C++ ��classǰ�� ����дpublic
#include<cstdio>
#include<stack>
#include<queue>
#include<assert.h>
using namespace std;

//�������
//op[0] is char[] is "ADD"
char op[5][4] = {"ADD","SUB","MUL","DIV","DUP"};
const int MAXVALUE = 30000;
class Node
{
public:
	int value;//������ֵ
	int operation;//����� ���
	Node* add;
	Node* sub;
	Node* mul;
	Node* div;
	Node* dup;
	Node* parent;
	stack<int> valueStack;//ÿ������һ����ջ 

	Node()
	{
		value = 0;
		operation = 0;
		add = NULL;
		sub = NULL;
		mul = NULL;
		div = NULL;
		dup = NULL;
		parent = NULL;
	}

	Node * createAddNode(Node* const u)
	{
		assert(u!=NULL);
		int a,b,v;
		stack<int> tmpstack = u->valueStack;
		if(tmpstack.size()<2)
			return NULL;
		a = tmpstack.top();
		tmpstack.pop();
		b = tmpstack.top();
		tmpstack.pop();
		v = a+b;
		if(abs(v)>MAXVALUE)
			return NULL;

		Node* p = new Node();
		p->value = v;
		p->parent = u;
		p->operation = 0;
		p->valueStack = tmpstack;
		p->valueStack.push(v);

		return p;
	}

	Node * createSubNode(Node* const u)
	{
		assert(u!=NULL);
		int a,b,v;
		stack<int> tmpstack = u->valueStack;
		if(tmpstack.size()<2)
			return NULL;
		a = tmpstack.top();
		tmpstack.pop();
		b = tmpstack.top();
		tmpstack.pop();
		v = b-a;
		if(abs(v)>MAXVALUE)
			return NULL;

		Node* p = new Node();
		p->value = v;
		p->parent = u;
		p->operation = 1;
		p->valueStack = tmpstack;
		p->valueStack.push(v);
		return p;
	}

	Node * createMulNode(Node* const u)
	{
		assert(u!=NULL);
		int a,b,v;
		stack<int> tmpstack = u->valueStack;
		if(tmpstack.size()<2)
			return NULL;
		a = tmpstack.top();
		tmpstack.pop();
		b = tmpstack.top();
		tmpstack.pop();
		v = a*b;
		if(abs(v)>MAXVALUE)
			return NULL;

		Node* p = new Node();
		p->value = v;
		p->parent = u;
		p->operation = 2;
		p->valueStack = tmpstack;
		p->valueStack.push(v);
		return p;
	}

	Node * createDivNode(Node* const u)
	{
		assert(u!=NULL);
		int a,b,v;
		stack<int> tmpstack = u->valueStack;
		if(tmpstack.size()<2)
			return NULL;
		a = tmpstack.top();
		if(a==0)
			return NULL;
		tmpstack.pop();
		b = tmpstack.top();
		tmpstack.pop();
		v = b/a;
		if(abs(v)>MAXVALUE)
			return NULL;

		Node* p = new Node();
		p->value = v;
		p->parent = u;
		p->operation = 3;
		p->valueStack = tmpstack;
		p->valueStack.push(v);
		return p;
	}

	Node * createDupNode(Node* const u)
	{
		assert(u!=NULL);
		int a,v;
		stack<int> tmpstack = u->valueStack;
		if(tmpstack.size()<1)
			return NULL;
		a = tmpstack.top();
		v = a;
		if(abs(v)>MAXVALUE)
			return NULL;
		tmpstack.pop();

		Node* p = new Node();
		p->value = v;
		p->parent = u;
		p->operation = 4;
		p->valueStack = tmpstack;
		p->valueStack.push(v);
		p->valueStack.push(v);
		return p;
	}
};

//stack<int> valueStack;//��ȫ�ֵĶ�ջ���񲻶�

stack<int> res;//�������������
queue<Node*> q;//���� ����BFS��

//Node* newNode()
//{
//	Node* u = (Node*)malloc(sizeof(Node));
//	assert(u!=NULL);
//	u->value = 0;
//	u->operation = 0;
//	u->add = NULL;
//	u->sub = NULL;
//	u->mul = NULL;
//	u->div = NULL;
//	u->dup = NULL;
//	u->parent = NULL;
//	stack<int> stacknow;
//	u->valueStack=stacknow;
//	return u;
//}
//
//Node* createAddNode(Node* const u)
//{
//	assert(u!=NULL);
//	int a,b,v;
//	stack<int> tmpstack = u->valueStack;
//	if(tmpstack.size()<2)
//		return NULL;
//	a = tmpstack.top();
//	tmpstack.pop();
//	b = tmpstack.top();
//	tmpstack.pop();
//	v = a+b;
//	if(abs(v)>MAXVALUE)
//		return NULL;
//
//	Node* p = newNode();
//	p->value = v;
//	p->parent = u;
//	p->operation = 0;
//	p->valueStack = tmpstack;
//	p->valueStack.push(v);
//
//	return p;
//}
//
//Node* createSubNode(Node* const u)
//{
//	assert(u!=NULL);
//	int a,b,v;
//	stack<int> tmpstack = u->valueStack;
//	if(tmpstack.size()<2)
//		return NULL;
//	a = tmpstack.top();
//	tmpstack.pop();
//	b = tmpstack.top();
//	tmpstack.pop();
//	v = b-a;
//	if(abs(v)>MAXVALUE)
//		return NULL;
//
//	Node* p = newNode();
//	p->value = v;
//	p->parent = u;
//	p->operation = 1;
//	p->valueStack = tmpstack;
//	p->valueStack.push(v);
//	return p;
//}
//
//Node* createMulNode(Node* const u)
//{
//	assert(u!=NULL);
//	int a,b,v;
//	stack<int> tmpstack = u->valueStack;
//	if(tmpstack.size()<2)
//		return NULL;
//	a = tmpstack.top();
//	tmpstack.pop();
//	b = tmpstack.top();
//	tmpstack.pop();
//	v = a*b;
//	if(abs(v)>MAXVALUE)
//		return NULL;
//
//	Node* p = newNode();
//	p->value = v;
//	p->parent = u;
//	p->operation = 2;
//	p->valueStack = tmpstack;
//	p->valueStack.push(v);
//	return p;
//}
//
//Node* createDivNode(Node* const u)
//{
//	assert(u!=NULL);
//	int a,b,v;
//	stack<int> tmpstack = u->valueStack;
//	if(tmpstack.size()<2)
//		return NULL;
//	a = tmpstack.top();
//	if(a==0)
//		return NULL;
//	tmpstack.pop();
//	b = tmpstack.top();
//	tmpstack.pop();
//	v = b/a;
//	if(abs(v)>MAXVALUE)
//		return NULL;
//
//	Node* p = newNode();
//	p->value = v;
//	p->parent = u;
//	p->operation = 3;
//	p->valueStack = tmpstack;
//	p->valueStack.push(v);
//	return p;
//}
//
//Node* createDupNode(Node* const u)
//{
//	assert(u!=NULL);
//	int a,v;
//	stack<int> tmpstack = u->valueStack;
//	if(tmpstack.size()<1)
//		return NULL;
//	a = tmpstack.top();
//	v = a;
//	if(abs(v)>MAXVALUE)
//		return NULL;
//	tmpstack.pop();
//
//	Node* p = newNode();
//	p->value = v;
//	p->parent = u;
//	p->operation = 4;
//	p->valueStack = tmpstack;
//	p->valueStack.push(v);
//	p->valueStack.push(v);
//	return p;
//}

void freeTree(Node* u)
{
	if(u==NULL)
		return;
	free(u->add);
	free(u->sub);
	free(u->mul);
	free(u->div);
	free(u->dup);
	free(u);
}

void emptyStack(stack<int>& s)
{
	while(!s.empty())
		s.pop();
}

void emptyQueue(queue<Node*>& q)
{
	while(!q.empty())
		q.pop();
}

//�ڹ�������ͬʱ����BFS
int buildTree_bfs(Node * root, const int target)
{
	assert(root!=NULL);
	q.push(root);
	
	Node* v = NULL;//�����쵽�����OK��
	int ok = 0;
	while(!q.empty())
	{
		Node* u = q.front();
		q.pop();

		u->add = u->createAddNode(u);
		if(u->add)
		{
			if(u->add->value == target)
			{
				v = u->add;
				ok = 1;
				break;
			}
			q.push(u->add);
		}

		u->sub = u->createSubNode(u);
		if(u->sub)
		{
			if(u->sub->value == target)
			{
				v = u->sub;
				ok = 1;
				break;
			}
			q.push(u->sub);
		}

		u->mul = u->createMulNode(u);
		if(u->mul)
		{
			if(u->mul->value == target)
			{
				v = u->mul;
				ok = 1;
				break;
			}
			q.push(u->mul);
		}

		u->div = u->createDivNode(u);
		if(u->div)
		{
			if(u->div->value == target)
			{
				v = u->div;
				ok = 1;
				break;
			}
			q.push(u->div);
		}

		u->dup = u->createDupNode(u);
		if(u->dup)
		{
			if(u->dup->value == target)
			{
				v = u->dup;
				ok = 1;
				break;
			}
			q.push(u->dup);
		}
	}
	while(v)
	{
		if(v->operation >= 0)//���ڵ��operation����Ϊ-1  �������pop��һ��
			res.push(v->operation);
		v = v->parent;
	}
	return ok;
}


int main()
{
	int a,b;
	while(scanf_s("%d%d",&a,&b) == 2 && abs(a)<=MAXVALUE && abs(b)<=MAXVALUE)
	{
		//emptyStack(valueStack);
		emptyStack(res);
		emptyQueue(q);

		Node* root = new Node();
		root->value = a;
		root->operation = -1;//
		
		root->valueStack.push(a);//��ջһ��ʼ��һ��a
		buildTree_bfs(root,b);
		//print path
		while(!res.empty())
		{
			//printf("%d ",res.top());
			printf("%s ",op[res.top()]);
			res.pop();
		}
		printf("\n");
		freeTree(root);
		
	}
	getchar();
	return 0;
}