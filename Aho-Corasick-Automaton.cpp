#include <cstdio>
#include <cstring>
#include <queue>

#define NIL 0
#define ALPHABET_SIZE 26
#define STRING_LENGTH 100000
#define PATTERN_COUNT 1000
#define PATTERN_LENGTH 1000
#define NODE_COUNT 100000

using namespace std;

struct node
{
	int id;
	node *next[ALPHABET_SIZE], *fail, *last;
	node();
}*root;

int idc = 0;
char s[PATTERN_COUNT][PATTERN_LENGTH], t[STRING_LENGTH];
int len[PATTERN_COUNT];

node::node() : id(0), fail(NIL), last(NIL)
{
	memset(next, 0, sizeof(next));
}

void init_trie()
{
	root = new node;
}

void insert(char *s)
{
	int l = strlen(s), x;
	node *cur = root;
	for (int i = 0; i < l; i++)
	{
		x = s[i] - 'a';
		if (cur->next[x] == NIL)
		{
			cur->next[x] = new node;
		}
		cur = cur->next[x];
	}
	cur->id = ++idc;
}

void init_fail()
{
	queue<node*> Q;
	root->fail = root;
	root->last = root;
	for (int i = 0; i < ALPHABET_SIZE; i++)
	{
		if (root->next[i] != NIL)
		{
			root->next[i]->fail = root;
			root->next[i]->last = root;
			Q.push(root->next[i]);
		}
		else
		{
			root->next[i] = root;
		}
	}
	while (!Q.empty())
	{
		node *cur = Q.front();
		Q.pop();
		for (int i = 0; i < ALPHABET_SIZE; i++)
		{
			if (cur->next[i] != NIL)
			{
				cur->next[i]->fail = cur->fail->next[i];
				cur->next[i]->last = cur->next[i]->fail->id > 0 ? cur->next[i]->fail : cur->next[i]->fail->last;
				Q.push(cur->next[i]);
			}
			else
			{
				cur->next[i] = cur->fail->next[i];
			}
		}
	}
}

void print(node *cur, int shift)
{
	while (cur != root)
	{
		printf("matched with shift %2d : %s\n", shift - len[cur->id] + 1, s[cur->id]);
		cur = cur->last;
	}
}

void ac_automation()
{
	int l = strlen(t);
	node *cur = root;
	for (int i = 0; i < l; i++)
	{
		cur = cur->next[t[i] - 'a'];
		if (cur->id > 0)
		{
			print(cur, i);
		}
		else
		{
			print(cur->last, i);
		}
	}
}

int main()
{
	int n;
	scanf("%s", t);
	scanf("%d", &n);
	init_trie();
	for (int i = 1; i <= n; i++)
	{
		scanf("%s", s[i]);
		len[i] = strlen(s[i]);
		insert(s[i]);
	}
	init_fail();
	ac_automation();
	return 0;
}
