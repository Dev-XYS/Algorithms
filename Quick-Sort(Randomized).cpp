#include <cstdio>
#include <climits>

#define INF INT_MAX

#define ELEMENT_COUNT 100000
#define ELEMENT_RANGE (1 << 17)
#define GROUP_RANGE (1 << 2)

using namespace std;

int n, d[ELEMENT_COUNT];

struct node
{
	int v, next;
}A[ELEMENT_COUNT + 1];
int head[ELEMENT_RANGE / GROUP_RANGE], cnt[ELEMENT_RANGE / GROUP_RANGE], vc = 1;

void insert(int v)
{
	int group = v / GROUP_RANGE;
	A[vc].next = head[group];
	head[group] = vc;
	A[vc].v = v;
	cnt[group]++;
	vc++;
}

void bucket_sort()
{
	for (int i = 0; i < n; i++)
	{
		insert(d[i]);
	}
	int ptr = 0;
	for (int i = 0; i < ELEMENT_RANGE / GROUP_RANGE; i++)
	{
		for (int j = 0; j < cnt[i]; j++)
		{
			int minv = INF, ord;
			for (int cur = head[i]; cur != 0; cur = A[cur].next)
			{
				if (A[cur].v < minv)
				{
					minv = A[cur].v;
					ord = cur;
				}
			}
			d[ptr++] = minv;
			A[ord].v = INF;
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
	bucket_sort();
	for (int i = 0; i < n; i++)
	{
		printf("%d ", d[i]);
	}
	return 0;
}
