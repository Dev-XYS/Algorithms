#include <cstdio>
#include <cstring>
#include <queue>

#define INF 2000000000
#define VERTEX_COUNT 100000
#define EDGE_COUNT 100000

using namespace std;

struct vertex
{
	int first, dis;
}V[VERTEX_COUNT];

struct edge
{
	int endp, next, f;
}E[EDGE_COUNT];

int ivc, iec, ec = 2, src, sink;

inline void add_edge(int u, int v, int f)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	E[ec].f = f;
	ec++;
}

bool bfs()
{
	queue<int> Q;
	static bool inq[VERTEX_COUNT];
	memset(inq, false, sizeof(inq));
	Q.push(sink), inq[sink] = true;
	while (!Q.empty())
	{
		int u = Q.front();
		Q.pop();
		for (int cur = V[u].first; cur != 0; cur = E[cur].next)
		{
			if (E[cur ^ 1].f > 0 && inq[E[cur].endp] == false)
			{
				V[E[cur].endp].dis = V[u].dis + 1;
				Q.push(E[cur].endp), inq[E[cur].endp] = true;
			}
		}
	}
	return inq[src] == true;
}

int dfs(int u, int curf)
{
	if (u == sink) return curf;
	int totalf = 0;
	for (int cur = V[u].first; cur != 0 && totalf < curf; cur = E[cur].next)
	{
		if (V[u].dis == V[E[cur].endp].dis + 1 && E[cur].f > 0)
		{
			int f = dfs(E[cur].endp, min(E[cur].f, curf - totalf));
			E[cur].f -= f;
			E[cur ^ 1].f += f;
			totalf += f;
		}
	}
	return totalf;
}

int max_flow()
{
	int res = 0;
	while (bfs() == true)
	{
		int flow;
		do
		{
			flow = dfs(src, INF);
			res += flow;
		} while (flow > 0);
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
	src = 1, sink = ivc;
	printf("%d", max_flow());
	return 0;
}
