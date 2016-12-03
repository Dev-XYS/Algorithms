#include <cstdio>

#define ELEMENT_COUNT 100000
#define EDITION_COUNT 100000

using namespace std;

struct node
{
	int l, r, sum;
	node *lch, *rch;
}*root[EDITION_COUNT];

int n, d[ELEMENT_COUNT], hs = 0;

void build(int l, int r, node *u)
{
	u->l = l;
	u->r = r;
	if (l == r)
	{
		u->sum = d[l];
	}
	else
	{
		int mid = (l + r) >> 1;
		build(l, mid, u->lch = new node);
		build(mid + 1, r, u->rch = new node);
		u->sum = u->lch->sum + u->rch->sum;
	}
}

int query(int l, int r, node *u)
{
	if (u->l == l && u->r == r)
	{
		return u->sum;
	}
	else
	{
		int mid = (u->l + u->r) >> 1;
		if (r <= mid)
		{
			return query(l, r, u->lch);
		}
		else if (l > mid)
		{
			return query(l, r, u->rch);
		}
		else
		{
			return query(l, mid, u->lch) + query(mid + 1, r, u->rch);
		}
	}
}

void modify(int k, int v, node *u, node *ori)
{
	u->l = ori->l;
	u->r = ori->r;
	if (u->l == u->r)
	{
		u->sum = v;
	}
	else
	{
		int mid = (u->l + u->r) >> 1;
		if (k <= mid)
		{
			u->rch = ori->rch;
			u->lch = new node;
			modify(k, v, u->lch, ori->lch);
		}
		else
		{
			u->lch = ori->lch;
			u->rch = new node;
			modify(k, v, u->rch, ori->rch);
		}
		u->sum = u->lch->sum + u->rch->sum;
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &d[i]);
	}
	build(1, n, root[0] = new node);
	int in, edition, ql, qr, k, v;
	while (true)
	{
		scanf("%d", &in);
		if (in == 1)
		{
			scanf("%d%d%d", &edition, &ql, &qr);
			printf("%d\n", query(ql, qr, root[edition]));
		}
		else if (in == 2)
		{
			scanf("%d%d", &k, &v);
			hs++;
			modify(k, v, root[hs] = new node, root[hs - 1]);
		}
		else if (in == 3)
		{
			printf("Current edition : %d\n", hs);
		}
		else if (in == 0)
		{
			return 0;
		}
		else
		{
			printf("No such command!\n");
		}
	}
	return 0;
}
