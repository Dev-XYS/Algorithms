// Problem Name: [HNOI2010] 弹飞绵羊 Bounce

#include <cstdio>

#define NIL 0
#define NODE_COUNT 200010

using namespace std;

class link_cut_tree
{
private:
	int ch[NODE_COUNT][2], fa[NODE_COUNT], size[NODE_COUNT], tf[NODE_COUNT];

public:
	link_cut_tree();

	int get_size(int u);
	void set_tf(int u, int uf);

	int which(int u);
	void update(int u);
	void rotate(int u);
	void splay(int u, int tar);
	int find_top(int u);

	void access(int u);
	void link(int u, int v);
	void cut(int u);

	void print_fa();
};

int n, m;

link_cut_tree::link_cut_tree()
{
	for (int i = 1; i <= n + 1; i++)
	{
		size[i] = 1;
	}
}

int link_cut_tree::get_size(int u)
{
	return size[u];
}

void link_cut_tree::set_tf(int u, int uf)
{
	tf[u] = uf;
}

int link_cut_tree::which(int u)
{
	return ch[fa[u]][0] == u ? 0 : 1;
}

void link_cut_tree::update(int u)
{
	size[u] = size[ch[u][0]] + size[ch[u][1]] + 1;
}

void link_cut_tree::rotate(int u)
{
	int uk = which(u);
	int p = fa[u];
	int q = fa[p];
	int c = ch[u][uk ^ 1];
	int pk = which(p);
	fa[c] = p;
	fa[u] = q;
	fa[p] = u;
	ch[p][uk] = c;
	ch[u][uk ^ 1] = p;
	ch[q][pk] = u;
	update(p);
	update(u);
}

void link_cut_tree::splay(int u, int tar)
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
}

int link_cut_tree::find_top(int u)
{
	int tar = fa[u];
	while (ch[u][0] != NIL)
	{
		u = ch[u][0];
	}
	splay(u, tar);
	return u;
}

void link_cut_tree::access(int u)
{
	int top = NIL;
	do
	{
		splay(u, NIL);
		size[u] -= size[ch[u][1]];
		fa[ch[u][1]] = NIL;
		ch[u][1] = top;
		fa[top] = u;
		update(u);
		top = find_top(u);
		u = tf[top];
	} while (u != NIL);
}

void link_cut_tree::link(int u, int v)
{
	tf[v] = u;
}

void link_cut_tree::cut(int u)
{
	access(tf[u]);
	tf[u] = NIL;
}

void link_cut_tree::print_fa()
{
	for (int i = 1; i <= n + 1; i++)
	{
		printf("fa[%d] = %d\n", i, fa[i]);
	}
}

int main()
{
	int op, k, x;
	scanf("%d", &n);
	static link_cut_tree lct;
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &x);
		lct.set_tf(i, i + x > n ? n + 1 : i + x);
	}
	scanf("%d", &m);
	while (m--)
	{
		scanf("%d", &op);
		if (op == 1)
		{
			scanf("%d", &k);
			lct.access(k + 1);
			printf("%d\n", lct.get_size(n + 1) - 1);
		}
		else
		{
			scanf("%d%d", &k, &x);
			lct.cut(k + 1);
			lct.link(k + x > n ? n + 1 : k + 1 + x, k + 1);
		}
	}
	return 0;
}
