#include <cstdio>
#include <cstdlib>

#define NIL 0
#define LAYER_COUNT 20
#define NODE_COUNT 100000

using namespace std;

struct node
{
	int id, value;
	node *next, *lower;
	node();
};

node::node() : next(NIL) { }

node *head[LAYER_COUNT];

void init()
{
	head[0] = new node;
	for (int i = 1; i < LAYER_COUNT; i++)
	{
		head[i] = new node;
		head[i]->lower = head[i - 1];
	}
}

void insert(int id, int value)
{
	int k = 0;
	while ((rand() & 1) == 0)
	{
		k++;
	}
	node *prev = head[k], *cur = head[k], *upper = NIL;
	for (; k >= 0; k--)
	{
		while (cur != NIL && cur->id < id)
		{
			prev = cur;
			cur = cur->next;
		}
		node *o = new node;
		o->next = cur;
		o->id = id;
		o->value = value;
		prev->next = o;
		prev = prev->lower;
		cur = prev;
		if (upper != NIL)
		{
			upper->lower = o;
		}
		upper = o;
	}
}

int find(int id)
{
	node *prev, *cur = head[LAYER_COUNT - 1];
	for (int k = LAYER_COUNT - 1; k >= 0; k--)
	{
		while (cur != NIL && cur->id < id)
		{
			prev = cur;
			cur = cur->next;
		}
		if (cur != NIL && cur->id == id)
		{
			return cur->value;
		}
		else
		{
			prev = prev->lower;
			cur = prev;
		}
	}
	return -1;
}

void debug()
{
	for (int i = 5; i >= 0; i--)
	{
		node *cur = head[i];
		printf("head[%d]", i);
		while (cur != NIL)
		{
			printf(" -> (%d, %d)", cur->id, cur->value);
			cur = cur->next;
		}
		printf("\n");
	}
}

int main()
{
	int in, id, value;
	init();
	while (true)
	{
		scanf("%d", &in);
		if (in == 1)
		{
			scanf("%d%d", &id, &value);
			insert(id, value);
		}
		else if (in == 2)
		{
			scanf("%d", &id);
			printf("%d\n", find(id));
		}
		else if (in == 4)
		{
			debug();
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
