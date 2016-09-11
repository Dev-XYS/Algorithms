#include <cstdio>

#define ELEMENT_COUNT 200000

using namespace std;

struct node
{
	int l, r;
	long long sum, lazy;
}T[ELEMENT_COUNT * 4];

int n, q;
int d[ELEMENT_COUNT];

void build_tree(int l, int r, int k)
{
	T[k].l = l;
	T[k].r = r;
	if (l == r)
	{
		T[k].sum = d[l];
	}
	else
	{
		int mid = (l + r) >> 1;
		build_tree(l, mid, k << 1);
		build_tree(mid + 1, r, (k << 1) + 1);
		T[k].sum = T[k << 1].sum + T[(k << 1) + 1].sum;
	}
}

long long get_sum(int l, int r, int k)
{
	if (l == T[k].l && r == T[k].r)
	{
		return T[k].sum + T[k].lazy * (r - l + 1);
	}
	else
	{
		T[k].sum += T[k].lazy * (T[k].r - T[k].l + 1);
		T[k << 1].lazy += T[k].lazy;
		T[(k << 1) + 1].lazy += T[k].lazy;
		T[k].lazy = 0;
		if (r <= T[k << 1].r)
		{
			return get_sum(l, r, k << 1);
		}
		else if (l >= T[(k << 1) + 1].l)
		{
			return get_sum(l, r, (k << 1) + 1);
		}
		else
		{
			return get_sum(l, T[k << 1].r, k << 1) + get_sum(T[(k << 1) + 1].l, r, (k << 1) + 1);
		}
	}
}

long long delta;
void update_segment(int l, int r, int k)
{
	if (l == T[k].l && r == T[k].r)
	{
		T[k].lazy += delta;
	}
	else
	{
		T[k].sum += delta * (r - l + 1); 
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
	scanf("%d", &q); 
	while (q--)
	{
		int o, a, b;
		long long d;
		scanf("%d", &o);
		switch (o)
		{
		case 1:
			scanf("%d%d%lld", &a, &b, &d);
			delta = d;
			update_segment(a - 1, b - 1, 1);
			break;
		case 2:
			scanf("%d%d", &a, &b);
			printf("%lld\n", get_sum(a - 1, b - 1, 1));
			break;
		case 3:
			for (int i = 0; i < n * 2; i++)
			{
				printf("%2d ", i);
			}
			printf("\n");
			for (int i = 0; i < n * 2; i++)
			{
				printf("%2lld ", T[i].lazy);
			}
			printf("\n");
			break;
		default:
			printf("Instruction incorrect!\n");
		}
	}
	return 0;
}
