#include <cstdio>

using namespace std;

int extended_gcd(int a, int b, int &x, int &y)
{
	if (b == 0)
	{
		x = 1;
		y = 0;
		return a;
	}
	int _gcd = extended_gcd(b, a % b, x, y);
	int temp = x;
	x = y;
	y = temp - (a / b) * y;
	return _gcd;
}

int inverse(int a, int p)
{
	int x, y;
	extended_gcd(a, p, x, y);
	return (x % p + p) % p;
}

int main()
{
	int a, p;
	
	while (true)
	{
		scanf("%d%d", &a, &p);
		printf("%d\n", inverse(a, p));
	}
	
	return 0;
}
