#include <cstdio>

using namespace std;

long long Euler(long long x)
{
	long long prev = 0, res = x;
	for (long long i = 2; i * i <= x; i++)
	{
		if (x % i == 0)
		{
			if (i != prev)
			{
				res = res / i * (i - 1);
				prev = i;
			}
			x /= i;
			i = 1;
		}
	}
	if (x != 1 && x != prev)
	{
		res = res / x * (x - 1);
	}
	return (long long)res;
}

int main()
{
	while (true)
	{
		long long x;
		scanf("%lld", &x);
		if (x == 0)
		{
			break;
		}
		printf("%lld\n", Euler(x));
	}
	return 0;
}
