#include <cstdio>
#include <cstring>
#include <algorithm>

#define NIL 0

using namespace std;

struct data
{
	char id[100];
	int pr;
}d[50010];

int n, lch[50010], rch[50010], S[50010], sp;

inline void parse(char *buf, char *str, int *num)
{
	for (int i = 0; ; i++)
	{
		if (buf[i] == '/')
		{
			buf[i] = ' ';
			break;
		}
	}
	sscanf(buf, "%s %d", str, num);
}

void print_tree(int rt)
{
	if (rt != 0)
	{
		printf("(");
		print_tree(lch[rt]);
		printf("%s/%d", d[rt].id, d[rt].pr);
		print_tree(rch[rt]);
		printf(")");
	}
}

inline bool _data_cmp_(const data &x, const data &y)
{
	return strcmp(x.id, y.id) < 0;
}

int main()
{
	char temp[1000];
	while (true)
	{
		scanf("%d", &n);
		if (n == 0)
		{
			break;
		}
		for (int i = 1; i <= n; i++)
		{
			scanf("%s", temp);
			parse(temp, d[i].id, &d[i].pr);
		}
		sort(d + 1, d + n + 1, _data_cmp_);
		sp = 0;
		for (int i = 1; i <= n; i++)
		{
			lch[i] = rch[i] = NIL;
			S[sp] = 0;
			while (sp > 0 && d[i].pr > d[S[sp - 1]].pr) sp--;
			if (sp > 0)
			{
				rch[S[sp - 1]] = i;
			}
			lch[i] = S[sp];
			S[sp++] = i;
		}
		print_tree(S[0]);
		printf("\n");
	}
	return 0;
}
