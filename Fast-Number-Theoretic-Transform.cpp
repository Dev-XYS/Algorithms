#include <cstdio>
#include <cstring>

#define MOD 998244353
#define ROOT 3

typedef long long ll;

using namespace std;

int n, n0, n1, k;
ll a0[500000], a1[500000];

inline void swap(ll &x, ll &y)
{
	ll temp = x;
	x = y;
	y = temp;
}

ll qpow(ll x, int y)
{
	if (y == 1) return x;
	ll t = qpow(x, y >> 1);
	t = t * t % MOD;
	if ((y & 1) == 0) return t;
	else return t * x % MOD;
}

void pre(ll *a)
{
	static ll temp[500000];
	memcpy(temp, a, sizeof(temp));
	for (int i = 0; i < n; i++)
	{
		int x = 0;
		for (int p = 0; p < k; p++)
		{
			if ((i & (1 << p)) != 0)
			{
				x += (1 << (k - p - 1));
			}
		}
		a[i] = temp[x];
	}
}

void dft(ll *a, int rev)
{
	ll _g = rev == 1 ? ROOT : qpow(ROOT, MOD - 2);
	for (int i = 2; i <= n; i <<= 1)
	{
		ll gn = qpow(_g, (MOD - 1) / i);
		for (int p = 0; p < n; p += i)
		{
			ll g = 1LL;
			for (int q = p; q < p + (i >> 1); q++)
			{
				ll temp = a[q];
				a[q] = (a[q] + g * a[q + (i >> 1)]) % MOD;
				a[q + (i >> 1)] = (temp - g * a[q + (i >> 1)]) % MOD;
				g = g * gn % MOD;
			}
		}
	}
}

inline ll read()
{
	char c;
	do
	{
		c = getchar();
	} while (c < '0' || c > '9');
	return (ll)(c - '0');
}

int main()
{
	scanf("%d%d", &n0, &n1);
	for (int i = 0; i <= n0; i++)
	{
		a0[i] = read();
	}
	for (int i = 0; i <= n1; i++)
	{
		a1[i] = read();
	}
	n = n0 + n1;
	while (n > 0)
	{
		k++;
		n >>= 1;
	}
	n = 1 << k;
	pre(a0);
	pre(a1);
	dft(a0, 1);
	dft(a1, 1);
	for (int i = 0; i < n; i++)
	{
		a0[i] = a0[i] * a1[i] % MOD;
	}
	pre(a0);
	dft(a0, -1);
	ll inv = qpow(n, MOD - 2);
	for (int i = 0; i <= n0 + n1; i++)
	{
		printf("%lld ", (a0[i] * inv % MOD + MOD) % MOD);
	}
	return 0;
}
