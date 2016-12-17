#include <cstdio>
#include <cstdlib>

#define NIL 0

using namespace std;

struct node
{
	node *ch[2];
	int key, pr;
	node(int _key = 0, int _pr = 0) : key(_key), pr(_pr) { ch[0] = ch[1] = NIL; }
}*root;

void rotate(node *&u, int dir)
{
	node *o = u->ch[dir];
	u->ch[dir] = o->ch[dir ^ 1];
	o->ch[dir ^ 1] = u;
	u = o;
}

int cmp(int ikey, int ukey)
{
	if (ikey == ukey)
		return -1;
	return ikey < ukey ? 0 : 1;
}

void insert(node *&u, int key, int pr)
{
	if (u == NIL)
	{
		u = new node(key, pr);
	}
	else
	{
		int k = cmp(key, u->key);
		if (k == -1)
		{
			return;
		}
		insert(u->ch[k], key, pr);
		if (u->ch[k]->pr > u->pr)
		{
			rotate(u, k);
		}
	}
}

int find(node *u, int key)
{
	if (u == NIL)
	{
		return -1;
	}
	else
	{
		int k = cmp(key, u->key);
		if (k == -1)
		{
			return 1;
		}
		return find(u->ch[k], key);
	}
}

int main()
{
	int in, key;
	while (true)
	{
		scanf("%d", &in);
		if (in == 1)
		{
			scanf("%d", &key);
			insert(root, key, rand());
		}
		else if (in == 2)
		{
			scanf("%d", &key);
			printf("%d\n", find(root, key));
		}
		else if (in == 0)
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
