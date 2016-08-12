#include <cstdio>
#include <cstdlib>

using namespace std;

int data[1000];

void bubble_sort(int *d, int n)
{
	for (int k = 1; k < n; k++)
	{
		for (int i = 1; i < n; i++)
		{
			if (d[i] < d[i - 1])
			{
				int temp = d[i];
				d[i] = d[i - 1];
				d[i - 1] = temp;
			}
		}
	}
}

int main()
{
	for (int i = 0; i < 1000; i++)
	{
		data[i] = rand();
	}
	
	bubble_sort(data, 1000);
	
	for (int i = 0; i < 1000; i++)
	{
		printf("%d\n", data[i]);
	}
	
	return 0;
}
