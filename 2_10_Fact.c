#include <stdio.h>

int Fact(int N) {
	if(N==0) {
		return 1;
	}
	else {
		return N*Fact(N-1);
	}
}

int main() {
	int N = 10;
	int result;
	result = Fact(N);
	printf("result=%d", result);
}
