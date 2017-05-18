// Algorithm: Fibonacci Heap

#include <cstdio>
#include <cstring>
#include <algorithm>

#define NIL 0
#define MAX_HEAP_SIZE 100010

using namespace std;

class FibonacciHeap
{
private:
	struct node
	{
		node *child, *parent, *left, *right;
		int key, degree;
		bool mark;
		node(int _key) : child(NIL), parent(NIL), left(NIL), right(NIL), key(_key), degree(0), mark(false) { }
	};

	node *min;
	size_t heap_size;

	void _M_insert_to(node *v, node *u);
	void _M_insert_to_root_list(node *u);
	void _M_remove_from_root_list(node *u);
	void _M_link(node *v, node *u);
	void _M_consolidate();
	
public:
	FibonacciHeap();
	void insert(int key);
	int extract_min();
};

void FibonacciHeap::_M_insert_to(node *v, node *u)
{
	v->right = u->right;
	v->left = u;
	u->right->left = v;
	u->right = v;
}

void FibonacciHeap::_M_insert_to_root_list(node *u)
{
	_M_insert_to(u, min);
}

void FibonacciHeap::_M_remove_from_root_list(node *u)
{
	u->left->right = u->right;
	u->right->left = u->left;
}

void FibonacciHeap::_M_link(node *v, node *u)
{
	_M_remove_from_root_list(v);
	if (u->child == NIL)
	{
		u->child = v;
		v->parent = u;
		v->left = v->right = v;
	}
	else
	{
		_M_insert_to(v, u->child);
		v->parent = u;
	}
}

void FibonacciHeap::_M_consolidate()
{
	static node *root_list[MAX_HEAP_SIZE];
	node *first = min;
	node *u = first;
	int cnt = 0;
	do
	{
		root_list[cnt++] = u;
		u = u->right;
	} while (u != first);
	node *list[50];
	memset(list, 0, sizeof(list));
	for (int i = 0; i < cnt; i++)
	{
		node *x = root_list[i];
		while (list[x->degree] != NIL)
		{
			node *y = list[x->degree];
			if (x->key > y->key) swap(x, y);
			_M_link(y, x);
			list[x->degree++] = NIL;
		}
		list[x->degree] = x;
	}
	min = NIL;
	for (int i = 0; i < 50; i++)
	{
		if (list[i] != NIL)
		{
			if (min == NIL)
			{
				min = list[i];
				list[i]->left = list[i]->right = list[i];
			}
			else
			{
				_M_insert_to_root_list(list[i]);
				if (list[i]->key < min->key) min = list[i];
			}
		}
	}
}

FibonacciHeap::FibonacciHeap() : min(NIL), heap_size(0) { }

void FibonacciHeap::insert(int key)
{
	if (min == NIL)
	{
		min = new node(key);
		min->left = min->right = min;
	}
	else
	{
		node *u = new node(key);
		_M_insert_to_root_list(u);
		if (key < min->key) min = u;
	}
	heap_size++;
}

int FibonacciHeap::extract_min()
{
	int res = min->key;
	if (min != NIL)
	{
		if (heap_size == 1)
		{
			min = NIL;
		}
		else
		{
			if (min->child != NIL)
			{
				static node *child_list[MAX_HEAP_SIZE];
				node *first = min->child;
				node *u = first;
				int cnt = 0;
				do
				{
					child_list[cnt++] = u;
					u = u->right;
				} while (u != first);
				for (int i = 0; i < cnt; i++)
				{
					_M_insert_to_root_list(child_list[i]);
				}
			}
			_M_remove_from_root_list(min);
			min = min->right;
			_M_consolidate();
		}
	}
	heap_size--;
	return res;
}

int main()
{
	FibonacciHeap H;
	char op[10];
	int x;
	while (true)
	{
		scanf("%s", op);
		if (strcmp(op, "push") == 0)
		{
			scanf("%d", &x);
			H.insert(x);
		}
		else if (strcmp(op, "pop") == 0)
		{
			printf("%d\n", H.extract_min());
		}
		else
		{
			printf("Command not found.\n");
		}
	}
	return 0;
}
