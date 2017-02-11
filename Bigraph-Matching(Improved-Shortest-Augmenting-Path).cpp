#include <cstdio>

#define INF 1000000000

using namespace std;

struct vertex
{
	int first, dis;
}V[1010];

struct edge
{
	int endp, next, flow;
}E[502010];

int nl, nr, iec, ec = 2, src = 1005, sink = 1006, gap[1010];

inline int min(int x, int y)
{
	return x < y ? x : y;
}

void init()
{
	gap[0] = nl + nr + 2;
}

void add_edge(int u, int v, int f)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	E[ec].flow = f;
	ec++;
}

int isap(int u, int curf)
{
	if (u == sink)
	{
		return curf;
	}
	int totalf = 0, mindis = nl + nr + 2;
	for (int cur = V[u].first; cur != 0 && totalf < curf; cur = E[cur].next)
	{
		if (E[cur].flow > 0)
		{
			if (V[u].dis == V[E[cur].endp].dis + 1)
			{
				int f = isap(E[cur].endp, min(curf - totalf, E[cur].flow));
				E[cur].flow -= f;
				E[cur ^ 1].flow += f;
				totalf += f;
			}
			if (V[E[cur].endp].dis < mindis)
			{
				mindis = V[E[cur].endp].dis;
			}
		}
	}
	if (totalf == 0)
	{
		if (--gap[V[u].dis] == 0) V[src].dis = nl + nr + 2;
		V[u].dis = mindis + 1;
		gap[V[u].dis]++;
	}
	return totalf;
}

int max_flow()
{
	int res = 0;
	while (V[src].dis < nl + nr + 2)
	{
		res += isap(src, INF);
	}
	return res;
}

int main()
{
	int u, v;
	scanf("%d%d%d", &nl, &nr, &iec);
	for (int i = 0; i < iec; i++)
	{
		scanf("%d%d", &u, &v);
		add_edge(u, v + nl, 1);
		add_edge(v + nl, u, 0);
	}
	for (int i = 1; i <= nl; i++)
	{
		add_edge(src, i, 1);
		add_edge(i, src, 0);
	}
	for (int i = 1; i <= nr; i++)
	{
		add_edge(i + nl, sink, 1);
		add_edge(sink, i + nl, 0);
	}
	init();
	printf("%d\n", max_flow());
	for (int i = 1; i <= nl; i++)
	{
		bool has = false;
		for (int cur = V[i].first; cur != 0; cur = E[cur].next)
		{
			if (E[cur].endp != src && E[cur].flow == 0)
			{
				printf("%d ", E[cur].endp - nl);
				has = true;
				break;
			}
		}
		if (has == false)
		{
			printf("0 ");
		}
	}
	return 0;
}
