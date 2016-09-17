#include <cstdio>

using namespace std;

int n, q;
int w[100][100];

inline int min(int x, int y)
{
	return x < y ? x : y;
}

void Floyd_Warshall()
{
	for (int k = 0; k < n; k++)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				w[i][j] = min(w[i][j], w[i][k] + w[k][j]);
			}
		}
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			scanf("%d", &w[i][j]);
		}
	}
	Floyd_Warshall();
	scanf("%d", &q);
	for (int i = 0; i < q; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		printf("%d\n", w[a - 1][b - 1]);
	}
	return 0;
}
