#include <cstdio>

#define INF 1000000000

using namespace std;

struct vertex
{
	int first_edge;
	int dis;
}V[100010];

struct edge
{
	int endp, next;
	int w;
}E[1000010];

int ec = 1;
int ivc, iec;

int Q[200000];
int hp = 0, tp = 0;

void enqueue(int x)
{
	Q[tp] = x;
	tp++;
	tp %= 200000;
}

int dequeue()
{
	int ret = Q[hp];
	hp++;
	hp %= 200000;
	return ret;
}

bool empty()
{
	return hp == tp;
}

void add_edge(int u, int v, int w)
{
	E[ec].next = V[u].first_edge;
	V[u].first_edge = ec;
	E[ec].endp = v;
	E[ec].w = w;
	ec++;
}

void initial_single_source(int s)
{
	for (int i = 1; i <= ivc; i++)
	{
		V[i].dis = INF;
	}
	V[s].dis = 0;
}

void SPFA(int s)
{
	initial_single_source(s);
	enqueue(s);
	while (!empty())
	{
		int u = dequeue();
		for (int cur = V[u].first_edge; cur != 0; cur = E[cur].next)
		{
			int newdis = V[u].dis + E[cur].w;
			if (newdis < V[E[cur].endp].dis)
			{
				V[E[cur].endp].dis = newdis;
				enqueue(E[cur].endp);
			}
		}
	}
}

int main()
{
	scanf("%d%d", &ivc, &iec);
	for (int i = 0; i < iec; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		add_edge(u, v, w);
		add_edge(v, u, w);
	}
	SPFA(1);
	printf("%d", V[ivc].dis);
	return 0;
}
