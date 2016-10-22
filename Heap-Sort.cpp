#include <cstdio>
#include <cstdlib>

#define MAX_HEAP_SIZE 100000

using namespace std;

int n, H[MAX_HEAP_SIZE], heapsize;

void min_heapify(int i)
{
	int smallest = i;
	int lch = i << 1;
	int rch = lch + 1;
	
	if (lch <= heapsize && H[smallest] > H[lch])
	{
		smallest = lch;
	}
	if (rch <= heapsize && H[smallest] > H[rch])
	{
		smallest = rch;
	}
	
	if (smallest != i)
	{
		int temp = H[smallest];
		H[smallest] = H[i];
		H[i] = temp;
		min_heapify(smallest);
	}
}

void build_heap()
{
	for (int i = heapsize >> 1; i >= 1; i--)
	{
		min_heapify(i);
	}
}

int extract_min()
{
	int res = H[1];
	H[1] = H[heapsize--];
	min_heapify(1);
	return res;
}

int main()
{
	scanf("%d", &n);
	heapsize = n;
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &H[i]);
	}
	build_heap();
	while (heapsize > 0)
	{
		printf("%d\n", extract_min());
	}
	
	return 0;
}
