#include <stdio.h>

//������ 
int main(){
	FILE *fp;
	HashTable H;	//���Ӽ�����Count 
	ElementType Word;
	int TableSize = 100;	//ɢ�б���ƴ�С
	int length, wordcount = 0;
	char document[30] = "HarryPotter.txt";	//Ҫ��ͳ�ƵĴ�Ƶ���ļ���
	
	H = CreateTable(TableSize);	//����ɢ�б�
	if((fp=fopen(document, "r"))==NULL) {
		printf("�޷����ļ���\n");
	}
	
	while(!feof(fp)){
		length = GetAWord(fp, word);	//��ȡһ������
		if(length>3){
			//ֻ���ǳ��ȴ���3���ַ��ĵ���
			wordcount++;
			InsertAndCount(H, word);	//ͳ��word���ִ��� 
		} 
	}
	fclose(fp);
	
	printf("���ĵ�������%d����Ч����", wordcount);
	Show(H, 10.0/100);	//��ʾ��Ƶǰ10%�ĵ���
	DestroyTable(H);	//����ɢ�б� 
	return 0;
} 


//����������
struct LNode{
	ElementType Data;
	int Count;
	PtrToLNode Next;
}; 

//����ɢ�б� 
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

//ɢ�к���(λ��ӳ��
int Hash(const char *Key, int TableSize){
	unsighed int H=0;	//ɢ�к���ֵ����ʼ��Ϊ0
	while(*Key != '\0'){
		H = (H<<5) + *Key++;
	} 
	return H%TableSize;
} 


//���뵥�ʲ�ͳ�ƴ�Ƶ
void InsertAndCount(HashTable H, ElementType Key){
	Position P, NewCell;
	Inder Pos;
	
	P = Find(H, Key);
	if(!P){
		//�ؼ���û�ҵ������Բ���
		NewCell = (Position)malloc(sizeof(struct LNode));
		strcpy(NewCell->Data, Key);
		NewCell->Count = 1;	//�µ��ʵ�һ�γ���
		Pos = Hash(Key, H->TableSize);	//��ʼ��ɢ��λ�� 
		//��NewCell����H->Heads[Pos]����ĵ�һ�����
		NewCell->Next = H->Heads[Pos].Next;
		H->Heads[Pos].Next = NewCell;
		H->Heads[Pos].Count++; 
	}
	else{
		//�ؼ����Ѵ���
		P->Count++; 
	}
} 

//�жϺϷ��ĵ����ַ�������Ϊ��Сд��ĸ�����ֺ��»���
bool IsWordChar(char c){
	if(c>='a'&&c<='z' || c>='A'&&c<='Z' || c>='0'&&c<='9' || c=='_'){
		return true;
	}
	else{
		return false;
	}
} 

//��ȡһ������
#define MAXWORDLEN 80	//���е�����󳤶�

int GetAWord(FILE *fp, ElementType word){
	char tempword[MAXWORDLEN+1], c;
	int len = 0;	//���ʳ���
	
	c = fgetc(fp);
	while(!feof(fp)){
		if(IsWordChar(c)){
			//����ǺϷ��ĵ����ַ� 
			tempword[len++] = c;
		}
		c = fgetc(fp);
		//��������ǰ�ķǷ��ַ������ԷǷ��ַ�����һ������
		if(len&&!IsWordChar(c)){
			break
		} 
	} 
	tempword[len] = '\0';	//�趨�ַ���������
	if(len>KEYLENGTH){
		//̫���ĵ��ʱ��ض�
		tempword[KEYLENGTH] = '\0';
		len = KEYLENGTH; 
	} 
	strcpy(word, tempword);
	return len;
} 

//��ʾ��Ƶ���������ı��������е���
void Show(HashTable H, double percent){
	int diffwordcount = 0;	//��ͬ�ĵ�������
	int maxf = 0;	//���Ĵ�Ƶ
	int *diffwords;	//ÿ����Ƶ��Ӧ�Ĳ�ͬ��������
	int maxCollision = 0;	//����ͻ�������������ȣ�����ʼ��Ϊ�� 
	int minCollision = 100;	//��С��ͻ��������ʼ��Ϊ100
	Position L;
	int i, j, k, lowerbound, count=0;
	
	for(i=0; i<H->TableSize; i++){
		//��ͬ���ʵ�����
		diffwordcount += H->Heads[i].Count;	//ͷ���Countͳ��������
		//ͳ��������С�ĳ�ͻ����
		if(maxCollision<H->Heads[i].Count){
			maxCollision = H->Heads[i].Count;
		} 
		if(minCollision>H->Heads[i].Count){
			minCollision = H->Heads[i].Count;
		}
		//�����Ĵ�Ƶ
		L = H->Heads[i].Next;	//��ÿ������ı�ͷ��ʼ
		while(L){
			//��������
			if(maxf<L->Count){
				maxf = L->Count;
				L = L->Next;
			} 
		} 
	} 
	
	printf("����%d����ͬ�ĵ��ʣ���Ƶ������%d��\n", diffwordcount, maxf);
	printf("����ͻ������%d����С��ͻ������%d��\n", maxCollision, minCollision);
	
	//��ÿ����Ƶ�ȼ�ӵ�еĲ�ͬ�������� 
	//�������Ĵ�Ƶ������һ����������
	diffwords = (int *)malloc((maxf+1)*sizeof(int));
	//ͳ�ƴ�Ƶ1��maxf�ĵ�������
	for(i=0; i<=maxf; i++){
		diffwords[i] = 0;
	} 
	for(i=0; i<H->TableSize; i++){
		L = H->Heads[i].Next;
		while(L){
			//��������
			diffwords[L->Count]++;	//�ô�Ƶ����һ������
			L = L->Next; 
		}
	}
	
	//���ض��Ĵ�Ƶ��ʹ�ô��ڵ��ڸô�Ƶ�ĵ����ܺͳ����ض��ı���
	lowerbound = (int)(diffwordcount *percent);
	for(i=maxf; i>=1&&count<lowerbound; i--){
		count += diffwords[i];
	} 
	//����Ƶ�Ӵ�С�������
	for(j=maxf; j>=i; j--){
		//��ÿ����Ƶ
		for(k=0; k<H->TableSize; k++){
			//��������ɢ�б�
			L = H->Heads[k].Next;
			while(L){
				if(j==L->Count){
					//����һ�����ʵĴ�Ƶ�뵱ǰ��Ƶ��ȣ�����õ����Լ���Ƶ 
					 printf("%-15s:%d\n", L->Data, L->Count); 
				}
				L = L->Next;
			} 
		} 
	} 
	free(diffwords);
} 
