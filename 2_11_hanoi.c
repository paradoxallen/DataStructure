#include <stdio.h>

void Move(int n, char start, char goal, char temp) {
	if(n==1) {
		printf("Move disk %d from %c to %c. \n", n, start, goal);
	}
	else {
		Move(n-1, start, temp, goal);
		printf("Move disk %d from %c to %c. \n", n, start, goal);
		Move(n-1, temp, goal, start);		
	}
}

void main() {
	int n = 3;

	Move(n, 'A', 'B', 'C');
	return 0;
}
