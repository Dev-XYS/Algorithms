#include <cstdio>

#define MOD 1000000007
#define MAX_ELEMENT 10000000

int rev[MAX_ELEMENT];

void sieve(int n)
{
	rev[1] = 1;
	for (int i = 2; i <= n; i++)
	{
		rev[i] = (int)(-(long long)(MOD / i) * (long long)rev[MOD % i] % (long long)MOD);
		rev[i] = (rev[i] % MOD + MOD) % MOD;
	}
}

int main()
{
	int n;
	scanf("%d", &n);
	sieve(n);
	for (int i = 1; i <= n; i++)
	{
		printf("rev(%d) = %d\n", i, rev[i]);
	}
	return 0;
}
