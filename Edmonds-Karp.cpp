#include <cstdio>
#include <cstring>

#define VERTEX_COUNT 210
#define EDGE_COUNT 20000

using namespace std;

struct vertex
{
	int first_edge;
	int pree, prev;
}V[VERTEX_COUNT];

bool vis[VERTEX_COUNT];

struct edge
{
	int endp, next;
	int flow;
}E[EDGE_COUNT];

int ec = 2;
int ivc, iec;

int maxflow = 0;

int Q[VERTEX_COUNT];
int hp = 0, tp = 0;

inline int min(int x, int y)
{
	return x < y ? x : y;
}

void add_edge(int u, int v, int f)
{
	E[ec].next = V[u].first_edge;
	V[u].first_edge = ec;
	E[ec].endp = v;
	E[ec].flow = f;
	ec++;
}

inline void enqueue(int x)
{
	Q[tp++] = x;
}

inline int dequeue()
{
	return Q[hp++];
}

inline bool isempty()
{
	return hp == tp;
}

inline void empty()
{
	hp = tp = 0;
}

void Edmonds_Karp(int s, int t)
{
	bool has_ap;
	
	do
	{
		has_ap = false;
		memset(vis, false, sizeof(vis));
		empty();
		enqueue(s);
		while (!isempty())
		{
			int u = dequeue();
			for (int cur = V[u].first_edge; cur != 0; cur = E[cur].next)
			{
				if (E[cur].flow > 0)
				{
					if (E[cur].endp == t)
					{
						has_ap = true;
						int p = u, pathmin = E[cur].flow;
						while (p != 1)
						{
							pathmin = min(pathmin, E[V[p].pree].flow);
							p = V[p].prev;
						}
						p = u;
						E[cur].flow -= pathmin;
						E[cur ^ 1].flow += pathmin;
						while (p != 1)
						{
							E[V[p].pree].flow -= pathmin;
							E[V[p].pree ^ 1].flow += pathmin;
							p = V[p].prev;
						}
						maxflow += pathmin;
						goto END;
					}
					else if (vis[E[cur].endp] == false)
					{
						V[E[cur].endp].pree = cur;
						V[E[cur].endp].prev = u;
						vis[E[cur].endp] = true;
						enqueue(E[cur].endp);
					}
				}
			}
		}
		
		END:;
	} while (has_ap == true);
}

int main()
{
	// e.g. CodeVS - 1993.
	
	scanf("%d%d", &iec, &ivc);
	for (int i = 0; i < iec; i++)
	{
		int u, v, f;
		scanf("%d%d%d", &u, &v, &f);
		add_edge(u, v, f);
		add_edge(v, u, 0);
	}
	
	Edmonds_Karp(1, ivc);
	
	printf("%d", maxflow);
	
	return 0;
}
