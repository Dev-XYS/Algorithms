#include <cstdio>

#define MAX_ELEMENT_COUNT 1000

int n, d[MAX_ELEMENT_COUNT];

void selection_sort() {
	for (int i = 0; i < n; i++) {
		int minv = d[i], minp = i;
		for (int j = i + 1; j < n; j++) {
			if (d[j] < minv) {
				minv = d[j];
				minp = j;
			}
		}
		int t = d[i];
		d[i] = minv;
		d[minp] = t;
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", d + i);
	}
	selection_sort();
	for (int i = 0; i < n; i++) {
		printf("%d ", d[i]);
	}
	printf("\n");
	return 0;
}
