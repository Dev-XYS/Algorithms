#include <cstdio>

using namespace std;

int gcd(int x, int y)
{
	return x % y == 0 ? y : gcd(y, x % y);
}

int main()
{
	int a, b;
	while (true)
	{
		scanf("%d%d", &a, &b);
		printf("%d\n", gcd(a, b));
	}
	
	return 0;
}
