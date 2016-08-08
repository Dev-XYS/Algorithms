#include <cstdio>

#define MAX_VERTEX_COUNT 100000
#define MAX_EDGE_COUNT 100000

using namespace std;

struct vertex
{
	int first_edge;
	bool finish;
}V[MAX_VERTEX_COUNT];

struct edge
{
	int endp, next;
}E[MAX_EDGE_COUNT];

int ec = 1;

struct qvertex
{
	int first_edge;
}QV[MAX_VERTEX_COUNT];

struct qedge
{
	int endp, next, ans;
}QE[MAX_EDGE_COUNT];

int qec = 1;

int fa[MAX_VERTEX_COUNT], size[MAX_VERTEX_COUNT], ancestor[MAX_VERTEX_COUNT];

void add_edge(int u, int v)
{
	E[ec].next = V[u].first_edge;
	V[u].first_edge = ec;
	E[ec].endp = v;
	ec++;
}

void add_qedge(int u, int v)
{
	QE[qec].next = QV[u].first_edge;
	QV[u].first_edge = qec;
	QE[qec].endp = v;
	qec++;
}

void initial_set(int c)
{
	for (int i = 1; i <= c; i++)
	{
		fa[i] = i;
		size[i] = 1;
	}
}

int get_root(int x)
{
	if (fa[x] == x)
	{
		return x;
	}
	return (fa[x] = get_root(fa[x]));
}

void merge(int x, int y)
{
	int rtx = get_root(x), rty = get_root(y);
	if (size[rtx] < size[rty])
	{
		fa[rtx] = rty;
		size[rty] += size[rtx];
	}
	else
	{
		fa[rty] = rtx;
		size[rtx] += size[rty];
	}
}

void DFS(int u, int prev)
{
	ancestor[get_root(u)] = u;
	
	for (int cur = V[u].first_edge; cur != 0; cur = E[cur].next)
	{
		if (E[cur].endp != prev)
		{
			DFS(E[cur].endp, u);
			merge(u, E[cur].endp);
			ancestor[get_root(u)] = u;
		}
	}
	V[u].finish = true;
	
	for (int cur = QV[u].first_edge; cur != 0; cur = QE[cur].next)
	{
		if (V[QE[cur].endp].finish == true)
		{
			QE[cur].ans = ancestor[get_root(QE[cur].endp)];
		}
	}
}

int main()
{
	int ivc, iqc;
	scanf("%d%d", &ivc, &iqc);
	
	for (int i = 1; i < ivc; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add_edge(u, v);
		add_edge(v, u);
	}
	
	for (int i = 0; i < iqc; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add_qedge(u, v);
		add_qedge(v, u);
	}
	
	initial_set(ivc);
	
	DFS(1, 0);
	
	for (int i = 1; i <= ivc; i++)
	{
		for (int cur = QV[i].first_edge; cur != 0; cur = QE[cur].next)
		{
			if (QE[cur].ans != 0)
			{
				printf("The LCA of %d and %d is %d.\n", i, QE[cur].endp, QE[cur].ans);
			}
		}
	}
	
	return 0;
}
