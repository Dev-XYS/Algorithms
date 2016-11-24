#include <cstdio>

using namespace std;

bool check(int x)
{
	for (int i = 2; i * i <= x; i++)
	{
		if (x % i == 0)
		{
			return false;
		}
	}
	return true;
}

int main()
{
	int n;
	while (scanf("%d", &n) > 0)
	{
		printf("%s\n", check(n) == true ? "YES" : "NO");
	}
	return 0;
}
