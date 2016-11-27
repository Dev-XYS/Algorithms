#include <cstdio>

#define MOD 1000000000
#define MAX 1000

int C[MAX][MAX];

void init_C()
{
	for (int i = 0; i < MAX; i++)
	{
		C[i][0] = 1;
	}
	for (int i = 1; i < MAX; i++)
	{
		for (int j = 1; j <= i; j++)
		{
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
		}
	}
}

int main()
{
	int n, m;
	init_C();
	while (scanf("%d%d", &n, &m) > 0)
	{
		printf("%d\n", C[n][m]);
	}
	return 0;
}
