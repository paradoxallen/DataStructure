#include <stdio.h>

List Insert( List L, ElementType X ){
	List head = L; //ͷ���
	L = L->Next;   //ת����һ���ڵ� 
	List p = (List)malloc(sizeof(struct Node)); //�����½�� ����Xֵ 
	p->Data = X;
	p->Next = NULL; 
	List q = head; //��ʼΪͷ���
	
	if(L==NULL){ //������ 
		head->Next = p;
		return head;
	} 
	
	while(L->Data < X){
		q = L;
		L = L->Next;
		if(L->Next == NULL){  //����β 
			L->Next = p;
			return head; 
		} 
	} 
	p->Next = L;//�����м� 
	q->Next = p;
	return head;
} 
