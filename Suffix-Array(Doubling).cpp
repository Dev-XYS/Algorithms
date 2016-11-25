#include <cstdio>
#include <cstring>

#define STRING_LENGTH 100000

using namespace std;

struct sortinfo
{
	int x, y, ord;
};

int l;
char s[STRING_LENGTH];
int rank[STRING_LENGTH * 2], sa[STRING_LENGTH];

inline bool operator == (const sortinfo &x, const sortinfo &y)
{
	return x.x == y.x && x.y == y.y;
}

void radix_sort(sortinfo *d)
{
	static sortinfo _d[STRING_LENGTH], res[STRING_LENGTH];
	static int c[STRING_LENGTH];
	memset(c, 0, sizeof(c));
	for (int i = 0; i < l; i++)
	{
		c[d[i].y]++;
	}
	for (int i = 1; i <= l; i++)
	{
		c[i] += c[i - 1];
	}
	for (int i = l - 1; i >= 0; i--)
	{
		_d[--c[d[i].y]] = d[i];
	}
	memset(c, 0, sizeof(c));
	for (int i = 0; i < l; i++)
	{
		c[_d[i].x]++;
	}
	for (int i = 1; i <= l; i++)
	{
		c[i] += c[i - 1];
	}
	for (int i = l - 1; i >= 0; i--)
	{
		res[--c[_d[i].x]] = _d[i];
	}
	for (int i = 0; i < l; i++)
	{
		d[i] = res[i];
	}
}

void init_rank()
{
	static int c[256];
	static sortinfo d[STRING_LENGTH];
	int x = 1;
	for (int i = 0; i < l; i++)
	{
		c[(int)s[i]] = 1;
	}
	for (int i = 0; i < 256; i++)
	{
		if (c[i] == 1)
		{
			c[i] = x++;
		}
	}
	for (int i = 0; i < l; i++)
	{
		rank[i] = c[(int)s[i]];
	}
	for (int k = 1; k < l; k <<= 1)
	{
		for (int i = 0; i < l; i++)
		{
			d[i].x = rank[i];
			d[i].y = rank[i + k];
			d[i].ord = i;
		}
		radix_sort(d);
		x = 1;
		rank[d[0].ord] = 1;
		for (int i = 1; i < l; i++)
		{
			rank[d[i].ord] = (d[i] == d[i - 1] ? x : ++x);
		}
	}
}

void rank_to_sa()
{
	for (int i = 0; i < l; i++)
	{
		sa[rank[i] - 1] = i + 1;
	}
}

int main()
{
	scanf("%d%s", &l, s);
	init_rank();
	rank_to_sa();
	for (int i = 0; i < l; i++)
	{
		printf("%d\n", sa[i]);
	}
	return 0;
}
