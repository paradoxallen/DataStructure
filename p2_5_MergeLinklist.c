#include <stdio.h>

List Merge( List L1, List L2){
	List L = (List)malloc(sizeof(struct Node)); //申请新链 
	List p1, p2, p;
	p1 = L1->Next;
	p2 = L2->Next; 
	p = L;
	
	while(p1 && p2){
		//比较复制元素 
		if(p1->Data<=p2->Data){
			p->Next = p1;
			p = p1;
			p1 = p1->Next;
		}
		else{
			p->Next = p2;
			p = p2;
			p2 = p2->Next;
		}
	} 
	
	p->Next=p1?p1:p2;          ///将非空链表的剩余段插入到pc所指节点后
    L1->Next=NULL; ///这里是根据题目要求输出合并后原链表的头结点所添加的。
    L2->Next=NULL; //
    return L;
}
