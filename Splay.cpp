#include <cstdio>

#define NIL 0

using namespace std;

struct node
{
	int key, value;
	node *ch[2];
	node(int _key = 0, int _value = 0) : key(_key), value(_value) { ch[0] = ch[1] = NIL; }
}*root;

void init_splay()
{
	root = new node();
}

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
		if (u->ch[0] == NIL)
		{
			u->ch[0] = new node(key, value);
		}
		else
		{
			if (key < u->ch[0]->key)
			{
				insert(u->ch[0]->ch[0], key, value);
				rotate(u->ch[0], 0);
			}
			else if (key > u->ch[0]->key)
			{
				insert(u->ch[0]->ch[1], key, value);
				rotate(u->ch[0], 1);
			}
		}
		rotate(u, 0);
	}
	else if (key > u->key)
	{
		if (u->ch[1] == NIL)
		{
			u->ch[1] = new node(key, value);
		}
		else
		{
			if (key < u->ch[1]->key)
			{
				insert(u->ch[1]->ch[0], key, value);
				rotate(u->ch[1], 0);
			}
			else if (key > u->ch[1]->key)
			{
				insert(u->ch[1]->ch[1], key, value);
				rotate(u->ch[1], 1);
			}
		}
		rotate(u, 1);
	}
}

int find(node *&u, int key)
{
	int res;
	if (u == NIL)
	{
		return -1;
	}
	if (u->key == key)
	{
		res = u->value;
	}
	if (key < u->key)
	{
		if (u->ch[0] == NIL)
		{
			return -1;
		}
		if (u->ch[0]->key == key)
		{
			res = u->ch[0]->value;
		}
		if (key < u->ch[0]->key)
		{
			res = find(u->ch[0]->ch[0], key);
			if (u->ch[0]->ch[0] != NIL)
			{
				rotate(u->ch[0], 0);
			}
		}
		else if (key > u->ch[0]->key);
		{
			res = find(u->ch[0]->ch[1], key);
			if (u->ch[0]->ch[1] != NIL)
			{
				rotate(u->ch[0], 1);
			}
		}
		rotate(u, 0);
	}
	else if (key > u->key)
	{
		if (u->ch[1] == NIL)
		{
			return -1;
		}
		if (u->ch[1]->key == key)
		{
			res = u->ch[1]->value;
		}
		if (key < u->ch[1]->key)
		{
			res = find(u->ch[1]->ch[0], key);
			if (u->ch[1]->ch[0] != NIL)
			{
				rotate(u->ch[1], 0);
			}
		}
		else if (key > u->ch[1]->key)
		{
			res = find(u->ch[1]->ch[1], key);
			if (u->ch[1]->ch[1] != NIL)
			{
				rotate(u->ch[1], 1);
			}
		}
		rotate(u, 1);
	}
	return res;
}

void DFS(node *u)
{
	printf("node : key = %d, value = %d\n", u->key, u->value);
	if (u->ch[0] != NIL)
	{
		printf("left child:\n");
		DFS(u->ch[0]);
	}
	if (u->ch[1] != NIL)
	{
		printf("right child:\n");
		DFS(u->ch[1]);
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
		else if (in == 4)
		{
			DFS(root);
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
