#include <cstdio>

#define INF 1000000000

#define VERTEX_COUNT 100010
#define EDGE_COUNT 1000010

using namespace std;

struct vertex
{
	int first_edge;
	int dis, hpos;
}V[VERTEX_COUNT];

struct edge
{
	int endp, next;
	int w;
}E[EDGE_COUNT];

int ec = 1;
int ivc, iec;

int H[VERTEX_COUNT], pos[VERTEX_COUNT];
int heapsize;

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

void build_heap(int s)
{
	heapsize = ivc;
	for (int i = 1; i <= ivc; i++)
	{
		H[i] = i;
		pos[i] = i;
	}
	H[s] = 1;
	pos[1] = s;
	H[1] = s;
	pos[s] = 1;
}

void heap_sink(int i)
{
	int lch = i << 1;
	int rch = lch + 1;
	int smallest = i;
	
	if (lch <= heapsize && V[H[lch]].dis < V[H[smallest]].dis)
	{
		smallest = lch;
	}
	if (rch <= heapsize && V[H[rch]].dis < V[H[smallest]].dis)
	{
		smallest = rch;
	}
	
	if (smallest != i)
	{
		V[H[smallest]].hpos = i;
		V[H[i]].hpos = smallest;
		int temp = H[i];
		H[i] = H[smallest];
		H[smallest] = temp;
		heap_sink(smallest);
	}
}

void heap_float(int i)
{
	int p = i >> 1;
	while (p >= 1 && V[H[i]].dis < V[H[p]].dis)
	{
		pos[H[i]] = p;
		pos[H[p]] = i;
		int temp = H[i];
		H[i] = H[p];
		H[p] = temp;
		i = p;
		p = i >> 1;
	}
}

int extract_min()
{
	int res = H[1];
	H[1] = H[heapsize--];
	pos[H[1]] = 1;
	heap_sink(1);
	return res;
}

void Dijkstra(int s)
{
	initial_single_source(s);
	build_heap(s);
	
	while (heapsize > 0)
	{
		int u = extract_min();
		for (int cur = V[u].first_edge; cur != 0; cur = E[cur].next)
		{
			int newpath = V[u].dis + E[cur].w;
			if (newpath < V[E[cur].endp].dis)
			{
				V[E[cur].endp].dis = newpath;
				heap_float(pos[E[cur].endp]);
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
	}
	
	Dijkstra(1);
	
	printf("%d", V[ivc].dis);
	
	return 0;
}
