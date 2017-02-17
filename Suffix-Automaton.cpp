#include <cstdio>
#include <cstring>

#define NIL 0
#define ALPHABET_SIZE 26

using namespace std;

struct node
{
	node *next[ALPHABET_SIZE], *parent;
	int len;
	node(int _len = 0) : len(_len) { memset(next, 0, sizeof(next)), parent = NIL; }
}*root, *last;

char s[100000];
int len;

void init()
{
	root = new node(0);
	last = root;
}

void extend(int x)
{
	node *p = last;
	node *np = new node(p->len + 1);
	while (p != NIL && p->next[x] == NIL)
	{
		p->next[x] = np;
		p = p->parent;
	}
	if (p == NIL)
	{
		np->parent = root;
	}
	else
	{
		node *q = p->next[x];
		if (q->len == p->len + 1)
		{
			np->parent = q;
		}
		else
		{
			node *nq = new node;
			*nq = *q;
			nq->len = p->len + 1;
			q->parent = np->parent = nq;
			while (p != NIL && p->next[x] == q)
			{
				p->next[x] = nq;
				p = p->parent;
			}
		}
	}
	last = np;
}

int main()
{
	scanf("%s", s);
	len = strlen(s);
	init();
	for (int i = 0; i < len; i++)
	{
		extend(s[i] - 'a');
	}
	return 0;
}
