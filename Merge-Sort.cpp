#include <cstdio>
#include <cstdlib>

#define INF 2000000000
#define MAX_ELEMENT_COUNT 100000

using namespace std;

int d[MAX_ELEMENT_COUNT];

void merge(int l, int m, int r)
{
	static int al[MAX_ELEMENT_COUNT], ar[MAX_ELEMENT_COUNT];
	int il, ir;
	
	// Copy the data to the temporary array al & ar.
	for (il = l; il <= m; il++)
	{
		al[il] = d[il];
	}
	al[m + 1] = INF;
	for (ir = m + 1; ir <= r; ir++)
	{
		ar[ir] = d[ir];
	}
	ar[r + 1] = INF;
	
	// Merge al & ar into array d.
	il = l;
	ir = m + 1;
	for (int i = l; i <= r; i++)
	{
		if (al[il] < ar[ir])
		{
			d[i] = al[il++];
		}
		else
		{
			d[i] = ar[ir++];
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
		merge(l, mid, r);
	}
}

int main()
{
	for (int i = 0; i < MAX_ELEMENT_COUNT; i++)
	{
		d[i] = rand();
	}
	
	merge_sort(0, MAX_ELEMENT_COUNT - 1);
	
	for (int i = 0; i < MAX_ELEMENT_COUNT; i++)
	{
		printf("%d\n", d[i]);
	}
	
	return 0;
}
