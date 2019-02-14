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


//快速排序
ElementType Median3(ElementType A[], int Left, int Right){
	int Center = (Left+Right)/2;
	if(A[Left])>A[Right]){
		Swap(&A[Left], &A[Right]);
	}
	if(A[Left]>A[Center]){
		Swap(&A[Left], &A[Center]);
	}
	if(A[Center]>A[Right]){
		Swap(&A[Center], &A[Right]);
	}
	//此时A[Left]<=A[Center]<=A[Right]
	Swap(&A[Center], &A[Right-1]);  //将基准Pivot藏到右边
	//只需考虑A[Left+1],A[Right-2] 
	return A[Right-1]; //返回基准值 
} 

void Qsort(ElementType A[], int Left, int Right){
	//核心递归函数
	int Pivot, Cutoff, Low, High;
	
	if(Cutoff<=Right-Left){
		//如果序列元素充分多，进入快排
		Pivot = Median3(A, Left, Right);
		Low = Left;
		High = Right-1;
		while(1){
			//将序列中比基准小的移到基准左边，大的移到右边
			while(A[++Low]<Pivot);
			while(A[--High]>Pivot);
			if(Low<High){
				Swap(&A[Low], &A[High]);
			} 
			else{
				break;
			}
		} 
		Swap(&A[Low], &A[Right-1]); //将基准换到正确的位置
		Qsort(A, Left, Low-1);
		Qsort(A, Low+1, Right); 
	} 
	else{
		InsertionSort(A+Left, Right-Left+1);  //元素太少，用简单排序 
	}
}

void QucikSort(ElementType A[],  int N){
	//统一接口；
	Qsort(A, 0, N-1); 
} 


//次位优先的基数排序算法
//假设元素最多有MaxDigit个关键字，基数全是同样的Radix(进位） 
#define MaxDigit 4
#define Radix 10

//桶元素结点
typedef struct Node *PtrToNode;
struct Node{
	int key;
	PtrToNode next;
}; 

//桶头结点
struct HeadNode{
	PtrToNode head, tail;
}; 
typedef struct HeadNode Bucket[Radix];

int GetDigit(int X, int D){
	//返回整型关键字X的第D位数字 
	//默认次位D=1，主位D<=MaxDigit
	int d, i;
	
	for(i=1; i<=D; i++){
		d = X%Radix;
		X /= Radix;
	} 
	return d;
}

void LSDRadixSort(ElementType A[], int N){
	//基数排序，次位优先
	int D, Di, i;
	Bucket B;
	PtrToNode tmp, p, List = NULL;
	
	for(i=0; i<Radix; i++){
		//初始化每个桶为空链表
		B[i].head = B[i].tail = NULL; 
	} 
	for(i=0; i<N; i++){
		//将原始序列逆序存入初始链表List
		tmp = (PtrToNode)malloc(sizeof(struct Node));
		tmp->key = A[i];
		tmp->next = List;
		List = tmp; 
	}
	
	//下面开始排序
	for (D=1; D<MaxDight; D++){
		//对数据的每一位循环处理
		//下面是分配过程
		p = List;
		while(p){
			Di = GetDight(p->Key, D);  //获得当前元素的当前位数字
			tmp = p; p=p->next;  //从list中摘除
			tmp->next = NULL;  
			//插入B[Di]号桶 
			if(B[Di].head==NULL){
				B[Di].head = B[Di].tail = tmp; 
			} 
			else{
				B[Di].tail->next = tmp;
				B[Di].tail = tmp;
			}
		} 
		
		//下面是收集的过程
		for(Di=Radix-1; Di>=0; Di--){
			//将每个桶的元素顺序收集入List
			if(B[Di].head){
				//如果桶不为空
				//整桶插入List表头
				B[Di].tail->next = List;
				List = B[Di].head;
				B[Di].head = B[Di].tail = NULL; //清空桶 
			} 
		} 
	}
	
	//将List倒入A[]并释放空间
	for(i=0; i<N; i++){
		tmp = List;
		List = List->next;
		A[i] = Tmp->key;
		free(tmp);
	} 
} 



