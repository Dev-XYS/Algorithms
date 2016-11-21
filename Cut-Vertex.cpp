#include <cstdio>

#define VERTEX_COUNT 100000
#define EDGE_COUNT 100000

using namespace std;

struct vertex
{
	int first, dfn, low;
	bool iscv;
}V[VERTEX_COUNT];

struct edge
{
	int endp, next;
}E[EDGE_COUNT];

int ec = 1, ivc, iec, dfn = 1;

inline int min(int x, int y)
{
	return x < y ? x : y;
}

void add_edge(int u, int v)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	ec++;
}

void DFS(int u, int p)
{
	V[u].dfn = V[u].low = dfn++;
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		if (V[E[cur].endp].dfn == 0)
		{
			DFS(E[cur].endp, u);
			V[u].low = min(V[u].low, V[E[cur].endp].low);
			if (V[E[cur].endp].low >= V[u].dfn)
			{
				V[u].iscv = true;
			}
		}
		else if (E[cur].endp != p)
		{
			V[u].low = min(V[u].low, V[E[cur].endp].dfn);
		}
	}
}

void get(int rt)
{
	int ctc = 0;
	V[rt].dfn = V[rt].low = dfn++;
	for (int cur = V[rt].first; cur != 0; cur = E[cur].next)
	{
		if (V[E[cur].endp].dfn == 0)
		{
			ctc++;
			DFS(E[cur].endp, rt);
		}
	}
	if (ctc > 1)
	{
		V[rt].iscv = true;
	}
}

int main()
{
	int u, v;
	scanf("%d%d", &ivc, &iec);
	for (int i = 0; i < iec; i++)
	{
		scanf("%d%d", &u, &v);
		add_edge(u, v);
		add_edge(v, u);
	}
	for (int i = 1; i <= ivc; i++)
	{
		if (V[i].dfn == 0)
		{
			get(i);
		}
	}
	int cnt = 0;
	for (int i = 1; i <= ivc; i++)
	{
		if (V[i].iscv == true)
		{
			cnt++;
		}
	}
	printf("%d", cnt);
}
