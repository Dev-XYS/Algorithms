#include <cstdio>

using namespace std;

int n, s[10], sp = 0;
bool ins[11];

void DFS()
{
	if (sp == n)
	{
		for (int i = 0; i < sp; i++)
		{
			printf("%d ", s[i]);
		}
		printf("\n");
		return;
	}
	for (int i = 1; i <= n; i++)
	{
		if (ins[i] == false)
		{
			ins[i] = true;
			s[sp++] = i;
			DFS();
			ins[i] = false;
			sp--;
		}
	}
}

int main()
{
	scanf("%d", &n);
	DFS();
	return 0;
}
