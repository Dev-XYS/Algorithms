#include <cstdio>

#define VERTEX_COUNT 100000
#define EDGE_COUNT 100000

using namespace std;

struct vertex
{
	int first_edge;
	bool vis;
}V[VERTEX_COUNT];

struct edge
{
	int endp, next;
}E[EDGE_COUNT];

int ec = 1;

int Q[VERTEX_COUNT];
int hp = 0, tp = 0;

void enqueue(int x)
{
	Q[tp++] = x;
}

int dequeue()
{
	return Q[hp++];
}

bool queue_empty()
{
	return hp == tp;
}

void add_edge(int u, int v)
{
	E[ec].next = V[u].first_edge;
	V[u].first_edge = ec;
	E[ec].endp = v;
	ec++;
}

void BFS()
{
	while (!queue_empty())
	{
		int u = dequeue();
		
		for (int cur = V[u].first_edge; cur != 0; cur = E[cur].next)
		{
			if (V[E[cur].endp].vis == false)
			{
				V[E[cur].endp].vis = true;
				enqueue(E[cur].endp);
			}
		}
	}
}

int main()
{
	int ivc, iec;
	scanf("%d%d", &ivc, &iec);
	
	for (int i = 0; i < iec; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		
		add_edge(u, v);
	}
	
	enqueue(1);
	
	BFS();
	
	return 0;
}
