#include <cstdio>

#define LOWBIT(x) ((x) & (-x))

#define ELEMENT_COUNT 1050
#define MOD 45679

using namespace std;

// Array D must begin with 1.
int D[ELEMENT_COUNT], T[ELEMENT_COUNT];

// The size of D;
int n = 1024;

void build_tree(int c)
{
	for (int i = 1; i <= c; i++)
	{
		for (int j = i - LOWBIT(i) + 1; j <= i; j++)
		{
			T[i] += D[j];
		}
	}
}

// Return the sum of 1..k.
int get_sum(int k)
{
	int res = 0;
	while (k > 0)
	{
		res += T[k];
		k -= LOWBIT(k);
	}
	return res;
}

// D[a] += x and update the tree.
void add_one(int a, int x)
{
	while (a <= n)
	{
		T[a] = (T[a] + x) % MOD;
		a += LOWBIT(a);
	}
}

int main()
{
	// e.g. CodeVS - 3900.
	
	for (int i = 1; i <= 1024; i++)
	{
		D[i] = 1;
	}
	build_tree(1024);
	
	int m;
	scanf("%d", &m);
	
	for (int i = 0; i < m; i++)
	{
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		if (a == 1)
		{
			int pre = D[b];
			D[b] = D[b] * c % MOD;
			add_one(b, D[b] - pre + MOD);
		}
		else
		{
			printf("%d\n", ((get_sum(c) - get_sum(b - 1)) % MOD + MOD) % MOD);
		}
	}
	
	return 0;
}
