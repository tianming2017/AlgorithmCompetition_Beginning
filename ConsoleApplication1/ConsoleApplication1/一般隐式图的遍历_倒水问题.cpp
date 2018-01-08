//ĳһʱ�̴���v0 �б���v1 С����v2
//��������a(init full) �б�����b(init empty) С������c(init empty) ���ٶ��ٲ��� ĳһ����������x 
//0 < c < b < a < 1000
//��ˮ ��һ����ˮ�ı���1 ���� һ��û�����ı���2;Ҫô����1���� Ҫô����2����
#include<cstdio>
#include<memory.h>
#include<queue>
#include<stack>
using namespace std;
const int MAXN = 1000;
int a,b,c,x;
int vis[MAXN][MAXN];//�����±�ֱ��� �б� �� С����ˮ��,�����жϴ�״̬�Ƿ��Ѿ�������

class state
{
public:
	int v0;//L
	int v1;//M
	int v2;//S
	state* L_to_M;
	state* L_to_S;
	state* M_to_L;
	state* M_to_S;
	state* S_to_L;
	state* S_to_M;
	state* parent;

	state()
	{
		v0 = 0;
		v1 = 0;
		v2 = 0;
		L_to_M = NULL;
		L_to_S = NULL;
		M_to_L = NULL;
		M_to_S = NULL;
		S_to_L = NULL;
		S_to_M = NULL;
		parent = NULL;
	}

	state* LargeToMediem(state* const s)
	{
		if(s->v0>0 && s->v1<b)//����ˮ �б�û��
		{
			state* u = new state();
			if(s->v1 + s->v0 >= b)//�б�����
			{
				u->v0 = s->v0 - (b - s->v1);
				u->v1 = b;
				u->v2 = s->v2;
			}
			else//�󱭵���ˮû��
			{
				u->v0 = 0;
				u->v1 = s->v1 + s->v0;
				u->v2 = s->v2;
			}
			u->parent = s;
			return u;
		}
		return NULL;
	}

	state* LargeToSmall(state* const s)
	{
		if(s->v0>0 && s->v2<c)//L has water, S not full
		{
			state* u = new state();
			if(s->v0 + s->v2 >= c)//S full
			{
				u->v0 = s->v0 - (c - s->v2);
				u->v1 = s->v1;
				u->v2 = c;
			}
			else//L empty
			{
				u->v0 = 0;
				u->v1 = s->v1;
				u->v2 = s->v2 + s->v0;
			}
			u->parent = s;
			return u;	
		}
		return NULL;
	}

	state* MediemToLarge(state* const s)
	{
		if(s->v1 > 0 && s->v0 < a)
		{
			state* u = new state();
			if(s->v0 + s->v1 >= a)//L full
			{
				u->v0 = a;
				u->v1 = s->v1 - (a-s->v0);
				u->v2 = s->v2;
			}
			else//M empty
			{
				u->v0 = s->v0 + s->v1;
				u->v1 = 0;
				u->v2 = s->v2;
			}
			u->parent = s;
			return u;
		}
		return NULL;
	}

	state* MediemToSmall(state* const s)
	{
		if(s->v1>0 && s->v2 < c)
		{
			state* u = new state();
			if(s->v1 + s->v2 >= c)//S full
			{
				u->v0 = s->v0;
				u->v1 = s->v1 - (c - s->v2);
				u->v2 = c;
			}
			else//M empty
			{
				u->v0 = s->v0;
				u->v1 = 0;
				u->v2 = s->v2 + s->v1;
			}
			u->parent = s;
			return u;
		}
		return NULL;
	}

	state* SmallToLarge(state* const s)
	{
		if(s->v2 > 0 && s->v0 < a)
		{
			state* u = new state();
			if(s->v0 + s->v2 >= a)//L full
			{
				u->v0 = a;
				u->v1 = s->v1;
				u->v2 = s->v2 - (a-s->v0);
			}
			else//S empty
			{
				u->v0 = s->v0 + s->v2;
				u->v1 = s->v1;
				u->v2 = 0;
			}
			u->parent = s;
			return u;
		}
		return NULL;
	}

	state* SmallToMediem(state* const s)
	{
		if(s->v2 > 0 && s->v1 <b)
		{
			state* u = new state();
			if(s->v1 + s->v2 >= b)//M full
			{
				u->v0 = s->v0;
				u->v1 = b;
				u->v2 = s->v2 - (b - s->v1);
			}
			else//S empty
			{
				u->v0 = s->v0;
				u->v1 = s->v1 + s->v2;
				u->v2 = 0;
			}
			u->parent = s;
			return u;
		}
		return NULL;
	}

};

//stack over flow 2333
//void freeGraph(state* & root)
//{
//	if(root == NULL)
//		return;
//	if(root)
//	{
//		freeGraph(root->L_to_M);
//		freeGraph(root->L_to_S);
//		freeGraph(root->M_to_L);
//		freeGraph(root->M_to_S);
//		freeGraph(root->S_to_L);
//		freeGraph(root->S_to_M);
//		freeGraph(root->parent);
//		delete root;
//		root = NULL;
//	}
//}

queue<state*> q;//����BFS
stack<state*> stk;//��ÿ��״̬

int bfs(state* s0)
{
	q.push(s0);
	vis[s0->v1][s0->v2] = 1;//���һ��״̬�Ƿ��Ѿ����ǹ�

	int ok = 0;
	state* u = NULL;

	while(!q.empty())
	{
		state* s = q.front();
		q.pop();
		if(s->v0 == x || s->v1 == x || s->v2 == x)
		{
			ok = 1;
			u = s;
			break;	
		}

		s->L_to_M = s->LargeToMediem(s);
		if(s->L_to_M)
			if(!vis[s->L_to_M->v1][s->L_to_M->v2])
			{
				q.push(s->L_to_M);
				vis[s->L_to_M->v1][s->L_to_M->v2] = 1;
			}

		s->L_to_S = s->LargeToSmall(s);
		if(s->L_to_S)
			if(!vis[s->L_to_S->v1][s->L_to_S->v2])
			{
				q.push(s->L_to_S);
				vis[s->L_to_S->v1][s->L_to_S->v2] = 1;
			}
				

		s->M_to_L = s->MediemToLarge(s);
		if(s->M_to_L)
			if(!vis[s->M_to_L->v1][s->M_to_L->v2])
			{
				q.push(s->M_to_L);
				vis[s->M_to_L->v1][s->M_to_L->v2] = 1;
			}
				

		s->M_to_S = s->MediemToSmall(s);
		if(s->M_to_S)
			if(!vis[s->M_to_S->v1][s->M_to_S->v2])
			{
				q.push(s->M_to_S);
				vis[s->M_to_S->v1][s->M_to_S->v2] = 1;
			}
			

		s->S_to_L = s->SmallToLarge(s);
		if(s->S_to_L)
			if(!vis[s->S_to_L->v1][s->S_to_L->v2])
			{
				q.push(s->S_to_L);
				vis[s->S_to_L->v1][s->S_to_L->v2] = 1;
			}

		s->S_to_M = s->SmallToMediem(s);
		if(s->S_to_M)
			if(!vis[s->S_to_M->v1][s->S_to_M->v2])
			{
				q.push(s->S_to_M);
				vis[s->S_to_M->v1][s->S_to_M->v2] = 1;
			}
			

	}
	while(u != NULL)
	{
		stk.push(u);
		u = u->parent;
	}
	return ok;
}

void emptyStack(stack<state*>& s)
{
	while(!s.empty())
		s.pop();
}

void emptyQueue(queue<state*>& q)
{
	while(!q.empty())
		q.pop();
}

int main()
{
	while(scanf_s("%d%d%d%d",&a,&b,&c,&x) == 4 && c>0 && b>c && a>b && a<MAXN && x>0 && x<a)
	{
		emptyStack(stk);
		emptyQueue(q);
		memset(vis,0,sizeof(vis));

		state* root = new state();
		root->v0 = a;
		root->v1 = 0;
		root->v2 = 0;
		if(bfs(root))
		{
			//output
			while(!stk.empty())
			{
				state* tmp = stk.top();
				printf("(%d,%d,%d) ",tmp->v0,tmp->v1,tmp->v2);
				stk.pop();
			}
			printf("\n");
		}
		else
		{
			printf("Can not find path!\n");
		}
		/*freeGraph(root);*/
	}
	getchar();
	getchar();
	return 0;
}
