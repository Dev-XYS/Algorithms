#include <cstdio>

using namespace std;

long long m;

// Calcutate a ^ b % m;
long long qpow(long long a, long long b)
{
	if (b == 1)
	{
		return a;
	}
	
	long long mid = qpow(a, b >> 1);
	if ((b & 1) == 0)
	{
		return mid * mid % m;
	}
	else
	{
		return mid * mid % m * a % m;
	}
}

int main()
{
	long long a, b;
	scanf("%lld%lld%lld", &a, &b, &m);
	printf("%lld", qpow(a, b));
	return 0;
}
