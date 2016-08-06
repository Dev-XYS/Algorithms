#include <cstdio>

#define VERTEX_COUNT 100000
#define EDGE_COUNT 100000

using namespace std;

struct vertex
{
	int first_edge;
	int ftime;
}V[VERTEX_COUNT];

int latest = 1;

struct edge
{
	int endp, next;
}E[EDGE_COUNT];

int ec = 1;

void add_edge(int u, int v)
{
	E[ec].next = V[u].first_edge;
	V[u].first_edge = ec;
	E[ec].endp = v;
	ec++;
}

void DFS(int u)
{
	if (V[u].ftime == 0)
	{
		for (int cur = V[u].first_edge; cur != 0; cur = E[cur].next)
		{
			DFS(E[cur].endp);
		}
		
		V[u].ftime = latest++;
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
	
	DFS(1);
	
	for (int i = 1; i <= ivc; i++)
	{
		printf("%d\n", V[i].ftime);
	}
	
	return 0;
}
