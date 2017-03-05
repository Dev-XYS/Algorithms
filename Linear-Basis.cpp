#include <cstdio>

using namespace std;

int n, d[100000], b[32], bsize;

void linear_basis()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 30; j >= 0 && d[i] != 0; j--)
		{
			if ((d[i] >> j) == 0) continue;
			else if (b[j] != 0) d[i] ^= b[j];
			else
			{
				b[j] = d[i];
				bsize++;
				break;
			}
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
	linear_basis();
	return 0;
}
