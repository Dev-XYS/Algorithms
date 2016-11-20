#include <cstdio>

#define ELEMENT_COUNT 10000

using namespace std;

int n, k, d[ELEMENT_COUNT];

int partition(int l, int r)
{
	int x = d[r], j = l - 1;
	for (int i = l; i <= r; i++)
	{
		if (d[i] <= x)
		{
			j++;
			int temp = d[i];
			d[i] = d[j];
			d[j] = temp;
		}
	}
	return j + 1;
}

int select(int k)
{
	int l = 0, r = n - 1;
	while (l < r)
	{
		int ord = partition(l, r);
		if (ord < k)
		{
			l = ord;
		}
		else if (ord > k)
		{
			r = ord - 2;
		}
		else
		{
			return d[ord - 1];
		}
	}
	return d[l];
}

int main()
{
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &d[i]);
	}
	int kth = select(k);
	printf("%d", kth);
	return 0;
}
