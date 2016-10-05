#include <cstdio>

#define QUEUE_SIZE 100000

using namespace std;

int Q[QUEUE_SIZE], hp = 0, tp = 0, M[QUEUE_SIZE], mhp = 0, mtp = 0;

void enqueue(int x)
{
	Q[tp++] = x;
	tp %= QUEUE_SIZE;
	
	while (mhp != mtp && x > M[mhp])
	{
		mtp = (mtp + 1) % QUEUE_SIZE;
	}
	M[mtp++] = x;
	mtp %= QUEUE_SIZE;
}

int dequeue()
{
	int ret = Q[hp++];
	hp %= QUEUE_SIZE;
	
	if (ret == M[mhp])
	{
		mhp = (mhp + 1) % QUEUE_SIZE;
	}
	
	return ret;
}

bool empty()
{
	return hp == tp;
}

int get_max()
{
	return M[mhp];
}

int main()
{
	while (true)
	{
		// 1 : enqueue; 2 : dequeue; 3 : get_max.
		int o, x;
		scanf("%d", &o);
		
		switch (o)
		{
		case 1:
			scanf("%d", &x);
			enqueue(x);
			break;
		case 2:
			x = dequeue();
			printf("%d\n", x);
			break;
		case 3:
			printf("%d\n", get_max());
			break;
		}
	}
	return 0;
}
