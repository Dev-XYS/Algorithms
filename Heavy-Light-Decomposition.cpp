#include <cstdio>

#define VERTEX_COUNT 100000
#define EDGE_COUNT 200000

using namespace std;

struct vertex
{
	int first, depth, fa, fae, hson, size, dfn, top;
}V[VERTEX_COUNT];

struct edge
{
	int endp, next, w;
}E[EDGE_COUNT];

struct segnode
{
	segnode *lch, *rch;
	int sum, lazy;
	void* operator new (size_t size);
}segpool[VERTEX_COUNT * 4];
int segtop = 0;

struct segment_tree
{
	segnode *root;
	int begin, end;
	
	void build(segnode *&u, int l, int r);
	void build();
	void modify(segnode *u, int ul, int ur, int il, int ir, int delta);
	int query(segnode *u, int ul, int ur, int il, int ir);
	int query(int il, int ir);
}seg;

int ivc, ec = 1, dfn = 1, map[VERTEX_COUNT];

void* segnode::operator new (size_t size)
{
	return segpool + segtop++;
}

void segment_tree::build(segnode *&u, int l, int r)
{
	u = new segnode;
	if (l == r)
	{
		u->sum = V[map[l]].fae;
	}
	else
	{
		int mid = (l + r) >> 1;
		build(u->lch, l, mid);
		build(u->rch, mid + 1, r);
		u->sum = u->lch->sum + u->rch->sum;
	}
}

void segment_tree::build()
{
	build(root, begin, end);
}

void segment_tree::modify(segnode *u, int ul, int ur, int il, int ir, int delta)
{
	if (ul == il && ur == ir)
	{
		u->sum += delta * (ur - ul + 1);
		u->lazy += delta;
	}
	else
	{
		int mid = (ul + ur) >> 1;
		if (ir <= mid)
		{
			modify(u->lch, ul, mid, il, ir, delta);
		}
		else if (il > mid)
		{
			modify(u->rch, mid + 1, ur, il, ir, delta);
		}
		else
		{
			modify(u->lch, ul, mid, il, mid, delta);
			modify(u->rch, mid + 1, ur, mid + 1, ir, delta);
		}
		u->sum += u->lch->sum + u->rch->sum;
	}
}

int segment_tree::query(segnode *u, int ul, int ur, int il, int ir)
{
	if (ul == il && ur == ir)
	{
		return u->sum;
	}
	else
	{
		int mid = (ul + ur) >> 1;
		u->lch->sum += u->lazy * (mid - ul + 1);
		u->lch->lazy += u->lazy;
		u->rch->sum += u->lazy * (ur - mid);
		u->rch->lazy += u->lazy;
		u->lazy = 0;
		if (ir <= mid)
		{
			return query(u->lch, ul, mid, il, ir);
		}
		else if (il > mid)
		{
			return query(u->rch, mid + 1, ur, il, ir);
		}
		else
		{
			return query(u->lch, ul, mid, il, mid) + query(u->rch, mid + 1, ur, mid + 1, ir);
		}
	}
}

int segment_tree::query(int il, int ir)
{
	return query(root, begin, end, il, ir);
}

void add_edge(int u, int v, int w)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	E[ec].w = w;
	ec++;
}

void DFS1(int u, int depth, int fa, int fae)
{
	int hson = 0;
	V[u].depth = depth;
	V[u].fa = fa;
	V[u].fae = fae;
	V[u].size = 1;
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		if (E[cur].endp != fa)
		{
			DFS1(E[cur].endp, depth + 1, u, E[cur].w);
			V[u].size += V[E[cur].endp].size;
			if (V[E[cur].endp].size > V[hson].size)
			{
				hson = E[cur].endp;
			}
		}
	}
	V[u].hson = hson;
}

void DFS2(int u, int fa, int top)
{
	V[u].dfn = dfn++;
	map[V[u].dfn] = u;
	V[u].top = top;
	if (V[u].hson != 0)
	{
		DFS2(V[u].hson, u, top);
	}
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		if (E[cur].endp != V[u].hson && E[cur].endp != fa)
		{
			DFS2(E[cur].endp, u, E[cur].endp);
		}
	}
}

int query(int x, int y)
{
	int res = 0;
	while (V[x].top != V[y].top)
	{
		int _x = V[x].top == x ? V[x].fa : V[x].top, _y = V[y].top == y ? V[y].fa : V[y].top;
		if (V[_x].depth < V[_y].depth)
		{
			int temp = x;
			x = y;
			y = temp;
		}
		res += V[x].top == x ? V[x].fae : seg.query(V[V[x].top].dfn + 1, V[x].dfn);
		x = V[x].top == x ? V[x].fa : V[x].top;
	}
	if (V[x].depth > V[y].depth)
	{
		res += seg.query(V[y].dfn, V[x].dfn) - V[y].fae;
	}
	else
	{
		res += seg.query(V[x].dfn, V[y].dfn) - V[x].fae;
	}
	return res;
}

int main()
{
	int u, v, w;
	scanf("%d", &ivc);
	for (int i = 1; i < ivc; i++)
	{
		scanf("%d%d%d", &u, &v, &w);
		add_edge(u, v, w);
		add_edge(v, u, w);
	}
	DFS1(1, 1, 0, 0);
	DFS2(1, 0, 1);
	seg.begin = 1;
	seg.end = ivc;
	seg.build();
	while (true)
	{
		scanf("%d%d", &u, &v);
		printf("%d\n", query(u, v));
	}
	return 0;
}
