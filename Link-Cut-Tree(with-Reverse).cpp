#include <cstdio>
  
#define NIL 0
#define N 10010
  
using namespace std;
  
int n, m;
int ch[N][2], fa[N], tf[N];
bool rev[N];
  
inline void swap(int *x)
{
	int temp = x[0];
	x[0] = x[1];
	x[1] = temp;
}
  
inline int which(int u)
{
	return ch[fa[u]][0] == u ? 0 : 1;
}
  
void rotate(int u)
{
	int p = fa[u];
	int g = fa[p];
	int k1 = which(u), k0 = which(p);
	int c = ch[u][k1 ^ 1];
	fa[c] = p;
	fa[u] = g;
	fa[p] = u;
	ch[g][k0] = u;
	ch[p][k1] = c;
	ch[u][k1 ^ 1] = p;
}
  
void push_down(int u)
{
	if (rev[u] == true)
	{
		swap(ch[u]);
		rev[u] = false;
		rev[ch[u][0]] ^= true, rev[ch[u][1]] ^= true;
	}
}
  
void splay(int u, int tar)
{
	static int path[N];
	int pc = 0;
	while (u != tar)
	{
		path[pc++] = u;
		u = fa[u];
	}
	for (int i = pc - 1; i >= 0; i--)
	{
		push_down(path[i]);
	}
	u = path[0];
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
  
int find_top(int u)
{
	push_down(u);
	while (ch[u][0] != NIL)
	{
		u = ch[u][0];
		push_down(u);
	}
	splay(u, NIL);
	return u;
}
  
int get_root(int u)
{
	while (fa[u] != NIL)
	{
		u = fa[u];
	}
	return u;
}
  
void access(int u)
{
	int c = NIL;
	while (u != NIL)
	{
		splay(u, NIL);
		fa[ch[u][1]] = NIL;
		if (ch[u][1] != NIL) tf[find_top(ch[u][1])] = u;
		ch[u][1] = c;
		fa[c] = u;
		c = find_top(u);
		u = tf[c];
	}
}
  
void change_root(int u)
{
	access(u);
	splay(u, NIL);
	rev[u] = true;
	find_top(u);
	tf[u] = NIL;
}
  
void link(int u, int v)
{
	change_root(v);
	tf[v] = u;
}
  
void cut(int u, int v)
{
	change_root(u);
	access(v);
	splay(u, NIL);
	fa[v] = NIL;
	ch[u][1] = NIL;
	tf[v] = NIL;
}
  
bool query(int u, int v)
{
	change_root(u);
	access(v);
	if (get_root(u) == get_root(v)) return true;
	else return false;
}
  
int main()
{
	char op[10];
	int u, v;
	scanf("%d%d", &n, &m);
	while (m--)
	{
		scanf("%s%d%d", op, &u, &v);
		if (op[0] == 'C')
		{
			link(u, v);
		}
		else if (op[0] == 'D')
		{
			cut(u, v);
		}
		else
		{
			printf("%s\n", query(u, v) == true ? "Yes" : "No");
		}
	}
	return 0;
}
