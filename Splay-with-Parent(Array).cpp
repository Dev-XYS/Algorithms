#include <cstdio>

#define NIL 0
#define ELEMENT_COUNT 100000

using namespace std;

int ch[ELEMENT_COUNT][2], fa[ELEMENT_COUNT], key[ELEMENT_COUNT], size[ELEMENT_COUNT], use = 0, root;

inline int which(int u)
{
	return ch[fa[u]][0] == u ? 0 : 1;
}

inline void update(int u)
{
	size[u] = size[ch[u][0]] + size[ch[u][1]] + 1;
}

void rotate(int u)
{
	int p = fa[u];
	int q = fa[p];
	int uk = which(u), pk = which(p);
	int c = ch[u][uk ^ 1];
	fa[c] = p;
	fa[u] = q;
	fa[p] = u;
	ch[p][uk] = ch[u][uk ^ 1];
	ch[u][uk ^ 1] = p;
	ch[q][pk] = u;
	update(p);
	update(u);
}

void splay(int u, int tar)
{
	while (fa[u] != tar)
	{
		if (fa[fa[u]] != tar)
		{
			if (which(u) == which(fa[u])) rotate(fa[u]);
			else rotate(u);
		}
		rotate(u);
	}
	if (tar == 0) root = u;
}

int cmp(int ikey, int ukey)
{
	return ikey < ukey ? 0 : 1;
}

void insert(int ikey)
{
	if (root == NIL) root = ++use, ch[use][0] = ch[use][1] = fa[use] = NIL, key[use] = ikey;
	else
	{
		int u = root;
		while (key[u] != ikey)
		{
			int k = cmp(ikey, key[u]);
			if (k == -1) break;
			if (ch[u][k] == NIL) ch[u][k] = ++use, fa[use] = u, key[use] = ikey;
			u = ch[u][k];
		}
		splay(u, 0);
	}
}

int find(int fkey)
{
	int u = root;
	while (u != NIL)
	{
		if (key[u] == fkey) return 1;
		else u = ch[u][cmp(fkey, key[u])];
	}
	return 0;
}

int main()
{
	int op, x;
	while (true)
	{
		scanf("%d%d", &op, &x);
		if (op == 1)
		{
			insert(x);
		}
		else if (op == 2)
		{
			splay(x, 0);
		}
		else if (op == 3)
		{
			printf("find result = %d\n", find(x));
		}
		else if (op == 0)
		{
			break;
		}
		else
		{
			printf("No such command!\n");
		}
	}
	return 0;
}
