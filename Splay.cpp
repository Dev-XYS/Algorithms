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

inline int compare(node *u, int key)
{
	if (key == u->key)
	{
		return -1;
	}
	return key < u->key ? 0 : 1;
}	

void insert(node *&u, int key, int value)
{
	if (u == NIL)
	{
		u = new node(key, value);
		return;
	}
	int k0 = compare(u, key);
	if (k0 == -1)
	{
		return;
	}
	if (u->ch[k0] == NIL)
	{
		u->ch[k0] = new node(key, value);
	}
	else
	{
		int k1 = compare(u->ch[k0], key);
		if (k1 == -1)
		{
			return;
		}
		insert(u->ch[k0]->ch[k1], key, value);
		if (k0 == k1)
		{
			rotate(u, k0);
		}
		else
		{
			rotate(u->ch[k0], k1);
		}
	}
	rotate(u, k0);
}

int find(node *&u, int key)
{
	if (u == NIL)
	{
		return -1;
	}
	int k0 = compare(u, key);
	if (k0 == -1)
	{
		return u->value;
	}
	if (u->ch[k0] == NIL)
	{
		return -1;
	}
	else
	{
		int k1 = compare(u->ch[k0], key), res;
		if (k1 == -1)
		{
			res = u->ch[k0]->value;
			goto END;
		}
		res = find(u->ch[k0]->ch[k1], key);
		if (u->ch[k0]->ch[k1] != NIL)
		{
			if (k0 == k1)
			{
				rotate(u, k0);
			}
			else
			{
				rotate(u->ch[k0], k1);
			}
		}
	END:
		rotate(u, k0);
		return res;
	}
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
