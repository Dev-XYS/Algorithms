#include <cstdio>

#define MAX_N 10000000

typedef long long ll;

using namespace std;

// p must be a prime greater than n.
ll n, fac_inv[MAX_N], p;

ll qpow(ll x, ll y)
{
	if (y == 1) return x;
	ll t = qpow(x, y >> 1);
	t = t * t % p;
	if ((y & 1) == 0) return t;
	else return t * x % p;
}

ll fac(ll x)
{
	ll res = 1;
	for (int i = 2; i <= x; i++)
	{
		res = res * i % p;
	}
	return res;
}

void fac_inv_sieve()
{
	fac_inv[n] = qpow(fac(n), p - 2);
	for (ll i = n - 1; i >= 1; i--)
	{
		fac_inv[i] = fac_inv[i + 1] * (i + 1) % p;
	}
}

int main()
{
	scanf("%lld%lld", &n, &p);
	fac_inv_sieve();
	for (int i = 1; i <= n; i++)
	{
		printf("inv(fac(%d)) mod %lld = %lld\n", i, p, fac_inv[i]);
	}
	return 0;
}
