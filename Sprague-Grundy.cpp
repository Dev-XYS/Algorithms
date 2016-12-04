#include <cstdio>
#include <cstring>

using namespace std;

int k, s[100], sg[10001];
bool has[10001];

void init_sg()
{
	sg[0] = 0;
	for (int i = 1; i <= 10000; i++)
	{
		memset(has, false, sizeof(has));
		for (int j = 0; j < k; j++)
		{
			if (i - s[j] >= 0)
			{
				has[sg[i - s[j]]] = true;
			}
		}
		for (int j = 0; ; j++)
		{
			if (has[j] == false)
			{
				sg[i] = j;
				break;
			}
		}
	}
}

int main()
{
	while (true)
	{
		scanf("%d", &k);
		if (k == 0)
		{
			break;
		}
		for (int i = 0; i < k; i++)
		{
			scanf("%d", &s[i]);
		}
		init_sg();
		int t, c, x, res;
		scanf("%d", &t);
		while (t--)
		{
			res = 0;
			scanf("%d", &c);
			while (c--)
			{
				scanf("%d", &x);
				res ^= sg[x];
			}
			if (res == 0)
			{
				printf("L");
			}
			else
			{
				printf("W");
			}
		}
		printf("\n");
	}
	return 0;
}
