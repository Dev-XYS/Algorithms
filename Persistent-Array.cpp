#include <cstdio>

#define NIL 0
#define ELEMENT_COUNT 100000
#define EDITION_COUNT 100000
#define POOL_SIZE 1000000

using namespace std;

struct node
{
	node *lch, *rch;
	int v;
	node(int _v = 0) : v(_v) { lch = rch = NIL; }
	void* operator new (size_t);
}*root[EDITION_COUNT], pool[POOL_SIZE];
int top = 0;

int n, d[ELEMENT_COUNT], cur = 0, used = 1;

void* node::operator new (size_t)
{
	return pool + top++;
}

void build(node *&u, int l, int r)
{
	u = new node;
	if (l == r)
	{
		u->v = d[l];
	}
	else
	{
		int mid = (l + r) >> 1;
		build(u->lch, l, mid);
		build(u->rch, mid + 1, r);
	}
}

void modify(node *&u, node *old, int l, int r, int k, int v)
{
	u = new node;
	if (l == r)
	{
		u->v = v;
	}
	else
	{
		int mid = (l + r) >> 1;
		if (k <= mid)
		{
			u->rch = old->rch;
			modify(u->lch, old->lch, l, mid, k, v);
		}
		else
		{
			u->lch = old->lch;
			modify(u->rch, old->rch, mid + 1, r, k, v);
		}
	}
}

int query(node *u, int l, int r, int k)
{
	if (l == r)
	{
		return u->v;
	}
	else
	{
		int mid = (l + r) >> 1;
		if (k <= mid)
		{
			return query(u->lch, l, mid, k);
		}
		else
		{
			return query(u->rch, mid + 1, r, k);
		}
	}
}

int main()
{
	int op, e, k, x;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &d[i]);
	}
	build(root[cur], 1, n);
	while (true)
	{
		scanf("%d", &op);
		if (op == 1)
		{
			scanf("%d%d", &k, &x);
			modify(root[used], root[cur], 1, n, k, x);
			cur = used;
			used++;
		}
		else if (op == 2)
		{
			scanf("%d%d", &e, &k);
			printf("%d\n", query(root[e], 1, n, k));
		}
		else if (op == 3)
		{
			scanf("%d", &e);
			cur = e;
		}
		else if (op == 0)
		{
			break;
		}
		else
		{
			printf("No such command!\n");
		}
	}
	return 0;
}
