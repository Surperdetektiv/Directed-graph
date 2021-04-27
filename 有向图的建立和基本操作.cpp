#include<stdio.h>
#include<stdlib.h>
#include<iostream>

using namespace std;
#define MAX 20
int n[100];
int m[100];
typedef struct QNode
{
	int data;
	struct QNode *next;
}QNode, *QueuePtr;



typedef struct
{
	QueuePtr rear;
	QueuePtr front;
}LinkQueue;


void InitQueue(LinkQueue &q)
{
	q.front=q.rear = (QueuePtr)malloc(sizeof(QNode));
	if (!q.front)exit(-2);
	q.front->next = NULL;
}

void Enqueue(LinkQueue &q, int e)
{
	QNode *p;
	p = (QueuePtr)malloc(sizeof(QNode));
	p->data = e;
	p->next = NULL;
	q.rear->next = p;
	q.rear = p;
}

void  Dequeue(LinkQueue &q, int &u)
{
	QNode *p;
	if (q.front == q.rear)
		return;
	p = q.front->next;
	u = p->data;
	q.front->next= p->next;
	if (q.rear == p)q.rear = q.front;
	free(p);
}


bool empty(LinkQueue &q)
{
	if (q.front == q.rear)
		return true;
	else
		return false;
}


typedef struct ArcNode
{
	int adjvex;
	struct ArcNode *nextarc;
	//int cost;
}ArcNode;

typedef struct VNode
{
	char data;
	ArcNode *firstarc;

}VNode, AdjList[MAX];


typedef struct
{
	AdjList vertices;
	int vexnum, arcnum;
}ALGraph;


typedef struct ArcInfo
{
	char tailname;
	char headname;
	//int cost;
}ArcInfo;


int GetVertexPos(ALGraph &G, const char &vertex)
{
	for (int i = 0; i < G.vexnum; i++)
	{
		if (G.vertices[i].data == vertex)
			return i;
	}
	return -1;


}


void InsertEdge(ALGraph &G, int tail, int head)//, int cost)
{
	ArcNode *p = new ArcNode();
	p->adjvex = head;
	//p->cost = cost;
	p->nextarc = NULL;
	ArcNode *q = G.vertices[tail].firstarc;
	G.vertices[tail].firstarc = p;
	p->nextarc = q;
}


void CreateDN(ALGraph &G, int vexnum, int arcnum, char name[], ArcInfo Info[])
{

	int i, tail, head;
	//int cost;
	G.vexnum = vexnum;
	G.arcnum = arcnum;
	for (i = 0; i < G.vexnum; i++)
	{
		G.vertices[i].data = name[i];
		G.vertices[i].firstarc = NULL;
	}
	for (i = 0; i < G.arcnum; i++)
	{
		//cost = Info[i].cost;
		tail = GetVertexPos(G, Info[i].tailname);
		head = GetVertexPos(G, Info[i].headname);
		InsertEdge(G, tail, head);//, Info[i].cost);
	}
}


int  FirstAdjVex(ALGraph G, int &v)
{
	//if (v<0 || v>MAX)
		//return -1;
	ArcNode*p = G.vertices[v].firstarc;
	if (p!=NULL)
		return p->adjvex;
	else
		return -1;
}


int NextAdjVex(ALGraph G, int &v, int &w)
{
	//if (v<0 || v>MAX)return -1;
	//if (w < 0 || w>MAX)return -1;
	ArcNode *p = G.vertices[v].firstarc;
	while (p&&p->adjvex != w)
	{
		p = p->nextarc;
	}
	if (p->nextarc != NULL)
		return p->nextarc->adjvex;
	else
		return -1;
}

bool visit[MAX];
void DFS(ALGraph G, int &v)
{
	visit[v] = true;
	cout << G.vertices[v].data << "  ";
	for (int w = FirstAdjVex(G, v); w != -1; w = NextAdjVex(G, v, w))
	{
		if (!visit[w])DFS(G, w);
	}
}

void DFSTraverse(ALGraph &G)
{
	for (int v = 0; v < G.vexnum; v++)
	{
		visit[v] = false;
	}
	for (int v = 0; v < G.vexnum; v++)
	{
		if (!visit[v])DFS(G,v);
	}
}

bool visited[MAX];
void BFSTraverse(ALGraph G)
{
	int v, u, w;
	for (v = 0; v < G.vexnum; v++)
	{
		visited[v] = false;
	}
	LinkQueue Q;
	InitQueue (Q);
	for (v = 0; v < G.vexnum; v++)
	{
		if (visited[v] == false)
		{
			visited[v] = true;
			cout << G.vertices[v].data << "  ";
			Enqueue(Q, v);
			while (!empty(Q))
			{
				Dequeue(Q, u);
				for (w = FirstAdjVex(G, u); w != -1; w = NextAdjVex(G, u, w))
				{
					if (!visited[w])
					{
						visited[w] = true;
						cout << G.vertices[w].data << "  ";
						Enqueue(Q, w);
					}
				}
			}
		}
	}
}
int main()
{
	ALGraph Graph1;
	int vexnum, arcnum;
	cin >> vexnum;
	char name[100];
	for (int i = 0; i < vexnum; i++)
	{
		cin >> name[i];
	}
	cin >> arcnum;
	ArcInfo Info[100];
	for (int i = 0; i < arcnum; i++)
	{
		cin >> Info[i].tailname >> Info[i].headname;//scanf("%c %c ", &Info[i].tailname, &Info[i].headname);
	}
	CreateDN(Graph1, vexnum, arcnum, name, Info);
	
	DFSTraverse(Graph1);
	cout << endl;
	BFSTraverse(Graph1);
	cout << endl;
	return 0;
}