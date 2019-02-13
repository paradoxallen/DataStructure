#include <stdio.h>

//冒泡排序
void BubbleSort(ElementType A[], int N){
	int i, p;
	bool flag;
	
	for(p=N-1; p>=0; p--){
		flag = false; //记录该次循环中是否发生交换，若无这说明整个序列有序 
		for(i=0; i<p; i++){
			if(A[i]>A[i+1]){
				Swap(&A[i], &A[i+1]);
				flag = true;
			}
		}
		if(flag==false){
			break;
		}
	}
} 

//插入排序
void InsertionSort(ElementType A[], int N){
	int i, p;
	ElementType tmp;
	
	for(p=1; p<=N; p++){
		tmp = A[p];  //取出未排序序列中的第一个元素  
		for(i=p; i>0&&tmp<A[i-1]; i--){
			A[i] = A[i-1];  //依次与已排序序列中的元素比较并右移 
		}
		A[i] = tmp;  //放进合适的位置 
	}
} 


//希尔排序
void ShellSort(ElmentType A[], int N){
	//用Sedgewick增量序列（9*4**i-9*2**i+1） 
	int Si, D, p, i;
	ElementType tmp;
	int Sedgewick[] = {929, 505, 209, 109, 41, 19, 5, 1, 0};
	
	for(Si=0; Sedgewick[Si]>=N; Si++){
		;//初始的增量Sedgewick[Si]不能超过待排序列的长度 
	} 
	
	for(D=Sedgewick[Si]; D>0; D=Sedgewick[++Si]){
		for(p=D; p<N; p++){
			//插入排序
			tmp = A[p];
			for(i=p; i>D&&tmp<A[i-D]; i-=D){
				A[i] = A[i-D];
			} 
			A[i] = tmp;
		}
	} 
} 


//简单选择排序
void Swap(ElementType *a, ElementType *b){
	ElementType t=*a, *a=*b, *b=t;
} 

void SimpleSelectionSort(ElementType A[], int N){
	int i, j, minp;
	
	for(i=0; i<N-1; i++){
		minp=i;
		for(j=i+1; j<N; j++){
			if(A[minp]>A[j]){
				minp = j;
			}
		}
		Swap(&A[i], &A[minp]);
	}
}

//堆排序
void PercDown(ElementType A[], int p, int N){
	//将N个元素的数组以A[P]为根的子堆调整为最大堆
	int Parent, Child;
	ElementType X;
	
	X = A[p]; //取出根节点所存放的值
	for(Parent=p; (Parent*2+1)<N; Parent=Child){
		Child = Parent*2+1;
		if((Child!=N-1)&&(A[Child]<A[Child+1])){
			Child++; //指向左右子节点的最大值 
		}
		if(X>=A[Child]){
			break; //找到了合适位置 
		} 
		else{
			//下滤X
			A[Parent] = A[Child]; 
		} 
	} 
	A[Parent]=X;
} 

void HeapSort(ElementType A[], int N){
	//堆排序
	int i;
	
	for(i=N/2-1; i>=0; i--){
		//建立最大堆
		PercDown(A, i, N); 
	} 
	for(i=N-1; i>0; i--){
		//删除最大堆项
		Swap(&A[0],&A[i]);
		PercDown(A, 0, i); 
	}
}


//归并排序
void Merge(ElementType A[], ElementType TmpA[], int L, int R, int  RightEnd){
	//L=左边起始位置，R=右边起始位置，RightEnd=右边终止位置 
	//将有序的A[L]~A[R-1]和A[R]~A[RightEnd]归并成一个有序序列
	int LeftEnd, NumElements, Tmp;
	int i;
	
	LeftEnd = R-1; //左边终点位置 
	Tmp = L;   //有序序列的起始位置
	NumElements = RightEnd-L-1; //元素总个数
	
	while(L<=LeftEnd && R<=RightEnd){//比较复制元素 
		if(A[L]<=A[R]){
			TmpA[Tmp++] = A[L++];
		}
		else{
			TmpA[Tmp++] = A[R++];
		}
	} 
	
	while(L<LeftEnd){//复制剩下的 
		TmpA[Tmp++] = A[L++]; 
	}
	while(R<RightEnd){
		TmpB[Tmp++] = A[R++];
	}
	
	for(i=0; i<NumElements; i++, RightEnd--){
		A[RightEnd] = TmpA[RightEnd];  //将有序的TmpA[]复制回A[] 
	}
} 

void Msort(ElementType A[], ElementType TmpA[], int L, int RightEnd){
	//核心递归排序函数
	int Center;
	
	if(L<RightEnd){
		Center = (L+RightEnd)/2;
		Msort(A, TmpA, L, Center);   //递归解决左边 
		Msort(A, TmpA, Center+1, RightEnd);  //递归解决右边 
		Merge(A, TmpA, L, Center+1, RightEnd);  //合并两段有序序列 
	} 
}

void MergeSort(ElementType A[], int N){
	//归并排序
	ElementType *TmpA;
	TmpA = (ElementType *)malloc(N*sizeof(ElementType));
	
	if(TmpA != NULL){
		Msort(A, TmpA, 0, N-1);
		free(TmpA);
	} 
	else{
		printf("空间不足。"); 
	}
}
