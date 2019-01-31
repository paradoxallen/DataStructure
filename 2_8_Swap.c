#include <stdio.h>

void Swap(int *a, int *b) {
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

int main() {
	int a = 1, b = 2;
	Swap(&a, &b);
	printf("a=%d, b=%d", a, b);
	return 0;
}
