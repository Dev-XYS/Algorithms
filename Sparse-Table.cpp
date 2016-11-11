#include <cstdio>

using namespace std;

int n, m;
int st[1000010][21], pow2[21];

inline int max(int x, int y)
{
	return x > y ? x : y;
}

inline int _log2(int x)
{
	int res = 0;
	while (x > 1)
	{
		x >>= 1;
		res++;
	}
	return res;
}

void init_pow2()
{
	pow2[0] = 1;
	for (int i = 1; i <= 20; i++)
	{
		pow2[i] = pow2[i - 1] * 2;
	}
}

void build_st()
{
	init_pow2();
	for (int i = 1; i <= 20; i++)
	{
		for (int j = 0; j < n; j++)
		{
			st[j][i] = max(st[j][i - 1], st[j + pow2[i - 1]][i - 1]);
		}
	}
}

int get_max(int l, int r)
{
	int x = _log2(r - l + 1);
	return max(st[l][x], st[r - pow2[x] + 1][x]);
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &st[i][0]);
	}
	build_st();
	for (int i = 0; i < m; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		printf("%d\n", get_max(a - 1, b - 1));
	}
	
	return 0;
}
