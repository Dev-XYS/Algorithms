#include <cstdio>
#include <cstring>
#include <algorithm>

#define NIL 0

using namespace std;

struct node
{
	node *next[26];
	int cnt;
	node() : cnt(0) { memset(next, 0, sizeof(next)); }
};

struct vertex
{
	int first, depth;
	node *root;
}V[100010];

struct edge
{
	int endp, next;
}E[200010];

int n, ec = 2, q, fa[100010][18], k;
char str[100010][12];

inline void add_edge(int u, int v)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	ec++;
}

void insert(node *&u, node *old, char *s, int len, int p)
{
	u = new node;
	if (old != NIL) *u = *old;
	u->cnt++;
	if (p == len) return;
	int x = s[p] - 'a';
	u->next[x] = NIL;
	insert(u->next[x], old == NIL ? NIL : old->next[x], s, len, p + 1);
}

int query(node *u, char *s, int len, int p)
{
	if (u == NIL) return 0;
	if (p == len) return u->cnt;
	int x = s[p] - 'a';
	return query(u->next[x], s, len, p + 1);
}

int query(int u, char *s)
{
	return query(V[u].root, s, strlen(s), 0);
}

void dfs(int u, int fa, int depth)
{
	::fa[u][0] = fa;
	V[u].depth = depth;
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		if (E[cur].endp != fa)
		{
			insert(V[E[cur].endp].root, V[u].root, str[cur >> 1], strlen(str[cur >> 1]), 0);
			dfs(E[cur].endp, u, depth + 1);
		}
	}
}

void init()
{
	V[1].root = new node;
	dfs(1, 0, 0);
	for (k = 1; (1 << k) <= n; k++)
	{
		for (int i = 1; i <= n; i++)
		{
			fa[i][k] = fa[fa[i][k - 1]][k - 1];
		}
	}
	k--;
}

int lca(int x, int y)
{
	if (V[x].depth < V[y].depth)
	{
		swap(x, y);
	}
	for (int i = k; i >= 0; i--)
	{
		if (V[x].depth - (1 << i) >= V[y].depth)
		{
			x = fa[x][i];
		}
	}
	if (x == y)
	{
		return x;
	}
	for (int i = k; i >= 0; i--)
	{
		if (fa[x][i] != fa[y][i])
		{
			x = fa[x][i];
			y = fa[y][i];
		}
	}
	return fa[x][0];
}

int main()
{
	scanf("%d", &n);
	int u, v;
	for (int i = 1; i < n; i++)
	{
		scanf("%d%d%s", &u, &v, str[i]);
		add_edge(u, v);
		add_edge(v, u);
	}
	init();
	scanf("%d", &q);
	char s[12];
	while (q--)
	{
		scanf("%d%d%s", &u, &v, s);
		printf("%d\n", query(u, s) + query(v, s) - query(lca(u, v), s) * 2);
	}
	return 0;
}
