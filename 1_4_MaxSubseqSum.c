#include <stdio.h>

int main() {
	int i, N, MaxSum;
	scanf("%d", &N);
	int List[N];
	for (i=0; i<N; i++) {
		scanf("%d", &List[i]);
	}

	MaxSum = MaxSubseqSum(List, N);
	printf("%d", MaxSum);
}


int MaxSubseqSum(int List[], int N) {
	int i;
	int ThisSum, MaxSum;
	
	ThisSum = MaxSum = 0;
	for(i=0; i<N; i++) {
		ThisSum+=List[i];
		if(ThisSum>MaxSum) {
			MaxSum = ThisSum;
		}
		else if(ThisSum<0) {
			ThisSum = 0;
		}
	} 
	return MaxSum;
}
