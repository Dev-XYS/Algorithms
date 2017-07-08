#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <utility>

using namespace std;

struct node
{
	node *lch, *rch;
	int key, pr;
	node(int _key);
}*root, *nil;

node::node(int _key = 0) : lch(nil), rch(nil), key(_key), pr(rand()) { }

void init()
{
	nil = new node;
	root = nil;
}

pair<node*, node*> split(node *u, int x)
{
	if (u == nil)
	{
		return make_pair(nil, nil);
	}
	if (x <= u->key)
	{
		pair<node*, node*> res = split(u->lch, x);
		u->lch = res.second;
		return make_pair(res.first, u);
	}
	else
	{
		pair<node*, node*> res = split(u->rch, x);
		u->rch = res.first;
		return make_pair(u, res.second);
	}
}

node* merge(node *u, node *v)
{
	if (u == nil)
	{
		return v;
	}
	else if (v == nil)
	{
		return u;
	}
	if (u->pr > v->pr)
	{
		u->rch = merge(u->rch, v);
		return u;
	}
	else
	{
		v->lch = merge(u, v->lch);
		return v;
	}
}

int find(node *u, int x)
{
	if (u == nil)
	{
		return 0;
	}
	if (u->key == x)
	{
		return 1;
	}
	if (x < u->key)
	{
		return find(u->lch, x);
	}
	else
	{
		return find(u->rch, x);
	}
}

int find(int x)
{
	return find(root, x);
}

void insert(int x)
{
	if (find(root, x) == 1)
	{
		return;
	}
	node *u = new node(x);
	pair<node*, node*> rts = split(root, x);
	rts.first = merge(rts.first, u);
	root = merge(rts.first, rts.second);
}

void print_tree(node *u)
{
	if (u != nil)
	{
		printf("(");
		print_tree(u->lch);
		printf("%d", u->key);
		print_tree(u->rch);
		printf(")");
	}
}

int main()
{
	char op[10];
	int x;
	init();
	while (true)
	{
		scanf("%s", op);
		if (strcmp(op, "insert") == 0)
		{
			scanf("%d", &x);
			insert(x);
		}
		else if (strcmp(op, "find") == 0)
		{
			scanf("%d", &x);
			printf("%d\n", find(x));
		}
		else if (strcmp(op, "exit") == 0)
		{
			break;
		}
		else
		{
			printf("Command not found.\n");
		}
	}
	return 0;
}
