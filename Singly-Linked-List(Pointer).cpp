#include <cstdio>

#define NIL 0

using namespace std;

struct node
{
	int id, value;
	node *next;
};

node *head;

void insert(int id, int value)
{
	node *o = new node;
	o->next = head;
	head = o;
	o->id = id;
	o->value = value;
}

int find(int id)
{
	node *cur = head;
	while (cur != NIL)
	{
		if (cur->id == id)
		{
			return cur->value;
		}
		cur = cur->next;
	}
	return -1;
}

bool del(int id)
{
	if (head == NIL)
	{
		return false;
	}
	if (head->id == id)
	{
		node *temp = head;
		head = head->next;
		delete temp;
		return true;
	}
	node *prev = head, *cur = head->next;
	while (cur != NIL)
	{
		if (cur->id == id)
		{
			prev->next = cur->next;
			delete cur;
			return true;
		}
		prev = cur;
		cur = cur->next;
	}
	return false;
}

int main()
{
	int in, id, value;
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
		else if (in == 3)
		{
			scanf("%d", &id);
			printf("%s\n", del(id) == true ? "deleted" : "failed");
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
