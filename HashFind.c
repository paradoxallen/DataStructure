//开放定址法的类型声明
#define MAXTABLESIZE 100000 //允许开辟的最大散列表长度
typedef int ElementType; //关键词类型用整型
typedef int Index;  //散列地址类型
typedef Index Position;  //数据所在位置和散列地址是同一类型

//散列单元状态类型， 分别对应：有合法元素，空单元，已删除元素
typedef enum {
	Legitimate, Empty, Deleted
} EntryType;

typedef struct HashEntry Cell;  //散列表单元类型
struct HashEntry{
	ElementType Data;  //存放元素
	EntryType Info; 
};

typedef struct TblNode *HashTable;  //散列表类型
struct TblNode{  //散列表节点定义 
	int TableSize;  //表的最大长度
	Cell *Cells;  //存放散列单元数据的数组 
}; 

//开放定值法的初始化函数
itn NextPrime(int N){
	//返回大于N且不超过MAXTABLESIZE的最小素数 
	int i, p=(N%2)?N+2:N+1;  //从大于N的下一个奇数开始
	
	while(p<=MAXTABLESIZE){
		for(i=(int)sqrt(p); i>2; i--){
			if(!(p%i)){
				break;  //p不是素数 
			}
		}
		if(i==2){
			break;  //for正常结束，说明p是素数 
		} 
		else{
			p+=2;  //否则试探下一个奇数 
		}
	} 
	return p; 
} 

HashTable CreateTable(int TableSize){
	HashTable H;
	int i;
	H = (HashTable)malloc(sizeof(struct TblNode));
	//保证散列表最大长度是素数
	H->TableSize = NextPrime(TableSize);
	//声明单元数组
	H->Cells = (Cell *)malloc(H->TableSize*sizeof(Cell));
	//初始化单元状态为空单元
	for(i=0; i<H->TableSize; i++){
		H->Cells[i].info = Empty;
	} 
	return H;
}

//散列函数(位移映射
int Hash(const char *Key, int TableSize){
	unsighed int H=0;	//散列函数值，初始化为0
	while(*Key != '\0'){
		H = (H<<5) + *Key++;
	} 
	return H%TableSize;
} 
 

//平方探测法的查找函数
Position Find(HashTable H, ElementType Key){
	Position CurrentPos, NewPos;
	int CNum = 0;  //记录冲突次数
	
	NewPos = CurrentPos = Hash(Key, H->TabelSize);	//初始化散列位置
	//当该位置的单元非空，并且不是要找的元素时，发生冲突
	while(H->Cells[NewPos].Info!=Empty && H->Cells[NewPos].Data!=Key){
		//字符串类型的关键词需要strcmp函数
		//统计一次冲突，并判断奇偶次
		if(++CNum%2){
			//奇数次冲突
			//增量为+[(CNum+1)/2]^2
			NewPos = CurrentPos +(CNum+1)*(CNum+1)/4; 
			if(NewPos >= H->TableSize){
				NewPos = NewPos % H->TableSize; //调整为合法地址 
			}
		} 
		else{
			//偶数次冲突
			NewPos = CurrentPos - Cnum*Cnum/4;
			while(NewPos<0){
				NewPos += H->TableSize;	//调整为合法地址 
			} 
		}
		return NewPos;
		//此时NewPos或是Key的位置，或是空单元的位置，表示找不到 
	} 
} 

//平方探测法的插入函数
bool Insert(HashTable H, ElementType Key){
	Position Pos = Find(H, Key);	//先检查Key是否已经存在
	 
	if(H->Cells[Pos].Info != Legitimate){
		//如果这个单元没有被占，说明Key可以插入在此
		H->Cells[Pos].Info = Legitimate;
		H->Cells[Pos].Data = Key;
		//字符串类型的关键词需要strcpy函数
		return true; 
	} 
	else{
		printf("键值已存在");
		return false;
	}
} 


//分离链接法的结构声明
#define KEYLENGTH 15	//关键词字符串的最大长度 
typedef char ElementType[KEYLENGTH+1] 	//关键词类型用字符串
typedef int Index	//散列地址类型

//单链表定义
typedef struct LNode *PtrToNode;
struct LNode{
	ElementType Data;
	PtrToNode Next;
}; 
typedef PtrToLNode Position;
typedef PtrToLNode List;

typedef struct TblNode *HashTable;	//散列表类型
struct TblNode{
	//散列表节点定义
	int TableSize;	//表的最大长度 
	List Heads;	 	//指向链表头结点的数组 
}; 

//分离链接法的初始化函数
HashTable CreateTable(int TableSize){
	HashTable H;
	int i;
	
	H = (HashTable)malloc(sizeof(struct TblNode));
	//保证散列表最大长度为素数
	H->TableSize = NextPrime(TableSize);
	
	//分配链表头结点数组
	H->Head = (List)malloc(H->TableSize*sizeof(struct LNode));
	//初始化表头结点
	for(i=0; i<H->TableSize; i++){
		H->Heads[i].Data[0]='\0';
		H->Heads[i].Next = NULL;
	} 
	return H;
} 

//分离链表法的查找函数
Position Find(HashTable H, ElementType Key){
	Position P;
	Index Pos;
	
	Pos = Hash(Key, H->TableSize);	//初始散列位置
	P = H->Head[Pos].Next;	//从该链表的第一个节点开始
	//但未到表尾，并且Key未找到时
	while(P && strcmp(P->Data, Key)){
		P = P->Next;
	} 
	
	return P;	//此时找到返回地址或未找到返回NULL 
} 

//分离链接法的插入函数
bool Insert(HashTable H, ElementType Key){
	Position P, NewCell;
	Index Pos;
	
	P = Find(H, Key);
	if(!P){
		//关键词未找到，可以插入
		NewCell = (Pos)malloc(sizeof(struct LNode));
		strcpy(NewCell->Data, Key);
		Pos = Hash(Key, H->TableSize);	//初始散列位置
		//将NewCell插入为H->Heads[Pos]链表的第一个结点
		NewCell->Next = H->Heads[Pos].Next;
		H->Heads[Pos].Next = NewCell;
		return true; 
	}
	else{
		//关键词已存在
		printf("键值已存在")；
		return false; 
	}
} 

//分离链接发的释放散列表函数
void DestroyTable(HashTable H) {
	int i;
	Position P, Tmp;
	
	//释放每个链表的结点
	for(i=0; i<H->TableSize; i++){
		P = H->Heads[i].Next;
		while(P){
			Tmp = P->Next;
			free(P);
			P = Tmp;
		}
	} 
	free(H->Heads);	//释放头结点数组
	free(H);	//释放散列表结点 
}
