#include <cstdio>

#define MAX_ELEMENT 100000000

using namespace std;

int prime[MAX_ELEMENT], pc, div[MAX_ELEMENT], phi[MAX_ELEMENT];

void sieve(int n)
{
	phi[1] = 1;
	for (int i = 2; i <= n; i++)
	{
		if (div[i] == 0)
		{
			prime[pc++] = i;
			div[i] = i;
			phi[i] = i - 1;
		}
		for (int j = 0; j < pc; j++)
		{
			if (i * prime[j] > n) break;
			div[i * prime[j]] = prime[j];
			if (i % prime[j] == 0)
			{
				phi[i * prime[j]] = phi[i] * prime[j];
				break;
			}
			else
			{
				phi[i * prime[j]] = phi[i] * (prime[j] - 1);
			}
		}
	}
}

int main()
{
	int n;
	scanf("%d", &n);
	sieve(n);
	for (int i = 1; i <= n; i++)
	{
		printf("phi(%d) = %d\n", i, phi[i]);
	}
	return 0;
}
