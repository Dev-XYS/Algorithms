#include <cstdio>

#define MAX_ELEMENT_COUNT 5010

using namespace std;

int fa[MAX_ELEMENT_COUNT], size[MAX_ELEMENT_COUNT];

int getrt(int v)
{
	if (fa[v] == v)
	{
		return v;
	}
	return (fa[v] = getrt(fa[v]));
}

void merge(int x, int y)
{
	int rx = getrt(x), ry = getrt(y);
	
	if (size[rx] < size[ry])
	{
		fa[rx] = ry;
		size[ry] += size[rx];
	}
	else
	{
		fa[ry] = rx;
		size[rx] += size[ry];
	}
}

void initial(int n)
{
	for (int i = 1; i <= n; i++)
	{
		fa[i] = i;
		size[i] = 1;
	}
}

int main()
{
	// e.g. CodeVS - 1073.
	int n, m, p;
	scanf("%d%d%d", &n, &m, &p);
	
	initial(n);
	
	for (int i = 0; i < m; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		merge(a, b);
	}
	
	for (int i = 0; i < p; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		if (getrt(a) == getrt(b))
		{
			printf("Yes\n");
		}
		else
		{
			printf("No\n");
		}
	}
	
	return 0;
}
