#include <cstdio>
#include <cstdlib>
#include <algorithm>

#define ELEMENT_COUNT 1000000 

using namespace std;

int d[ELEMENT_COUNT];

int flag = 0; 

void qsort(int l, int r)
{
	if (l < r)
	{
		int _rand = rand() % (r - l + 1) + l;
		
		int temp = d[_rand];
		d[_rand] = d[r];
		d[r] = temp;
		
		int x = d[r];
		int j = l - 1;
		
		for (int i = l; i < r; i++)
		{
			if (d[i] < x)
			{
				j++;
				temp = d[i];
				d[i] = d[j];
				d[j] = temp;
			}
			else if (d[i] == x)
			{
				if ((flag++ & 1) == 0)
				{
					j++;
					temp = d[i];
					d[i] = d[j];
					d[j] = temp;
				}
			}
		}
		j++;
		temp = d[r];
		d[r] = d[j];
		d[j] = temp;
		
		qsort(l, j - 1);
		qsort(j + 1, r);
	}
}

int main()
{
	int n;
	scanf("%d", &n);
	
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &d[i]);
	}
	
	qsort(0, n - 1);
	
	for (int i = 0; i < n; i++)
	{
		printf("%d ", d[i]);
	}
	
	return 0;
}
