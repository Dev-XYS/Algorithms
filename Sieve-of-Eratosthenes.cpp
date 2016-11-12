#include <cstdio>
#include <cstring>

#define MAX 100

using namespace std;

bool isprime[MAX + 1];

int main()
{
	memset(isprime, true, sizeof(isprime));
	for (int i = 2; i * i <= MAX; i++)
	{
		if (isprime[i] == true)
		{
			for (int j = i * i; j <= MAX; j += i)
			{
				isprime[j] = false;
			}
		}
	}
	for (int i = 2; i < MAX; i++)
	{
		if (isprime[i] == true)
		{
			printf("%d\n", i);
		}
	}
	return 0;
}
