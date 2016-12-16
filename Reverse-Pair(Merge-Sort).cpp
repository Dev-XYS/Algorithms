#include <cstdio>

#define INF 1000000000
#define ELEMENT_COUNT 100000

using namespace std;

int n, d[ELEMENT_COUNT], ans;

void merge(int o1, int l1, int o2, int l2)
{
	static int a1[ELEMENT_COUNT], a2[ELEMENT_COUNT];
	int k1 = 0, k2 = 0;
	for (int i = 0; i < l1; i++)
	{
		a1[i] = d[i + o1];
	}
	a1[l1] = INF;
	for (int i = 0; i < l2; i++)
	{
		a2[i] = d[i + o2];
	}
	a2[l2] = INF;
	for (int i = 0; i < l1 + l2; i++)
	{
		if (a1[k1] <= a2[k2])
		{
			d[i + o1] = a1[k1++];
		}
		else
		{
			d[i + o1] = a2[k2++];
			ans += (l1 - k1);
		}
	}
}

void merge_sort(int l, int r)
{
	if (l < r)
	{
		int mid = (l + r) >> 1;
		merge_sort(l, mid);
		merge_sort(mid + 1, r);
		merge(l, mid - l + 1, mid + 1, r - mid);
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &d[i]);
	}
	merge_sort(0, n - 1);
	printf("%d", ans);
	return 0;
}
