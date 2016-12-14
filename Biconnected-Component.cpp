#include <cstdio>

#define VERTEX_COUNT 100000
#define EDGE_COUNT 100000

using namespace std;

struct vertex
{
	int first, dfn, low;
}V[VERTEX_COUNT];

struct edge
{
	int endp, next, col;
}E[EDGE_COUNT];

int ec = 2, ivc, iec, S[VERTEX_COUNT], sp = 0, dfn = 1, col = 1;

inline int min(int x, int y)
{
	return x < y ? x : y;
}

inline void push(int e)
{
	S[sp++] = e;
}

inline int pop()
{
	return S[--sp];
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
			push(cur);
			DFS(E[cur].endp, u);
			V[u].low = min(V[u].low, V[E[cur].endp].low);
			if (V[E[cur].endp].low >= V[u].dfn)
			{
				int e;
				do
				{
					e = pop();
					E[e].col = col;
					E[e ^ 1].col = col;
				} while (e != cur);
				col++;
			}
		}
		else if (E[cur].endp != p)
		{
			push(cur);
			V[u].low = min(V[u].low, V[E[cur].endp].dfn);
		}
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
	DFS(1, 0);
	return 0;
}
