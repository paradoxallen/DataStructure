//���Ŷ�ַ������������
#define MAXTABLESIZE 100000 //�����ٵ����ɢ�б���
typedef int ElementType; //�ؼ�������������
typedef int Index;  //ɢ�е�ַ����
typedef Index Position;  //��������λ�ú�ɢ�е�ַ��ͬһ����

//ɢ�е�Ԫ״̬���ͣ� �ֱ��Ӧ���кϷ�Ԫ�أ��յ�Ԫ����ɾ��Ԫ��
typedef enum {
	Legitimate, Empty, Deleted
} EntryType;

typedef struct HashEntry Cell;  //ɢ�б�Ԫ����
struct HashEntry{
	ElementType Data;  //���Ԫ��
	EntryType Info; 
};

typedef struct TblNode *HashTable;  //ɢ�б�����
struct TblNode{  //ɢ�б�ڵ㶨�� 
	int TableSize;  //�����󳤶�
	Cell *Cells;  //���ɢ�е�Ԫ���ݵ����� 
}; 

//���Ŷ�ֵ���ĳ�ʼ������
itn NextPrime(int N){
	//���ش���N�Ҳ�����MAXTABLESIZE����С���� 
	int i, p=(N%2)?N+2:N+1;  //�Ӵ���N����һ��������ʼ
	
	while(p<=MAXTABLESIZE){
		for(i=(int)sqrt(p); i>2; i--){
			if(!(p%i)){
				break;  //p�������� 
			}
		}
		if(i==2){
			break;  //for����������˵��p������ 
		} 
		else{
			p+=2;  //������̽��һ������ 
		}
	} 
	return p; 
} 

HashTable CreateTable(int TableSize){
	HashTable H;
	int i;
	H = (HashTable)malloc(sizeof(struct TblNode));
	//��֤ɢ�б���󳤶�������
	H->TableSize = NextPrime(TableSize);
	//������Ԫ����
	H->Cells = (Cell *)malloc(H->TableSize*sizeof(Cell));
	//��ʼ����Ԫ״̬Ϊ�յ�Ԫ
	for(i=0; i<H->TableSize; i++){
		H->Cells[i].info = Empty;
	} 
	return H;
}

//ɢ�к���(λ��ӳ��
int Hash(const char *Key, int TableSize){
	unsighed int H=0;	//ɢ�к���ֵ����ʼ��Ϊ0
	while(*Key != '\0'){
		H = (H<<5) + *Key++;
	} 
	return H%TableSize;
} 
 

//ƽ��̽�ⷨ�Ĳ��Һ���
Position Find(HashTable H, ElementType Key){
	Position CurrentPos, NewPos;
	int CNum = 0;  //��¼��ͻ����
	
	NewPos = CurrentPos = Hash(Key, H->TabelSize);	//��ʼ��ɢ��λ��
	//����λ�õĵ�Ԫ�ǿգ����Ҳ���Ҫ�ҵ�Ԫ��ʱ��������ͻ
	while(H->Cells[NewPos].Info!=Empty && H->Cells[NewPos].Data!=Key){
		//�ַ������͵Ĺؼ�����Ҫstrcmp����
		//ͳ��һ�γ�ͻ�����ж���ż��
		if(++CNum%2){
			//�����γ�ͻ
			//����Ϊ+[(CNum+1)/2]^2
			NewPos = CurrentPos +(CNum+1)*(CNum+1)/4; 
			if(NewPos >= H->TableSize){
				NewPos = NewPos % H->TableSize; //����Ϊ�Ϸ���ַ 
			}
		} 
		else{
			//ż���γ�ͻ
			NewPos = CurrentPos - Cnum*Cnum/4;
			while(NewPos<0){
				NewPos += H->TableSize;	//����Ϊ�Ϸ���ַ 
			} 
		}
		return NewPos;
		//��ʱNewPos����Key��λ�ã����ǿյ�Ԫ��λ�ã���ʾ�Ҳ��� 
	} 
} 

//ƽ��̽�ⷨ�Ĳ��뺯��
bool Insert(HashTable H, ElementType Key){
	Position Pos = Find(H, Key);	//�ȼ��Key�Ƿ��Ѿ�����
	 
	if(H->Cells[Pos].Info != Legitimate){
		//��������Ԫû�б�ռ��˵��Key���Բ����ڴ�
		H->Cells[Pos].Info = Legitimate;
		H->Cells[Pos].Data = Key;
		//�ַ������͵Ĺؼ�����Ҫstrcpy����
		return true; 
	} 
	else{
		printf("��ֵ�Ѵ���");
		return false;
	}
} 


//�������ӷ��Ľṹ����
#define KEYLENGTH 15	//�ؼ����ַ�������󳤶� 
typedef char ElementType[KEYLENGTH+1] 	//�ؼ����������ַ���
typedef int Index	//ɢ�е�ַ����

//��������
typedef struct LNode *PtrToNode;
struct LNode{
	ElementType Data;
	PtrToNode Next;
}; 
typedef PtrToLNode Position;
typedef PtrToLNode List;

typedef struct TblNode *HashTable;	//ɢ�б�����
struct TblNode{
	//ɢ�б�ڵ㶨��
	int TableSize;	//�����󳤶� 
	List Heads;	 	//ָ������ͷ�������� 
}; 

//�������ӷ��ĳ�ʼ������
HashTable CreateTable(int TableSize){
	HashTable H;
	int i;
	
	H = (HashTable)malloc(sizeof(struct TblNode));
	//��֤ɢ�б���󳤶�Ϊ����
	H->TableSize = NextPrime(TableSize);
	
	//��������ͷ�������
	H->Head = (List)malloc(H->TableSize*sizeof(struct LNode));
	//��ʼ����ͷ���
	for(i=0; i<H->TableSize; i++){
		H->Heads[i].Data[0]='\0';
		H->Heads[i].Next = NULL;
	} 
	return H;
} 

//���������Ĳ��Һ���
Position Find(HashTable H, ElementType Key){
	Position P;
	Index Pos;
	
	Pos = Hash(Key, H->TableSize);	//��ʼɢ��λ��
	P = H->Head[Pos].Next;	//�Ӹ�����ĵ�һ���ڵ㿪ʼ
	//��δ����β������Keyδ�ҵ�ʱ
	while(P && strcmp(P->Data, Key)){
		P = P->Next;
	} 
	
	return P;	//��ʱ�ҵ����ص�ַ��δ�ҵ�����NULL 
} 

//�������ӷ��Ĳ��뺯��
bool Insert(HashTable H, ElementType Key){
	Position P, NewCell;
	Index Pos;
	
	P = Find(H, Key);
	if(!P){
		//�ؼ���δ�ҵ������Բ���
		NewCell = (Pos)malloc(sizeof(struct LNode));
		strcpy(NewCell->Data, Key);
		Pos = Hash(Key, H->TableSize);	//��ʼɢ��λ��
		//��NewCell����ΪH->Heads[Pos]����ĵ�һ�����
		NewCell->Next = H->Heads[Pos].Next;
		H->Heads[Pos].Next = NewCell;
		return true; 
	}
	else{
		//�ؼ����Ѵ���
		printf("��ֵ�Ѵ���")��
		return false; 
	}
} 

//�������ӷ����ͷ�ɢ�б���
void DestroyTable(HashTable H) {
	int i;
	Position P, Tmp;
	
	//�ͷ�ÿ������Ľ��
	for(i=0; i<H->TableSize; i++){
		P = H->Heads[i].Next;
		while(P){
			Tmp = P->Next;
			free(P);
			P = Tmp;
		}
	} 
	free(H->Heads);	//�ͷ�ͷ�������
	free(H);	//�ͷ�ɢ�б��� 
}
