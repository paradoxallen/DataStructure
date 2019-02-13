#include <stdio.h>

//ð������
void BubbleSort(ElementType A[], int N){
	int i, p;
	bool flag;
	
	for(p=N-1; p>=0; p--){
		flag = false; //��¼�ô�ѭ�����Ƿ���������������˵�������������� 
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

//��������
void InsertionSort(ElementType A[], int N){
	int i, p;
	ElementType tmp;
	
	for(p=1; p<=N; p++){
		tmp = A[p];  //ȡ��δ���������еĵ�һ��Ԫ��  
		for(i=p; i>0&&tmp<A[i-1]; i--){
			A[i] = A[i-1];  //�����������������е�Ԫ�رȽϲ����� 
		}
		A[i] = tmp;  //�Ž����ʵ�λ�� 
	}
} 


//ϣ������
void ShellSort(ElmentType A[], int N){
	//��Sedgewick�������У�9*4**i-9*2**i+1�� 
	int Si, D, p, i;
	ElementType tmp;
	int Sedgewick[] = {929, 505, 209, 109, 41, 19, 5, 1, 0};
	
	for(Si=0; Sedgewick[Si]>=N; Si++){
		;//��ʼ������Sedgewick[Si]���ܳ����������еĳ��� 
	} 
	
	for(D=Sedgewick[Si]; D>0; D=Sedgewick[++Si]){
		for(p=D; p<N; p++){
			//��������
			tmp = A[p];
			for(i=p; i>D&&tmp<A[i-D]; i-=D){
				A[i] = A[i-D];
			} 
			A[i] = tmp;
		}
	} 
} 


//��ѡ������
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

//������
void PercDown(ElementType A[], int p, int N){
	//��N��Ԫ�ص�������A[P]Ϊ�����Ӷѵ���Ϊ����
	int Parent, Child;
	ElementType X;
	
	X = A[p]; //ȡ�����ڵ�����ŵ�ֵ
	for(Parent=p; (Parent*2+1)<N; Parent=Child){
		Child = Parent*2+1;
		if((Child!=N-1)&&(A[Child]<A[Child+1])){
			Child++; //ָ�������ӽڵ�����ֵ 
		}
		if(X>=A[Child]){
			break; //�ҵ��˺���λ�� 
		} 
		else{
			//����X
			A[Parent] = A[Child]; 
		} 
	} 
	A[Parent]=X;
} 

void HeapSort(ElementType A[], int N){
	//������
	int i;
	
	for(i=N/2-1; i>=0; i--){
		//��������
		PercDown(A, i, N); 
	} 
	for(i=N-1; i>0; i--){
		//ɾ��������
		Swap(&A[0],&A[i]);
		PercDown(A, 0, i); 
	}
}


//�鲢����
void Merge(ElementType A[], ElementType TmpA[], int L, int R, int  RightEnd){
	//L=�����ʼλ�ã�R=�ұ���ʼλ�ã�RightEnd=�ұ���ֹλ�� 
	//�������A[L]~A[R-1]��A[R]~A[RightEnd]�鲢��һ����������
	int LeftEnd, NumElements, Tmp;
	int i;
	
	LeftEnd = R-1; //����յ�λ�� 
	Tmp = L;   //�������е���ʼλ��
	NumElements = RightEnd-L-1; //Ԫ���ܸ���
	
	while(L<=LeftEnd && R<=RightEnd){//�Ƚϸ���Ԫ�� 
		if(A[L]<=A[R]){
			TmpA[Tmp++] = A[L++];
		}
		else{
			TmpA[Tmp++] = A[R++];
		}
	} 
	
	while(L<LeftEnd){//����ʣ�µ� 
		TmpA[Tmp++] = A[L++]; 
	}
	while(R<RightEnd){
		TmpB[Tmp++] = A[R++];
	}
	
	for(i=0; i<NumElements; i++, RightEnd--){
		A[RightEnd] = TmpA[RightEnd];  //�������TmpA[]���ƻ�A[] 
	}
} 

void Msort(ElementType A[], ElementType TmpA[], int L, int RightEnd){
	//���ĵݹ�������
	int Center;
	
	if(L<RightEnd){
		Center = (L+RightEnd)/2;
		Msort(A, TmpA, L, Center);   //�ݹ������ 
		Msort(A, TmpA, Center+1, RightEnd);  //�ݹ����ұ� 
		Merge(A, TmpA, L, Center+1, RightEnd);  //�ϲ������������� 
	} 
}

void MergeSort(ElementType A[], int N){
	//�鲢����
	ElementType *TmpA;
	TmpA = (ElementType *)malloc(N*sizeof(ElementType));
	
	if(TmpA != NULL){
		Msort(A, TmpA, 0, N-1);
		free(TmpA);
	} 
	else{
		printf("�ռ䲻�㡣"); 
	}
}
