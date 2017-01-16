#include <cstdio>

using namespace std;

int n;
double a[15][15], s[15];

void gaussian_elimination()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			for (int k = n; k >= i; k--)
			{
				a[j][k] -= a[i][k] * (a[j][i] / a[i][i]);
			}
		}
	}
	for (int i = n - 1; i >= 0; i--)
	{
		double b = a[i][n];
		for (int j = n - 1; j > i; j--)
		{
			b -= a[i][j] * s[j];
		}
		s[i] = b / a[i][i];
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			scanf("%lf", &a[i][j]);
		}
		scanf("%lf", &a[i][n]);
	}
	gaussian_elimination();
	for (int i = 0; i < n; i++)
	{
		printf("x[%d] = %.2lf\n", i, s[i]);
	}
	return 0;
}
