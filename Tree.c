typedef struct TNode *Position
typedef Postion BinTree

Stuct TNode {
	ElementType Data;
	BinTree Left;
	BinTree Right;
};

void InorderTraversal(BinTree Bt){
	if(BT){
		InorderTraversal(BT->Left);
		printf("%d", BT->Data);
		InorderTraversal(BT->Right);
	}
} 

void PreorderTraversal(BinTree Bt){
	if(BT){
		printf("%d", BT->Data);
		PreorderTraversal(BT->Left);	
		PreorderTraversal(BT->Right);
	}
} 

void PostorderTraversal(BinTree Bt){
	if(BT){
		PostorderTraversal(BT->Left);	
		PostorderTraversal(BT->Right);
		printf("%d", BT->Data);
	}
} 

void Inordertravetsal(BinTree BT){
	BinTree T;
	Stack S = CreateStack();
	T = BT;
	while(T || !IsEmpty(S)){
		while(T){
			Push(S, T);
			T = T->Left; 	
		}
		T = Pop(S);
		Print("%d", T->Data);
		T = T->Right;
	}
	
} 

void LevelorderTraversal(BinTree BT){
	Queue Q;
	BinTree T;
	
	if(!BT){
		return;
	}
	
	Q = CreateQueue();
	Add(Q, BT);
	while(!IsEmpty){
		T = DeleteQ(Q);
		printf("%d", T->Data);
		if(T->Left){
			AddQ(Q, T-Left);
		}
		if(T->Right){
			AddQ(Q, T->Right);
		}
	}
}

void PreorderPrintLeaves(BinTree Bt){
	if(BT){
		if(!BT->Left && !BT->Right){
			printf("%d", BT->Data);			
		}
		PreorderPrintLeaves(BT->Left);	
		PreorderPrintLeaves(BT->Right);
	}
} 

int GetHeight(BinTree Bt){
	int HL, HR, MAXH;
	
	if(BT){
		GetHeight(BT->Left);	
		GetHeight(BT->Right);
		MaxH=HL>HR?HL:HR;
		return (MAXH+1);
	}
	else{
		return 0;
	}
} 

//生成二叉树
typedef int ElementType;
#define NoInfo 0 //没有节点 
BinTree CreateBinTree(){
	ElementType Data;
	BinTree BT, T;
	Queue Q = CreateQueue();
	
	//建立根节点
	scanf("%d", &Data);
	if(Data != NoInfo){
		BT = (BinTree)malloc(sizeof(Struct TNode));
		BT->Data = Data;
		BT->Left = BT->Right = NULL;
		AddQ(Q, Bt); 
	} 
	else return NULL; //空树
	while(!IsEmpty(Q)){
		T=DeleteQ(Q); //取出节点地址
		scanf("%d", &Data); //左孩子
		if(Data==NoInfo){
			T->Left = NULL;
		} 
		else{
			T->Left = (BinTree)malloc(sizeof(Struct TNode));
			T->Left->Data = Data;
			T->Left->Left = BT->Left->Right = NULL;
			AddQ(Q, T->Left); 			
		}
		
		scanf("%d", &Data); //右孩子
		if(Data==NoInfo){
			T->Right = NULL;
		} 
		else{
			T->Right = (BinTree)malloc(sizeof(Struct TNode));
			T->Right->Data = Data;
			T->Right->Left = BT->Right->Right = NULL;
			AddQ(Q, T->Right); 			
		}
	} 
	return BT;
} 


//二叉搜索树的递归查找函数
Position Find(BinTree BST, ElementType X){
	if(!BST){
		return NULL;
	}
	if(X>BST->Data){
		return Find(BST->Right, X);
	}
	else if(X<BST->Data){
		return Find(BST->Left, X);
	}
	else{
		return BST;
	}
} 

//二叉搜索树的迭代查找函数
 Position Find(BinTree BST, ElementType X){
	while(BST){
		if(X>BST->Data){
			BST = BST->Right;
		}
		else if(X<BST->Data){
			BST = BST->Left;
		}
		else{
			break;
		}		
	}
	return BST;
} 

Position FindMin(BinTree BST){
	if(!BST){
		return NULL;
	}
	else if(!BST->Left){
		return BST;
	}
	else{
		return FindMin(BST->Left);
	}
}

Position FindMax(BinTree BST){
	if(BST){
		while(BST->Right){
			BST= BST->Right;
		}
		return BST; 
	}
}

BinTree Insert(BinTree BST, ElementType X){
	if(!BST){
		BST = (BinTree)malloc(sizeof(Struct TNode));
		BST->Data = X;
		BST->Left = BST->Right = NULL; 
	}
	else{
		if(X<BST->Data){
			BST->Left = Insert(BST->Left, X);
		}
		else if(X>BST->Data){
			BST->Right = Insert(BST->Right, X);
		}
	}
	return BST;
} 


BinTree Delete(BinTree BST, ElementType X){
	Position Tmp;
	if(!BST){
		printf("not fount");
	}
	else{
		if(X<BST->Data){
			BST->Left = Delete(BST->Left, X);
		}
		else if(X>BST->Data){
			BST->Right = Delete(BST->Right, X);
		}
		else{
			if(BST->Left && BST->Right){
				Tmp = FindMin(BST->Right);
				BST->Data = Tmp->Data;
				BST->Right = Delete(BST->Right, BST->Data);
			}
			else{
				Tmp = BST;
				if(!BST->Left){
					BST = BSt->Right; 
				}
				else{
					BST = BST->Left;
				}
				free(Tmp);
			}
		}
	}
	return BST; 
}


//AVL树的插入操作
typedef struct AVLNode *Position;
typedef Position AVLTree; 
typedef struct ACLNode{
	ElementType Data;
	AVLTree Left;
	AVLTree Right;
	int Height;  //树高 
};

int Max(int a, int B){
	return a>b?a:b;
} 

AVLTree Insert(AVLTree T, ElementType X){
	if(!T){
		//空树则建树
		T = (AVLTree)malloc(sizeof(struct AVLNode));
		T->Data = X;
		T->Height = 1;
		T->Left = T->Right = NULL; 
	}
	else if(X<T->Data){
		T->Left = Insert(T->Left, X);
		if(GetHeight(T->Left) - GetHeight(T->Right) == 2){
			if(X < T->Left->Data){
				T = SingleLeftRotation(T); //左单旋 
			}
			else{
				T = DoubleLeftRightRotation(T); //左右双旋 
			} 
		} //else if 插入左子树结束 
	}
	else if(X>T->Data){
		T->Right = Insert(T->Right, X);
		if(GetHeight(T->Left) - GetHeight(T->Right) == -2){
			if(X > T->Right->Data){
				T = SingleRightRotation(T); //右单旋 
			}
			else{
				T = DoubleRightLeftRotation(T); //右左双旋 
			} 
		} //else if 插入右子树结束 		
	}
	
	//else X==Data， 无需插入
	
	T->Height = Max(GetHeight(T->Left), GetHeight(T->Right)); //更新树高
	
	return T; 
	
}

//左单旋算法
AVLTree SingleLeftRotation(AVLTree A){
	//注意A必须有个左子节点B
	AVLTree B = A->Left;
	A->Left = B->Right;
	B->Right = A;
	
	A->Height = Max(GetHeight(A->Left), GetHeight(A->Right))+1;
	B->Height = Max(GetHeight(B->Left), A->Height)+1;
	
	return B;
} 

//左右双旋算法
AVLTree DoubleLeftRightRotation(AVLTree A){
	//注意A必须有个左子节点B， B必须有个右子节点C
	
	A->Left = SingleRightRotation(A->Left); //BC右单旋，返回C
	return SingleLeftRotation(A);           //AC左单旋，返回A 
} 

//堆定义 
typedef struct HNode *Heap;
strucr HNode{
	ElementType *Data;
	int Size;
	int Capacity;
} ;
typedef Heap MaxHeap;
typedef Heap MinHeap;


//最大堆的创建 
#define MAXDATA 1000

MaxHeap CreateHeap(int MaxSize){
	MaxHeap H = (MaxHeap)malloc(sizeof(struct HNode));
	H->Data = (ElementType *)malloc((MaxSize+1)*sizeof(ElementType));
	H->Size = 0;
	H->Capacity = MaxSize;
	H->Data[0] = MAXDATA; //哨兵，最大值
	
	return H; 
} 

//最大堆的插入
bool IsFull(MaxHeap H){
	return(H->Size == H->Capacity);
} 

bool Insert(MaxHeap H, ElementType X){
	int i;
	
	if(IsFull(H)){
		printf("Full.");
		return false;
	}
	i = ++H->Size;
	for( ; H->Data[i/2]; i/=2){
		H->Data[i] == H->Data[i/2]; 
	}
	H->Data[i] = X;
	
	return true;
}

//最大堆的删除
#define ERROR -1

bool IsEmpty(MaxHeap H){
	return(H->Size == 0);
} 

ElementType DeleteMax(MaxHeap H){
	int Parent, Child;
	ElmentType MaxItem, X;
	
	if(IsEmpty(H)){
		printf("Empty.");
		return ERROR;
	}
	
	MaxItem = H->Data[1];
	
	X = H->Data[H->Size--];
	for(Parent=1; Parent*2<H->Size; Parent=Child){
		Child = Parent * 2;
		if((Child!=H->Size)&&(H->Data[Child]<H->Data[Child+1])){
			Child++;
		}
		if(X>=H->Data[Child]){
			break;
		}
		else{
			H->Data[Parent] = H->Data[Child]; //下滤X 
		}
	}
	
	H->Data[Parent] = X;
	
	return MaxItem;
}


//建立最大堆
void PercDown(MaxHeap H, int p){
	//下滤：将H中以H->Data[p]为根的子堆调整为最大堆 
	int Parent, Child;
	ElementType X;
	
	X = H->Data[p]; //取出根节点存的值
	for(Parent=p; Parent*2<H->Size; Parent=Child){
		Child = Parent*2;
		if((Child!=H->Size)&&(H->Data[Child]<H->Data[Child+1])){
			Child++;
		}
		if(X>=H->Data[Child]){
			break;
		}
		else{
			H->Data[Parent] = H->Data[Child];
		}
	} 
	H->Data[Parent] = X;
} 

void BuildHeap(MaxHeap H){
	int i;
	for(i=H->Size/2; i>0; i--){
		PercDown(H, i); 
	}
}


//哈夫曼树的构造
typedef struct HTNode *HuffmanTree;
struct HTNode{
	int Weight;
	HuffmanTree Left;
	HuffmanTree Right;
}; 

HuffmanTree Huffman(MinHeap H){
	int i, N;
	HuffmanTree T;
	
	BuildHeap(H); //将H-Data[ 按权值weight调整为最小堆
	N->H->Size;
	for(i=1; i<N; i++){
		//Size-1次合并
		T = (HuffmanTree)malloc(sizeof(struct HtNode));//建立根节点 
		T->Left = DeleteMin(H);//删除最小堆的一个节点，作为T左子节点 
		T->Right = DeleteMin(H);
		T->Weight = T->Left->Weight + T->Right->Weight;//计算新权值 
		Insert(H, T);
	} 
	
	return DeleteMin(H); //最小堆的最后一个元素即是指向哈夫曼树节点的指针 
} 


//集合 
#define MAXN 1000
typedef int ElementType;
typedef int SetName;
typedef ElementType SetType[MAXN];

//集合元素查找
SetName Find(SetType S, ElementType X){
	for( ; S[X]>=0; X=S[X]);
	return X;
} 

//集合并运算 
void Union1(SetType S, SetName Root1, SetName Root2){
	S[Root2] = Root1;
}

void Union2(SetType S, SetName Root1, SetName Root2){
	if(S[Root2]<S[Root1]){
		S[Root2] += S[Root1];
		S[Root1] = Root2;
	}
	else{
		S[Root1] += S[Root2];
		S[Root2] = Root1;
	}
} 

//Find的路径压缩算法
SetName Find(SetType S, ElementType X){
	if(S[X] < 0){
		return X; 
	}
	else{
		return S[X] = Find(S, S[X]);
	}
} 


