#include <cstdio>
#include <cstring>

#define VERTEX_COUNT 1010
#define EDGE_COUNT 250010

using namespace std;

struct vertex
{
	int first, mv;
}V[VERTEX_COUNT];

struct edge
{
	int endp, next;
}E[EDGE_COUNT];

int nl, nr, iec, ec = 2;
bool vis[VERTEX_COUNT];

inline void add_edge(int u, int v)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	ec++;
}

bool dfs(int u)
{
	if (vis[u] == true) return false;
	vis[u] = true;
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		if (V[u].mv != E[cur].endp && (V[E[cur].endp].mv == 0 || dfs(V[E[cur].endp].mv) == true))
		{
			V[u].mv = E[cur].endp;
			V[E[cur].endp].mv = u;
			return true;
		}
	}
	return false;
}

int match()
{
	int res = 0;
	for (int i = 1; i <= nl; i++)
	{
		memset(vis, false, sizeof(vis));
		res += (int)dfs(i);
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
		add_edge(u, v + nl);
	}
	printf("%d\n", match());
	for (int i = 1; i <= nl; i++)
	{
		if (V[i].mv != 0) printf("%d ", V[i].mv - nl);
		else printf("0 ");
	}
	return 0;
}
