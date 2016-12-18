#include <cstdio>
#include <cstdlib>

#define NIL 0
#define EDITION_COUNT 100000

using namespace std;

struct node
{
	node *ch[2];
	int key, pr;
	node(int _key = 0, int _pr = 0) : key(_key), pr(_pr) { }
}*root[EDITION_COUNT];

int hs = 0;

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

void insert(node *&u, node *prev, int key, int pr)
{
	if (prev == NIL)
	{
		u = new node(key, pr);
		return;
	}
	u = new node(prev->key, prev->pr);
	int k = cmp(key, prev->key);
	u->ch[k ^ 1] = prev->ch[k ^ 1];
	if (k == -1)
	{
		u->ch[k] = prev->ch[k];
		return;
	}
	insert(u->ch[k], prev->ch[k], key, pr);
	if (u->ch[k]->pr > u->pr)
	{
		rotate(u, k);
	}
}

int find(node *&u, int key)
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
	int in, edition, key;
	while (true)
	{
		scanf("%d", &in);
		if (in == 1)
		{
			scanf("%d", &key);
			insert(root[hs + 1], root[hs], key, rand());
			hs++;
		}
		else if (in == 2)
		{
			scanf("%d%d", &edition, &key);
			printf("%d\n", find(root[edition], key));
		}
		else if (in == 3)
		{
			printf("Current edition : %d\n", hs);
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
