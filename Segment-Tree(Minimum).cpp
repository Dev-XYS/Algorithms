#include <cstdio>

using namespace std;

struct node
{
	int l, r, min, lazy;
}T[4000010];

int d[1000010];

inline int min(int x, int y)
{
	return x < y ? x : y;
}

void build_tree(int l, int r, int k)
{
	T[k].l = l;
	T[k].r = r;
	if (l == r)
	{
		T[k].min = d[l];
	}
	else
	{
		int mid = (l + r) >> 1;
		build_tree(l, mid, k << 1);
		build_tree(mid + 1, r, (k << 1) + 1);
		T[k].min = min(T[k << 1].min, T[(k << 1) + 1].min);
	}
}

int delta;
void update(int l, int r, int k)
{
	if (T[k].l == l && T[k].r == r)
	{
		T[k].lazy += delta;
		T[k].min += delta;
	}
	else
	{
		int mid = (T[k].l + T[k].r) >> 1;
		if (r <= mid)
		{
			update(l, r, k << 1);
		}
		else if (l > mid)
		{
			update(l, r, (k << 1) + 1);
		}
		else
		{
			update(l, mid, k << 1);
			update(mid + 1, r, (k << 1) + 1);
		}
		T[k].min = min(T[k << 1].min, T[(k << 1) + 1].min);
	}
}

int query(int l, int r, int k)
{
	if (T[k].l == l && T[k].r == r)
	{
		return T[k].min;
	}
	else
	{
		int mid = (T[k].l + T[k].r) >> 1, res;
		T[k << 1].lazy += T[k].lazy;
		T[k << 1].min += T[k].lazy;
		T[(k << 1) + 1].lazy += T[k].lazy;
		T[(k << 1) + 1].min += T[k].lazy;
		T[k].lazy = 0;
		if (r <= mid)
		{
			res = query(l, r, k << 1);
		}
		else if (l > mid)
		{
			res = query(l, r, (k << 1) + 1);
		}
		else
		{
			res = min(query(l, mid, k << 1), query(mid + 1, r, (k << 1) + 1));
		}
		T[k].min = min(T[k << 1].min, T[(k << 1) + 1].min);
		return res;
	}
}

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &d[i]);
	}
	build_tree(1, n, 1);
	while (true)
	{
		int o, a, b, d;
		scanf("%d", &o);
		switch (o)
		{
		case 1:
			scanf("%d%d", &a, &b);
			printf("%d\n", query(a, b, 1));
			break;
		case 2: 
			scanf("%d%d%d", &a, &b, &d);
			delta = d;
			update(a, b, 1);
			break;
		}
	}
	return 0;
}
