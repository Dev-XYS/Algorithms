#include <cstdio>

using namespace std;

struct vertex
{
	int first, depth;
}V[100010];

struct edge
{
	int endp, next;
}E[200010];

int ec = 1, ivc;
int fa[100010][25];

void add_edge(int u, int v)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	ec++;
}

void DFS(int u, int prev, int depth)
{
	if (fa[u][0] == 0)
	{
		fa[u][0] = prev;
		V[u].depth = depth;
		for (int cur = V[u].first; cur != 0; cur = E[cur].next)
		{
			DFS(E[cur].endp, u, depth + 1);
		}
	}
}

void init()
{
	DFS(1, -1, 1);
	for (int i = 1; i <= 20; i++)
	{
		for (int j = 1; j <= ivc; j++)
		{
			fa[j][i] = fa[fa[j][i - 1]][i - 1];
		}
	}
}

int lca(int a, int b)
{
	if (V[b].depth > V[a].depth)
	{
		int temp = a;
		a = b;
		b = temp;
	}
	int delta = V[a].depth - V[b].depth, k = 0;
	while (delta > 0)
	{
		if ((delta & 1) == 1)
		{
			a = fa[a][k];
		}
		k++;
		delta >>= 1;
	}
	if (a == b)
	{
		return a;
	}
	for (int i = 20; i >= 0; i--)
	{
		if (fa[a][i] != fa[b][i])
		{
			a = fa[a][i];
			b = fa[b][i];
		}
	}
	return fa[a][0];
}

int main()
{
	int u, v;
	scanf("%d", &ivc);
	for (int i = 1; i < ivc; i++)
	{
		scanf("%d%d", &u, &v);
		add_edge(u, v);
		add_edge(v, u);
	}
	init();
	while (true)
	{
		scanf("%d%d", &u, &v);
		printf("%d\n", lca(u, v));
	}
	return 0;
}
