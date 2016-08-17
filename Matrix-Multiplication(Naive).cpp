#include <cstdio>

using namespace std;

int A[100][100], B[100][100], R[100][100];

// Matrix A is p columns and m rows. Matrix B is n columns and p rows.
void matrix_multiplication(int p, int m, int n)
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < p; k++)
			{
				R[i][j] += A[i][k] * B[k][j];
			}
		}
	}
}

int main()
{
	int p, m, n;
	scanf("%d%d%d", &p, &m, &n);
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < p; j++)
		{
			scanf("%d", &A[i][j]);
		}
	}
	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < n; j++)
		{
			scanf("%d", &B[i][j]);
		}
	}
	
	matrix_multiplication(p, m, n);
	
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%d ", R[i][j]);
		}
		printf("\n");
	}
	
	return 0;
}
