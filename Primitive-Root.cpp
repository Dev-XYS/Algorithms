#include <cstdio>

typedef long long ll;

using namespace std;

ll p;

ll qpow(ll x, ll y)
{
	if (y == 1) return x;
	ll t = qpow(x, y >> 1);
	t = t * t % p;
	if ((y & 1) == 0) return t;
	return t * x % p;
}

int main()
{
	ll x;
	while (true)
	{
		scanf("%lld", &p);
		for (ll k = 2; ; k++)
		{
			x = p - 1;
			for (ll i = 2; i * i <= x; i++)
			{
				if (x % i == 0)
				{
					if (qpow(k, (p - 1) / i) == 1) goto NEXT;
					while (x % i == 0) x /= i;
				}
			}
			if (x != 1)
			{
				if (qpow(k, (p - 1) / x) == 1) goto NEXT;
			}
			printf("%lld\n", k);
			break;
		NEXT:;
		}
	}
	return 0;
}
