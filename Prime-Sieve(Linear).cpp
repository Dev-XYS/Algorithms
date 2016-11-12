#include <cstdio>
#include <cstring>

#define MAX 100

using namespace std;

bool isprime[MAX + 1];
int prime[MAX], cnt;

int main()
{
	memset(isprime, true, sizeof(isprime));
	for (int i = 2; i <= MAX; i++)
	{
		if (isprime[i] == true)
		{
			prime[cnt++] = i;
		}
		for (int j = 0; j < cnt && i * prime[j] <= MAX; j++)
		{
			isprime[i * prime[j]] = false;
			if (i % prime[j] == 0)
			{
				break;
			}
		}
	}
	for (int i = 0; i < cnt; i++)
	{
		printf("%d\n", prime[i]);
	}
	return 0;
}
