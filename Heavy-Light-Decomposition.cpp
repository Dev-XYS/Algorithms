#include <cstdio>
#include <algorithm>

#define NIL 0
#define INF 1000000000
#define VERTEX_COUNT 100000
#define EDGE_COUNT 200000
#define POOL_SIZE 200000

using namespace std;

struct edge;
struct vertex
{
	edge *first;
	int w, depth, size, ord;
	vertex *p, *heavy, *top;
}*nil, V[VERTEX_COUNT];

struct edge
{
	edge *next;
	vertex *endp;
	edge(edge *_next = NIL, vertex *_endp = nil);
	void* operator new (size_t);
}E[EDGE_COUNT];

edge::edge(edge *_next, vertex *_endp) : next(_next), endp(_endp) { }

int Etop = 0;
void* edge::operator new (size_t)
{
	return E + Etop++;
}

struct node
{
	node *lch, *rch;
	int sum, max;
	node();
	void* operator new (size_t);
}*root, pool[POOL_SIZE];

node::node() : lch(NIL), rch(NIL), sum(0), max(0) { }

int pooltop = 0;
void* node::operator new (size_t)
{
	return pool + pooltop++;
}

int ivc, m, ord = 0;
vertex *map[VERTEX_COUNT];

void add_edge(vertex *u, vertex *v)
{
	u->first = new edge(u->first, v);
}

void DFS1(vertex *u, vertex *p, int depth)
{
	vertex *heavy = nil;
	u->p = p;
	u->depth = depth;
	u->size = 1;
	for (edge *cur = u->first; cur != NIL; cur = cur->next)
	{
		if (cur->endp != p)
		{
			DFS1(cur->endp, u, depth + 1);
			u->size += cur->endp->size;
			if (cur->endp->size > heavy->size)
			{
				heavy = cur->endp;
			}
		}
	}
	u->heavy = heavy;
}

void DFS2(vertex *u, vertex *top)
{
	u->top = top;
	u->ord = ++ord;
	map[ord] = u;
	if (u->heavy != nil)
	{
		DFS2(u->heavy, top);
	}
	for (edge *cur = u->first; cur != NIL; cur = cur->next)
	{
		if (cur->endp != u->heavy && cur->endp != u->p)
		{
			DFS2(cur->endp, cur->endp);
		}
	}
}

void build(node *&u, int l, int r)
{
	u = new node;
	if (l == r)
	{
		u->sum = u->max = map[l]->w;
	}
	else
	{
		int mid = (l + r) >> 1;
		build(u->lch, l, mid);
		build(u->rch, mid + 1, r);
		u->sum = u->lch->sum + u->rch->sum;
		u->max = max(u->lch->max, u->rch->max);
	}
}

void modify(node *u, int l, int r, int k, int x)
{
	if (l == r)
	{
		u->sum = u->max = x;
	}
	else
	{
		int mid = (l + r) >> 1;
		if (k <= mid)
		{
			modify(u->lch, l, mid, k, x);
		}
		else
		{
			modify(u->rch, mid + 1, r, k, x);
		}
		u->sum = u->lch->sum + u->rch->sum;
		u->max = max(u->lch->max, u->rch->max);
	}
}

int query_sum(node *u, int l, int r, int ql, int qr)
{
	if (l == ql && r == qr)
	{
		return u->sum;
	}
	int mid = (l + r) >> 1;
	if (qr <= mid)
	{
		return query_sum(u->lch, l, mid, ql, qr);
	}
	else if (ql > mid)
	{
		return query_sum(u->rch, mid + 1, r, ql, qr);
	}
	else
	{
		return query_sum(u->lch, l, mid, ql, mid) + query_sum(u->rch, mid + 1, r, mid + 1, qr);
	}
}

int query_max(node *u, int l, int r, int ql, int qr)
{
	if (l == ql && r == qr)
	{
		return u->max;
	}
	int mid = (l + r) >> 1;
	if (qr <= mid)
	{
		return query_max(u->lch, l, mid, ql, qr);
	}
	else if (ql > mid)
	{
		return query_max(u->rch, mid + 1, r, ql, qr);
	}
	else
	{
		return max(query_max(u->lch, l, mid, ql, mid), query_max(u->rch, mid + 1, r, mid + 1, qr));
	}
}

void tmodify(vertex *x, int v)
{
	modify(root, 1, ivc, x->ord, v);
}

int tquery_sum(vertex *x, vertex *y)
{
	int res = 0;
	vertex *ux, *uy;
	while (x->top != y->top)
	{
		ux = x->top == x ? x->p : x->top;
		uy = y->top == y ? y->p : y->top;
		if (ux->depth < uy->depth)
		{
			swap(x, y);
		}
		if (x->top == x)
		{
			res += query_sum(root, 1, ivc, x->ord, x->ord);
			x = x->p;
		}
		else
		{
			res += query_sum(root, 1, ivc, x->top->ord + 1, x->ord);
			x = x->top;
		}
	}
	if (x->depth > y->depth)
	{
		swap(x, y);
	}
	res += query_sum(root, 1, ivc, x->ord, y->ord);
	return res;
}

int tquery_max(vertex *x, vertex *y)
{
	int res = -INF;
	vertex *ux, *uy;
	while (x->top != y->top)
	{
		ux = x->top == x ? x->p : x->top;
		uy = y->top == y ? y->p : y->top;
		if (ux->depth < uy->depth)
		{
			swap(x, y);
		}
		if (x->top == x)
		{
			res = max(res, query_max(root, 1, ivc, x->ord, x->ord));
			x = x->p;
		}
		else
		{
			res = max(res, query_max(root, 1, ivc, x->top->ord + 1, x->ord));
			x = x->top;
		}
	}
	if (x->depth > y->depth)
	{
		swap(x, y);
	}
	res = max(res, query_max(root, 1, ivc, x->ord, y->ord));
	return res;
}
		
int main()
{
	int u, v, a, b;
	char op[10];
	scanf("%d", &ivc);
	for (int i = 1; i < ivc; i++)
	{
		scanf("%d%d", &u, &v);
		add_edge(V + u, V + v);
		add_edge(V + v, V + u);
	}
	for (int i = 1; i <= ivc; i++)
	{
		scanf("%d", &(V + i)->w);
	}
	nil = new vertex;
	nil->size = 0;
	DFS1(V + 1, nil, 1);
	DFS2(V + 1, V + 1);
	build(root, 1, ivc);
	scanf("%d", &m);
	while (m--)
	{
		scanf("%s%d%d", op, &a, &b);
		switch (op[1])
		{
		case 'H':
			tmodify(V + a, b);
			break;
		case 'S':
			printf("%d\n", tquery_sum(V + a, V + b));
			break;
		case 'M':
			printf("%d\n", tquery_max(V + a, V + b));
			break;
		}
	}
	return 0;
}
