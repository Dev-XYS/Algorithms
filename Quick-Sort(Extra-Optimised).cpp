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
		int x = d[rand() % (r - l + 1) + l];
		int j = l - 1;
		
		for (int i = l; i <= r; i++)
		{
			if (d[i] < x)
			{
				j++;
				int temp = d[i];
				d[i] = d[j];
				d[j] = temp;
			}
			else if (d[i] == x)
			{
				if ((flag++ & 1) == 0)
				{
					j++;
					int temp = d[i];
					d[i] = d[j];
					d[j] = temp;
				}
			}
		}
		
		qsort(l, j - 1);
		qsort(j + 1, r);
	}
}

int main()
{
	for (int i = 0; i < ELEMENT_COUNT; i++)
	{
		// All elements are the same.
		d[i] = 0;
	}
	
	// You can compare the following two functions.
	qsort(0, ELEMENT_COUNT - 1);
	sort(d, d + ELEMENT_COUNT);
	
	return 0;
}
