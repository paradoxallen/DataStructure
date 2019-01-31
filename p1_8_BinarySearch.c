#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10
#define NotFound 0
typedef int ElementType;

typedef int Position;
typedef struct LNode *List;
struct LNode {
    ElementType Data[MAXSIZE];
    Position Last; /* 保存线性表中最后一个元素的位置 */
};

List ReadInput(); /* 裁判实现，细节不表。元素从下标1开始存储 */
Position BinarySearch( List L, ElementType X );

int main()
{
    List L;
    ElementType X;
    Position P;

    L = ReadInput();
    scanf("%d", &X);
    P = BinarySearch( L, X );
    printf("%d\n", P);

    return 0;
}

int ReadInput(){
	int i, N;
	scanf("%d", &N);
	int List[N];
	for (i=1; i<=N; i++) {
		scanf("%d", &List[i]);
	}
}

	
/* 你的代码将被嵌在这里 */
int BinarySearch(List L, int X){
	if(L==NULL){
		return NotFound;
	}
	int mid, head = 1 , tail = L->Last;
	while(head<=tail){
		mid = (head+tail)/2;
		if(L->Data[mid]<X){
			head = mid + 1;
		}
		else if(L->Data[mid]>X){
			tail = mid - 1;
		}
		else if(L->Data[mid]==X){
			return mid;
		}
	}
	return NotFound;
}
