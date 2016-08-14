#include <cstdio>
#include <cmath>

#define VERTEX_COUNT 10000
#define EDGE_COUNT 10000

#define INFINITE 1000000000

struct vertex
{
	int first_edge;

	int x, y;

	double shortest;
}V[VERTEX_COUNT];

int vc = 1;

struct edge
{
	int endp;
	int next;

	double w;
}E[EDGE_COUNT];

int ec = 1;

int ivc, iec;

int s, t;

void AddVertex(int x, int y)
{
	V[vc].x = x;
	V[vc].y = y;

	vc++;
}

void AddEdge(int u, int v)
{
	E[ec].next = V[u].first_edge;
	V[u].first_edge = ec;
	E[ec].endp = v;
	E[ec].w = sqrt((V[u].x - V[v].x) * (V[u].x - V[v].x) + (V[u].y - V[v].y) * (V[u].y - V[v].y));

	ec++;
}

// We assume that s is the source and t is the destination.
void InitialSingleSource()
{
	V[s].shortest = 0;

	for (int i = 1; i <= ivc; i++)
	{
		if (i != s)
		{
			V[i].shortest = INFINITE;
		}
	}
}

// The edge (u, v) must exist.
void Relax(int u, int v, double w)
{
	if (w + V[u].shortest < V[v].shortest)
	{
		V[v].shortest = w + V[u].shortest;
	}
}

// The main procedure of "Bellman-Ford" algorithm.
void Bellman_Ford()
{
	InitialSingleSource();

	for (int i = 0; i < ivc - 1; i++)
	{
		for (int curp = 1; curp <= ivc; curp++)
		{
			for (int cure = V[curp].first_edge; cure != 0; cure = E[cure].next)
			{
				Relax(curp, E[cure].endp, E[cure].w);
			}
		}
	}
}

int main()
{
	scanf("%d", &ivc);

	for (int i = 0; i < ivc; i++)
	{
		int x, y;

		scanf("%d%d", &x, &y);

		AddVertex(x, y);
	}

	scanf("%d", &iec);

	for (int i = 0; i < iec; i++)
	{
		int u, v;

		scanf("%d%d", &u, &v);

		AddEdge(u, v);
		AddEdge(v, u);
	}

	scanf("%d%d", &s, &t);

	Bellman_Ford();

	printf("%.2lf", V[t].shortest);

	return 0;
}
