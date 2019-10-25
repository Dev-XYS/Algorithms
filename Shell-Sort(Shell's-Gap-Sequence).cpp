#include <cstdio>

#define ELEMENT_COUNT 100000

using namespace std;

int n, d[ELEMENT_COUNT];

void Shell_sort()
{
	for (int gc = n >> 1; gc >= 1; gc >>= 1)
	{
		for (int s = 0; s < gc; s++)
		{
			for (int i = s; i < n; i += gc)
			{
				for (int j = i - gc; j >= 0 && d[j] > d[j + gc]; j -= gc)
				{
					int temp = d[j];
					d[j] = d[j + gc];
					d[j + gc] = temp;
				}
			}
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
	Shell_sort();
	for (int i = 0; i < n; i++)
	{
		printf("%d ", d[i]);
	}
	printf("\n");
	return 0;
}
