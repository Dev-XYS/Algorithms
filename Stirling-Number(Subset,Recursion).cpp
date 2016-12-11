#include <cstdio>

using namespace std;

int n, S[100][100];

void init_S()
{
	for (int i = 1; i <= n; i++)
	{
		S[i][0] = 0;
		S[0][i] = 0;
	}
	S[0][0] = 1;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= i; j++)
		{
			S[i][j] = S[i - 1][j - 1] + S[i - 1][j] * j;
		}
	}
}

int main()
{
	scanf("%d", &n);
	init_S();
	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			printf("%5d ", S[i][j]);
		}
		printf("\n");
	}
	return 0;
}
