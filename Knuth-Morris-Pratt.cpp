#include <cstdio>
#include <cstring>

#define MAX_LENGTH 100000

using namespace std;

char T[MAX_LENGTH], P[MAX_LENGTH];
int pi[MAX_LENGTH];
int lt, lp;

void compute_prefix_function()
{
	int q = 0;
	pi[0] = 0;
	
	for (int i = 1; i < lp; i++)
	{
		while (q > 0 && P[i] != P[q])
		{
			q = pi[q - 1];
		}
		
		if (P[i] == P[q])
		{
			q++;
		}
		
		pi[i] = q;
	}
}

void KMP_matcher()
{
	compute_prefix_function();
	
	int q = 0;
	
	for (int i = 0; i < lt; i++)
	{
		while (q > 0 && T[i] != P[q])
		{
			q = pi[q - 1];
		}
		
		if (T[i] == P[q])
		{
			q++;
		}
		
		if (q == lp)
		{
			printf("matched with shift %d\n", i - lp + 1);
			q = pi[q - 1];
		}
	}
}

int main()
{
	gets(T);
	gets(P);
	lt = strlen(T);
	lp = strlen(P);
	
	KMP_matcher();
	
	return 0;
}
