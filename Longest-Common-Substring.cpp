#include <cstdio>
#include <cstring>

#define STRING_LENGTH 300000

using namespace std;

struct sortinfo
{
	int x, y, ord;
};

int l;
char s[STRING_LENGTH], t[STRING_LENGTH / 2];
int rank[STRING_LENGTH * 2], sa[STRING_LENGTH], height[STRING_LENGTH];

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
			rank[d[i].ord] = (d[i].x == d[i - 1].x && d[i].y == d[i - 1].y ? x : ++x);
		}
		if (x == l)
		{
			break;
		}
	}
}

void rank_to_sa()
{
	for (int i = 0; i < l; i++)
	{
		sa[rank[i]] = i;
	}
}

void init_height()
{
	int k = 0;
	for (int i = 0; i < l; i++)
	{
		if (k > 0)
		{
			k--;
		}
		if (rank[i] == l)
		{
			continue;
		}
		for (; s[i + k] == s[sa[rank[i] + 1] + k]; k++) ;
		height[rank[i]] = k;
	}
}

int main()
{
	int l1, l2;
	scanf("%s%s", s, t);
	l1 = strlen(s);
	l2 = strlen(t);
	s[l1] = '#';
	strcat(s, t);
	l = l1 + l2;
	init_rank();
	rank_to_sa();
	init_height();
	int maxlen = 0;
	for (int i = 1; i < l; i++)
	{
		if (height[i] > maxlen && ((sa[i] < l1 && sa[i + 1] > l1) || (sa[i] > l1 && sa[i + 1] < l1)))
		{
			maxlen = height[i];
		}
	}
	printf("%d", maxlen);
	return 0;
}
