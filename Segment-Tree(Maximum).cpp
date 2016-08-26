#include <cstdio>

#define ELEMENT_COUNT 100000

using namespace std;

int d[ELEMENT_COUNT], T[ELEMENT_COUNT * 4], lazy[ELEMENT_COUNT * 4];

inline int max(int x, int y)
{
	return x > y ? x : y;
}

void build_tree(int l, int r, int k)
{
	if (l == r)
	{
		T[k] = d[l];
	}
	else
	{
		int mid = (l + r) >> 1;
		build_tree(l, mid, k << 1);
		build_tree(mid + 1, r, (k << 1) + 1);
		T[k] = max(T[k << 1], T[(k << 1) + 1]);
	}
}

int query(int l, int r, int b, int e, int k)
{
	if (l == b && r == e)
	{
		return T[k];
	}
	
	int mid = (l + r) >> 1;
	if (b > mid)
	{
		return query(mid + 1, r, b, e, (k << 1) + 1);
	}
	else if (e <= mid)
	{
		return query(l, mid, b, e, k << 1);
	}
	else
	{
		return max(query(l, mid, b, mid, k << 1), query(mid + 1, r, mid + 1, e, (k << 1) + 1));
	}
}

void update_one(int l, int r, int v, int x, int k)
{
	if (l == r)
	{
		T[k] = x;
	}
	else
	{
		int mid = (l + r) >> 1;
		if (v <= mid)
		{
			update_one(l, mid, v, x, k << 1);
		}
		else
		{
			update_one(mid + 1, r, v, x, (k << 1) + 1);
		}
		T[k] = max(T[k << 1], T[(k << 1) + 1]);
	}
}

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &d[i]);
	}
	build_tree(0, n - 1, 1);
	while (true)
	{
		int o, a, b;
		scanf("%d", &o);
		switch (o)
		{
		case 1:
			scanf("%d%d", &a, &b);
			printf("%d\n", query(0, n - 1, a - 1, b - 1, 1));
			break;
		case 2:
			scanf("%d%d", &a, &b);
			update_one(0, n - 1, a - 1, b, 1);
			break;
		}
	}
	
	return 0;
}
