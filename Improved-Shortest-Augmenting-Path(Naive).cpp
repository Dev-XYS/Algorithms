#include <cstdio>

#define INF 1000000000
#define VERTEX_COUNT 1000
#define EDGE_COUNT 1000

using namespace std;

struct vertex
{
	int first, dis;
}V[VERTEX_COUNT];

struct edge
{
	int endp, next, flow;
}E[EDGE_COUNT];

int ec = 2, iec, ivc, src, sink;

inline int min(int x, int y)
{
	return x < y ? x : y;
}

void add_edge(int u, int v, int f)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	E[ec].flow = f;
	ec++;
}

int DFS(int u, int curf)
{
	if (u == sink)
	{
		return curf;
	}
	int totalf = 0, mindis = INF;
	for (int cur = V[u].first; cur != 0 && totalf < curf; cur = E[cur].next)
	{
		if (E[cur].flow > 0)
		{
			if (V[u].dis == V[E[cur].endp].dis + 1)
			{
				int t = DFS(E[cur].endp, min(curf - totalf, E[cur].flow));
				E[cur].flow -= t;
				E[cur ^ 1].flow += t;
				totalf += t;
			}
			mindis = min(mindis, V[E[cur].endp].dis);
		}
	}
	if (totalf == 0)
	{
		V[u].dis = mindis + 1;
	}
	return totalf;
}

int max_flow()
{
	int res = 0;
	while (V[src].dis < ivc)
	{
		res += DFS(src, INF);
	}
	return res;
}

int main()
{
	int u, v, f;
	scanf("%d%d", &iec, &ivc);
	for (int i = 0; i < iec; i++)
	{
		scanf("%d%d%d", &u, &v, &f);
		add_edge(u, v, f);
		add_edge(v, u, 0);
	}
	src = 1;
	sink = ivc;
	printf("%d", max_flow());
	return 0;
}
