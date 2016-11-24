#include <cstdio>

#define ELEMENT_COUNT 100000

using namespace std;

int n, d[ELEMENT_COUNT];
int pow10[] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000 };

void radix_sort()
{
	static int c[10], t[11], _d[ELEMENT_COUNT];
	for (int k = 0; k < 8; k++)
	{
		for (int i = 0; i < 10; i++)
		{
			c[i] = t[i] = 0;
		}
		for (int i = 0; i < n; i++)
		{
			c[d[i] / pow10[k] % 10 + 1]++;
		}
		for (int i = 1; i < 10; i++)
		{
			c[i] += c[i - 1];
		}
		for (int i = 0; i < n; i++)
		{
			int w = d[i] / pow10[k] % 10;
			_d[c[w] + t[w]] = d[i];
			t[w]++;
		}
		for (int i = 0; i < n; i++)
		{
			d[i] = _d[i];
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
	radix_sort();
	for (int i = 0; i < n; i++)
	{
		printf("%d\n", d[i]);
	}
	return 0;
}
