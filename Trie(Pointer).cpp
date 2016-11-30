#include <cstdio>
#include <cstring>

#define NIL 0

using namespace std;

struct node
{
	int info;
	node *next[26];
};

node root;

void insert(char *s)
{
	int l = strlen(s);
	node *cur = &root;
	for (int i = 0; i < l; i++)
	{
		if (cur->next[s[i] - 'a'] == NIL)
		{
			node *o = new node;
			o->info = 0;
			cur->next[s[i] - 'a'] = o;
		}
		cur = cur->next[s[i] - 'a'];
	}
	cur->info++;
}

int find(char *s)
{
	int l = strlen(s);
	node *cur = &root;
	for (int i = 0; i < l; i++)
	{
		if (cur->next[s[i] - 'a'] == NIL)
		{
			return -1;
		}
		else
		{
			cur = cur->next[s[i] - 'a'];
		}
	}
	return cur->info;
}

int main()
{
	int in;
	char str[100];
	while (true)
	{
		scanf("%d", &in);
		if (in == 1)
		{
			scanf("%s", str);
			insert(str);
		}
		else if (in == 2)
		{
			scanf("%s", str);
			printf("%d\n", find(str));
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
