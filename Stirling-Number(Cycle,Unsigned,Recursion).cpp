#include <cstdio>

using namespace std;

int n, su[100][100];

void init_su()
{
	for (int i = 1; i <= n; i++)
	{
		su[i][0] = 0;
		su[0][i] = 0;
	}
	su[0][0] = 1;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			su[i][j] = su[i - 1][j - 1] + su[i - 1][j] * (i - 1);
		}
	}
}

int main()
{
	scanf("%d", &n);
	init_su();
	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			printf("%5d ", su[i][j]);
		}
		printf("\n");
	}
	return 0;
}
