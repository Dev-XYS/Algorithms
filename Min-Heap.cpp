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

void insert(int x)
{
	H[++heapsize] = x;
	
	int ch = heapsize, p = heapsize >> 1;
	while (H[p] > H[ch] && p >= 1)
	{
		int temp = H[p];
		H[p] = H[ch];
		H[ch] = temp;
		
		ch = p;
		p >>= 1;
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		int x;
		scanf("%d", &x);
		insert(x);
	}
	// Add more actions here.
	
	return 0;
}
