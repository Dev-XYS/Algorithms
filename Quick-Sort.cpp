#include <cstdio>
#include <cstdlib>

#define MAX_ELEMENT_COUNT 1000000

using namespace std;

int d[MAX_ELEMENT_COUNT];

void qsort(int l, int r)
{
	if (l < r)
	{
		int x = d[r];
		int j = l - 1;
		
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
		
		qsort(l, j - 1);
		qsort(j + 1, r);
	}
}

int main()
{
	for (int i = 0; i < MAX_ELEMENT_COUNT; i++)
	{
		d[i] = rand();
	}
	
	qsort(0, MAX_ELEMENT_COUNT - 1);
	
	for (int i = 0; i < MAX_ELEMENT_COUNT; i++)
	{
		printf("%d\n", d[i]);
	}
	
	return 0;
}
