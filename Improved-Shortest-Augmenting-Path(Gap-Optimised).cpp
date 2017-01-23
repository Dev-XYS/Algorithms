#include <cstdio>

#define INF 1000000000
#define VERTEX_COUNT 210
#define EDGE_COUNT 410

using namespace std;

struct vertex
{
	int first, dis;
}V[VERTEX_COUNT];

struct edge
{
	int endp, next, lower, upper, flow;
}E[EDGE_COUNT];

int ivc, iec, ec = 2, gap[VERTEX_COUNT], src, sink;

inline int min(int x, int y)
{
	return x < y ? x : y;
}

void init()
{
	src = 1;
	sink = ivc;
	gap[0] = ivc;
}

void add_edge(int u, int v, int lower, int upper, int flow)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	E[ec].lower = lower;
	E[ec].upper = upper;
	E[ec].flow = flow;
	ec++;
}

int isap(int u, int curf)
{
	if (u == sink)
	{
		return curf;
	}
	int totalf = 0, mindis = ivc;
	for (int cur = V[u].first; cur != 0 && totalf < curf; cur = E[cur].next)
	{
		if (E[cur].flow > 0)
		{
			if (V[u].dis == V[E[cur].endp].dis + 1)
			{
				int f = isap(E[cur].endp, min(E[cur].flow, curf - totalf));
				totalf += f;
				E[cur].flow -= f;
				E[cur ^ 1].flow += f;
			}
			mindis = min(mindis, V[E[cur].endp].dis);
		}
	}
	if (totalf == 0)
	{
		gap[V[u].dis]--;
		if (gap[V[u].dis] == 0) V[src].dis = ivc;
		V[u].dis = mindis + 1;
		gap[V[u].dis]++;
	}
	return totalf;
}

int max_flow()
{
	int res = 0;
	while (V[src].dis < ivc)
	{
		res += isap(src, INF);
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
		add_edge(u, v, 0, 0, f);
		add_edge(v, u, 0, 0, 0);
	}
	init();
	printf("%d", max_flow());
	return 0;
}
