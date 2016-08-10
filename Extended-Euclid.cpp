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

int main()
{
	int a, b, x, y;
	while (true)
	{
		scanf("%d%d", &a, &b);
		int gcd = extended_gcd(a, b, x, y);
		printf("gcd = %d, x = %d, y = %d.\n", extended_gcd(a, b, x, y), x, y);
	}
	
	return 0;
}
