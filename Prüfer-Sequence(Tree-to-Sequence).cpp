#include <cstdio>
#include <queue>

#define VERTEX_COUNT 100010
#define EDGE_COUNT 200010

using namespace std;

struct vertex
{
	int first, subcnt, fa;
	bool vis;
}V[VERTEX_COUNT];

struct edge
{
	int endp, next;
}E[EDGE_COUNT];

int ivc, ec = 2, prufer[VERTEX_COUNT], pc;
priority_queue< int, vector<int>, greater<int> > Q;

inline void add_edge(int u, int v)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	ec++;
}

void dfs(int u, int fa)
{
	V[u].vis = true;
	V[u].fa = fa;
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		if (V[E[cur].endp].vis == false) dfs(E[cur].endp, u), V[u].subcnt++;
	}
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
	dfs(1, 0);
	for (int i = 1; i <= ivc; i++)
	{
		if (E[V[i].first].next == 0) Q.push(i);
	}
	for (int i = 3; i <= ivc; i++)
	{
		int u = Q.top();printf("pop : %d, fa = %d\n", u, V[u].fa);
		Q.pop();
		if (V[u].fa == 0)
		{
			for (int cur = V[u].first; cur != 0; cur = E[cur].next)
			{
				if (V[E[cur].endp].fa != 0)
				{
					prufer[pc++] = E[cur].endp;
					V[E[cur].endp].fa = 0;
					if (V[E[cur].endp].subcnt == 1) Q.push(E[cur].endp);
					break;
				}
			}
		}
		else
		{
			prufer[pc++] = V[u].fa;
			V[V[u].fa].subcnt--;
			if (V[V[u].fa].subcnt == 0) Q.push(V[u].fa);
			else if (V[V[u].fa].subcnt == 1 && V[V[u].fa].fa == 0) Q.push(V[u].fa);
		}
	}
	for (int i = 0; i < pc; i++)
	{
		printf("%d ", prufer[i]);
	}
	return 0;
}
