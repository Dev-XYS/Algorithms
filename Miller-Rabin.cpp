#include <cstdio>
#include <cstdlib>

#define LOWBIT(x) ((x) & (-(x)))

#define COMPOSITE 0
#define PRIME 1

typedef long long ll;

using namespace std;

ll qpow(ll x, int y, int p)
{
	if (y == 0) return 1;
	ll h = qpow(x * x % p, y >> 1, p);
	if ((y & 1) == 0) return h;
	else return h * x % p;
}

bool witness(int a, int n)
{
	int t = LOWBIT(n - 1);
	int u = n / t;
	ll x = qpow(a, u, n);
	for (int i = 1; i < t; i <<= 1)
	{
		ll r = x * x % (ll)n;
		if (r == 1 && x != 1 && x != n - 1) return true;
		x = r;
	}
	if (x != 1) return true;
	return false;
}

bool Miller_Rabin(int n, int s)
{
	if (n == 2) return PRIME;
	if ((n & 1) == 0) return COMPOSITE;
	while (s--)
	{
		if (witness(rand() % (n - 2) + 2, n) == true) return COMPOSITE;
	}
	return PRIME;
}

int main()
{
	int n;
	while (true)
	{
		scanf("%d", &n);
		printf("%s\n", Miller_Rabin(n, 10) == COMPOSITE ? "COMPOSITE" : "PRIME");
	}
	return 0;
}
