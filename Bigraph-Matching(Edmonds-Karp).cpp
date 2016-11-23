#include <cstdio>

#define INF 1000000000

#define VERTEX_COUNT 10000
#define EDGE_COUNT 100000

using namespace std;

struct vertex
{
	int first, prev, pree, maxflow;
	bool inq;
}V[VERTEX_COUNT];

struct edge
{
	int endp, next, flow;
}E[EDGE_COUNT];

int ec = 2, n, m, ans;
int Q[VERTEX_COUNT], hp = 0, tp = 0;

void enqueue(int x)
{
	Q[tp++] = x;
	tp %= VERTEX_COUNT;
}

int dequeue()
{
	hp %= VERTEX_COUNT;
	return Q[hp++];
}

void add_edge(int u, int v)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	E[ec].flow = 1;
	ec++;
	E[ec].next = V[v].first;
	V[v].first = ec;
	E[ec].endp = u;
	E[ec].flow = 0;
	ec++;
}

void Edmonds_Karp(int s, int t)
{
	bool has_ap = false;
	do
	{
		has_ap = false;
		for (int i = 1; i < 10000; i++)
		{
			V[i].inq = false;
		}
		hp = tp = 0;
		enqueue(s);
		V[s].inq = true;
		while (hp != tp)
		{
			int u = dequeue();
			if (u == t)
			{
				int x = u, apflow = INF;
				while (x != s)
				{
					if (E[V[x].pree].flow < apflow)
					{
						apflow = E[V[x].pree].flow;
					}
					x = V[x].prev;
				}
				ans += apflow;
				x = u;
				while (x != s)
				{
					E[V[x].pree].flow -= apflow;
					E[V[x].pree ^ 1].flow += apflow;
					x = V[x].prev;
				}
				has_ap = true;
				break;
			}
			for (int cur = V[u].first; cur != 0; cur = E[cur].next)
			{
				if (V[E[cur].endp].inq == false && E[cur].flow > 0)
				{
					enqueue(E[cur].endp);
					V[E[cur].endp].inq = true;
					V[E[cur].endp].prev = u;
					V[E[cur].endp].pree = cur;
				}
			}
		}
	} while (has_ap == true);
}

int main()
{
	int k, u;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &k);
		for (int j = 0; j < k; j++)
		{
			scanf("%d", &u);
			add_edge(i, u + 1000);
		}
	}
	scanf("%d", &m);
	for (int i = 0; i < m; i++)
	{
		scanf("%d", &u);
		add_edge(u + 1000, 9999);
	}
	for (int i = 1; i <= n; i++)
	{
		add_edge(9998, i);
	}
	Edmonds_Karp(9998, 9999);
	printf("%d", ans);
	return 0;
}
