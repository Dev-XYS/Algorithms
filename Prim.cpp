#include <cstdio>
#include <queue>

typedef long long ll;

using namespace std;

struct vertex
{
	int first;
}V[5010];

struct edge
{
	int endp, next, w;
}E[400010];

struct queue_node
{
	int u;
	ll dis;
	queue_node(int _u = 0, ll _dis = 0) : u(_u), dis(_dis) { }
};

int n, m, ec = 2;
bool vis[5010];

inline void add_edge(int u, int v, int w)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	E[ec].w = w;
	ec++;
}

inline bool operator < (const queue_node &x, const queue_node &y)
{
	return x.dis > y.dis;
}

ll prim()
{
	ll res = 0;
	int vc = 0;
	priority_queue<queue_node> Q;
	Q.push(queue_node(1, 0));
	while (vc < n)
	{
		queue_node u = Q.top();
		Q.pop();
		if (vis[u.u] == false)
		{
			res += u.dis;
			vis[u.u] = true;
			vc++;
			for (int cur = V[u.u].first; cur != 0; cur = E[cur].next)
			{
				Q.push(queue_node(E[cur].endp, E[cur].w));
			}
		}
	}
	return res;
}

int main()
{
	scanf("%d%d", &n, &m);
	int u, v, w;
	for (int i = 0; i < m; i++)
	{
		scanf("%d%d%d", &u, &v, &w);
		add_edge(u, v, w);
		add_edge(v, u, w);
	}
	printf("%lld\n", prim());
	return 0;
}
