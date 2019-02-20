#include <stdio.h>

//主函数 
int main(){
	FILE *fp;
	HashTable H;	//增加计数器Count 
	ElementType Word;
	int TableSize = 100;	//散列表估计大小
	int length, wordcount = 0;
	char document[30] = "HarryPotter.txt";	//要被统计的词频的文件名
	
	H = CreateTable(TableSize);	//建立散列表
	if((fp=fopen(document, "r"))==NULL) {
		printf("无法打开文件！\n");
	}
	
	while(!feof(fp)){
		length = GetAWord(fp, word);	//读取一个单词
		if(length>3){
			//只考虑长度大于3个字符的单词
			wordcount++;
			InsertAndCount(H, word);	//统计word出现次数 
		} 
	}
	fclose(fp);
	
	printf("该文档共出现%d个有效单词", wordcount);
	Show(H, 10.0/100);	//显示词频前10%的单词
	DestroyTable(H);	//销毁散列表 
	return 0;
} 


//链表结点类型
struct LNode{
	ElementType Data;
	int Count;
	PtrToLNode Next;
}; 

//建立散列表 
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

//散列函数(位移映射
int Hash(const char *Key, int TableSize){
	unsighed int H=0;	//散列函数值，初始化为0
	while(*Key != '\0'){
		H = (H<<5) + *Key++;
	} 
	return H%TableSize;
} 


//插入单词并统计词频
void InsertAndCount(HashTable H, ElementType Key){
	Position P, NewCell;
	Inder Pos;
	
	P = Find(H, Key);
	if(!P){
		//关键词没找到，可以插入
		NewCell = (Position)malloc(sizeof(struct LNode));
		strcpy(NewCell->Data, Key);
		NewCell->Count = 1;	//新单词第一次出现
		Pos = Hash(Key, H->TableSize);	//初始化散列位置 
		//将NewCell插入H->Heads[Pos]链表的第一个结点
		NewCell->Next = H->Heads[Pos].Next;
		H->Heads[Pos].Next = NewCell;
		H->Heads[Pos].Count++; 
	}
	else{
		//关键词已存在
		P->Count++; 
	}
} 

//判断合法的单词字符，本例为大小写字母，数字和下划线
bool IsWordChar(char c){
	if(c>='a'&&c<='z' || c>='A'&&c<='Z' || c>='0'&&c<='9' || c=='_'){
		return true;
	}
	else{
		return false;
	}
} 

//读取一个单词
#define MAXWORDLEN 80	//所有单词最大长度

int GetAWord(FILE *fp, ElementType word){
	char tempword[MAXWORDLEN+1], c;
	int len = 0;	//单词长度
	
	c = fgetc(fp);
	while(!feof(fp)){
		if(IsWordChar(c)){
			//如果是合法的单词字符 
			tempword[len++] = c;
		}
		c = fgetc(fp);
		//跳过单词前的非法字符，或以非法字符结束一个单词
		if(len&&!IsWordChar(c)){
			break
		} 
	} 
	tempword[len] = '\0';	//设定字符串结束符
	if(len>KEYLENGTH){
		//太长的单词被截断
		tempword[KEYLENGTH] = '\0';
		len = KEYLENGTH; 
	} 
	strcpy(word, tempword);
	return len;
} 

//显示词频超过给定的比例的所有单词
void Show(HashTable H, double percent){
	int diffwordcount = 0;	//不同的单词数量
	int maxf = 0;	//最大的词频
	int *diffwords;	//每个词频对应的不同单词数量
	int maxCollision = 0;	//最大冲突次数（单链表长度），初始化为零 
	int minCollision = 100;	//最小冲突次数，初始化为100
	Position L;
	int i, j, k, lowerbound, count=0;
	
	for(i=0; i<H->TableSize; i++){
		//求不同单词的数量
		diffwordcount += H->Heads[i].Count;	//头结点Count统计链表长度
		//统计最大和最小的冲突次数
		if(maxCollision<H->Heads[i].Count){
			maxCollision = H->Heads[i].Count;
		} 
		if(minCollision>H->Heads[i].Count){
			minCollision = H->Heads[i].Count;
		}
		//求最大的词频
		L = H->Heads[i].Next;	//从每个链表的表头开始
		while(L){
			//遍历链表
			if(maxf<L->Count){
				maxf = L->Count;
				L = L->Next;
			} 
		} 
	} 
	
	printf("共有%d个不同的单词，词频最大的是%d；\n", diffwordcount, maxf);
	printf("最大冲突次数是%d，最小冲突次数是%d。\n", maxCollision, minCollision);
	
	//求每个词频等级拥有的不同单词数量 
	//根据最大的词频，分配一个整数数组
	diffwords = (int *)malloc((maxf+1)*sizeof(int));
	//统计词频1到maxf的单词数量
	for(i=0; i<=maxf; i++){
		diffwords[i] = 0;
	} 
	for(i=0; i<H->TableSize; i++){
		L = H->Heads[i].Next;
		while(L){
			//遍历链表
			diffwords[L->Count]++;	//该词频增加一个单词
			L = L->Next; 
		}
	}
	
	//求特定的词频，使得大于等于该词频的单词总和超过特定的比例
	lowerbound = (int)(diffwordcount *percent);
	for(i=maxf; i>=1&&count<lowerbound; i--){
		count += diffwords[i];
	} 
	//按词频从大到小输出单词
	for(j=maxf; j>=i; j--){
		//对每个词频
		for(k=0; k<H->TableSize; k++){
			//遍历整个散列表
			L = H->Heads[k].Next;
			while(L){
				if(j==L->Count){
					//发现一个单词的词频与当前词频相等，输出该单词以及词频 
					 printf("%-15s:%d\n", L->Data, L->Count); 
				}
				L = L->Next;
			} 
		} 
	} 
	free(diffwords);
} 
