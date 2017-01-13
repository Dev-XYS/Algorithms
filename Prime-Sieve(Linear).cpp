#include <cstdio>

#define MAX_ELEMENT 1000000

using namespace std;

int prime[MAX_ELEMENT], pc, div[MAX_ELEMENT];

void sieve(int n)
{
	for (int i = 2; i <= n; i++)
	{
		if (div[i] == 0)
		{
			prime[pc++] = i;
			div[i] = i;
		}
		for (int j = 0; j < pc; j++)
		{
			if (i * prime[j] > n) break;
			div[i * prime[j]] = prime[j];
			if (div[i] == prime[j]) break;
		}
	}
}

int main()
{
	int n;
	scanf("%d", &n);
	sieve(n);
	for (int i = 0; i < pc; i++)
	{
		printf("%d ", prime[i]);
	}
	printf("\n");
	return 0;
}
