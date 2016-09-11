#include <cstdio>

#define ELEMENT_COUNT 100000

using namespace std;

struct node
{
	int l, r, max, lazy;
}T[ELEMENT_COUNT * 4];

int n;
int d[ELEMENT_COUNT];

inline int max(int x, int y)
{
	return x > y ? x : y;
}

void build_tree(int l, int r, int k)
{
	T[k].l = l;
	T[k].r = r;
	if (l == r)
	{
		T[k].max = d[l];
	}
	else
	{
		int mid = (l + r) >> 1;
		build_tree(l, mid, k << 1);
		build_tree(mid + 1, r, (k << 1) + 1);
		T[k].max = max(T[k << 1].max, T[(k << 1) + 1].max);
	}
}

int get_max(int l, int r, int k)
{
	if (l == T[k].l && r == T[k].r)
	{
		return T[k].max + T[k].lazy;
	}
	else
	{
		T[k].max += T[k].lazy;
		T[k << 1].lazy += T[k].lazy;
		T[(k << 1) + 1].lazy += T[k].lazy;
		T[k].lazy = 0;
		if (r <= T[k << 1].r)
		{
			return get_max(l, r, k << 1);
		}
		else if (l >= T[(k << 1) + 1].l)
		{
			return get_max(l, r, (k << 1) + 1);
		}
		else
		{
			return max(get_max(l, T[k << 1].r, k << 1), get_max(T[(k << 1) + 1].l, r, (k << 1) + 1));
		}
	}
}

int delta;
void update_segment(int l, int r, int k)
{
	if (l == T[k].l && r == T[k].r)
	{
		T[k].lazy += delta;
	}
	else
	{
		if (r <= T[k << 1].r)
		{
			update_segment(l, r, k << 1);
		}
		else if (l >= T[(k << 1) + 1].l)
		{
			update_segment(l, r, (k << 1) + 1);
		}
		else
		{
			update_segment(l, T[k << 1].r, k << 1);
			update_segment(T[(k << 1) + 1].l, r, (k << 1) + 1);
		}
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &d[i]);
	}
	build_tree(0, n - 1, 1);
	while (true)
	{
		int o, a, b, d;
		scanf("%d", &o);
		switch (o)
		{
		case 1:
			scanf("%d%d", &a, &b);
			printf("%d\n", get_max(a - 1, b - 1, 1));
			break;
		case 2:
			scanf("%d%d%d", &a, &b, &d);
			delta = d;
			update_segment(a - 1, b - 1, 1);
			break;
		case 3:
			for (int i = 0; i < n * 2; i++)
			{
				printf("%2d ", i);
			}
			printf("\n");
			for (int i = 0; i < n * 2; i++)
			{
				printf("%2d ", T[i].lazy);
			}
			printf("\n");
			break;
		default:
			printf("Instruction incorrect!\n");
		}
	}
	return 0;
}
