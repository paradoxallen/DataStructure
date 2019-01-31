#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> 
#include <stdbool.h>

#define MAXOP 100 /*max length*/
#define INFINITY 1e9 /*infinite*/
#define ERROR -1
typedef double ElementType; 
typedef enum {num, opr, end
} Type;

typedef int Position;
typedef struct SNode *PtrToSNode;
struct SNode {
	ElementType *Data;
	Position Top;
	int MaxSize;
};
typedef PtrToSNode Stack;

Stack CreateStack( int MaxSize ) {
	Stack S = (Stack)malloc(sizeof(struct SNode));
	S->Data = (ElementType *)malloc(MaxSize * sizeof(ElementType));
	S->Top = -1;
	S->MaxSize = MaxSize;
	return S;
}

bool IsFull(Stack S){
	return(S->Top==S->MaxSize-1);
}

bool Push(Stack S, ElementType X){
	if(IsFull){
		printf("Stack is full.");
		return false;
	}
	else{
		S->Data[++(S->Top)] = X;
		return true;
	}
}

bool IsEmpty(Stack S){
	return(S->Top==-1);
}

bool Pop(Stack S){
	if(IsEmpty){
		printf("Stack is Empty.");
		return ERROR;
	}
	else{
		return S->Data[(S->Top)--];
	}
}

Type GetOp(char *Expr, int *start, char *str){
	int i = 0;
	
	while((str[0] = Expr[(*start)++])==' '); /*ignore empty*/
	
	while(str[i]!=' ' && str[i]!='\0'){
		str[++i] = Expr[(*start)++];
	}
	if(str[i]=='\0'){
		(*start)--; /*end*/
	}
	str[i]='\0';
	
	if(i==0){
		return end;
	}
	else if(isdigit(str[0]) || isdigit(str[1])){
		return num;
	}
	else{
		return opr;
	}
} 

ElementType PostfixExp(char *Expr){
	Stack S;
	Type T;
	ElementType Op1, Op2;
	char str[MAXOP];
	int start = 0;
	
	/*apply new stack*/
	S = CreateStack(MAXOP);
	
	Op1 = Op2 = 0;
	while((T=GetOp(Expr, &start, str))!=end) {
		if(T==num){
			Push(S, atof(str));
		}
		else{
			if(!IsEmpty(S)){
				Op2 = Pop(S);
			}
			else{
				Op2 = INFINITY;
			} 
			
			if(!IsEmpty(S)){
				Op1 = Pop(S);
			}
			else{
				Op2 = INFINITY;
			}
			
			switch(str[0]) {
				case '+':{
					Push(S, Op1+Op2);
					break;
				}
				case '*':{
					Push(S, Op1*Op2);
					break;
				}
				case '-':{
					Push(S, Op1-Op2);
					break;
				}
				case '/':{
					if(Op2!=0.0){
						Push(S, Op1/Op2);
					}
					else{
						printf("Error:divide 0 \n");
						Op2 = INFINITY;
					}
					break;
				}
				default:{
					printf("Error:Unknown operation%s \n", str);
					Op2 = INFINITY;
					break;
				}	
			}
			
			if(Op2 >= INFINITY){
				break;
			}
		}
	}
	
	if(Op2<INFINITY){
		if(!IsEmpty(S)){
			Op2=Pop(S);
		}
		else{
			Op2=INFINITY;
		}
	} 
	free(S);
	return Op2;
} 

int main(){
	char Expr[MAXOP];
	ElementType f;
	
	gets(Expr);
	f = PostfixExp(Expr);
	if(f<INFINITY){
		printf("%.4f \n", f);
	}
	else{
		printf("Expression Error. \n");
	}
	
	return 0;
}
