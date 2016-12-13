#include <cstdio>

#define NIL 0

using namespace std;

struct node
{
	int key, value;
	node *ch[2];
	node(int _key = 0, int _value = 0) : key(_key), value(_value) { ch[0] = ch[1] = NIL; }
}*root;

void rotate(node *&u, int dir)
{
	node *o = u->ch[dir];
	u->ch[dir] = o->ch[dir ^ 1];
	o->ch[dir ^ 1] = u;
	u = o;
}

void insert(node *&u, int key, int value)
{
	if (u == NIL)
	{
		u = new node(key, value);
		return;
	}
	if (key < u->key)
	{
		insert(u->ch[0], key, value);
		rotate(u, 0);
	}
	else if (key > u->key)
	{
		insert(u->ch[1], key, value);
		rotate(u, 1);
	}
}

int find(node *&u, int key)
{
	if (u == NIL)
	{
		return -1;
	}
	if (u->key == key)
	{
		return u->value;
	}
	int res;
	if (key < u->key)
	{
		res = find(u->ch[0], key);
		if (u->ch[0] != NIL)
			rotate(u, 0);
	}
	else if (key > u->key)
	{
		res = find(u->ch[1], key);
		if (u->ch[1] != NIL)
			rotate(u, 1);
	}
	return res;
}

int main()
{
	int in, key, value;
	while (true)
	{
		scanf("%d", &in);
		if (in == 1)
		{
			scanf("%d%d", &key, &value);
			insert(root, key, value);
		}
		else if (in == 2)
		{
			scanf("%d", &key);
			printf("%d\n", find(root, key));
		}
		else if (in == 0)
		{
			return 0;
		}
		else
		{
			printf("No such command!\n");
		}
	}
	return 0;
}
