#include <stdio.h>

void PrintN(int N);

int main() {
	int N;
	
	scanf("%d", &N);
	PrintN(N);
	return 0;
}

//void PrintN(int N)
//{
//	int i;
//	for(i=1; i<=N; i++) {
//		printf("%d\n", i);		
//	}
//	return;
//}

void PrintN(int N)
{
	if(N>0) {
		PrintN(N-1);
		printf("%d\n", N);
	}
}
