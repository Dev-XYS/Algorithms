#include <cstdio>

#define TREE_SIZE 100000

using namespace std;

struct node
{
	int lch, rch, key, satellite;
}T[TREE_SIZE];

int tc = 1;

int _satellite;
void insert(int rt, int x)
{
	if (T[rt].lch == 0 && T[rt].rch == 0)
	{
		T[rt].lch = tc++;
		T[rt].rch = tc++;
		T[rt].key = x;
		T[rt].satellite = _satellite;
	}
	else
	{
		if (x < T[rt].key)
		{
			insert(T[rt].lch, x);
		}
		else
		{
			insert(T[rt].rch, x);
		}
	}
}

int query(int rt, int key)
{
	if (T[rt].key == key)
	{
		return T[rt].satellite;
	}
	else
	{
		return key < T[rt].key ? query(T[rt].lch, key) : query(T[rt].rch, key);
	}
}

int main()
{
	int ord, key, sat;
	while (true)
	{
		scanf("%d", &ord);
		if (ord == 1)
		{
			scanf("%d%d", &key, &sat);
			_satellite = sat;
			insert(0, key);
		}
		else if (ord == 2)
		{
			scanf("%d", &key);
			printf("%d\n", query(0, key));
		}
	}
	return 0;
}
