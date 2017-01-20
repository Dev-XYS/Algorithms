#include <cstdio>

using namespace std;

struct node
{
	node *lch, *rch;
	int key, dis;
	node(int _key = 0, int _dis = 0);
}*root, *nil;

node::node(int _key, int _dis) : key(_key), dis(_dis)
{
	lch = rch = nil;
}

void init()
{
	nil = new node(0, -1);
	root = nil;
}

inline void swap(node *&u, node *&v)
{
	node *temp = u;
	u = v;
	v = temp;
}

void merge(node *&u, node *&v)
{
	if (u == nil)
	{
		u = v;
		return;
	}
	if (v == nil) return;
	if (u->key > v->key) swap(u, v);
	merge(u->rch, v);
	if (u->lch->dis < u->rch->dis) swap(u->lch, u->rch);
	u->dis = u->rch->dis + 1;
}

int extract_min()
{
	int res = root->key;
	merge(root->lch, root->rch);
	node *del = root;
	root = root->lch;
	delete del;
	return res;
}

int main()
{
	int op, x;
	init();
	while (true)
	{
		scanf("%d", &op);
		if (op == 1)
		{
			scanf("%d", &x);
			node *o = new node(x, 0);
			merge(root, o);
		}
		else if (op == 2)
		{
			printf("%d\n", extract_min());
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
