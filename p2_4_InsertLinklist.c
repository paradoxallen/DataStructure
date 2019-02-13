#include <stdio.h>

List Insert( List L, ElementType X ){
	List head = L; //头结点
	L = L->Next;   //转到第一个节点 
	List p = (List)malloc(sizeof(struct Node)); //申请新结点 储存X值 
	p->Data = X;
	p->Next = NULL; 
	List q = head; //初始为头结点
	
	if(L==NULL){ //空链表 
		head->Next = p;
		return head;
	} 
	
	while(L->Data < X){
		q = L;
		L = L->Next;
		if(L->Next == NULL){  //链表尾 
			L->Next = p;
			return head; 
		} 
	} 
	p->Next = L;//插在中间 
	q->Next = p;
	return head;
} 
