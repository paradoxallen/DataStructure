#include <stdio.h>

List Merge( List L1, List L2){
	List L = (List)malloc(sizeof(struct Node)); //�������� 
	List p1, p2, p;
	p1 = L1->Next;
	p2 = L2->Next; 
	p = L;
	
	while(p1 && p2){
		//�Ƚϸ���Ԫ�� 
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
	
	p->Next=p1?p1:p2;          ///���ǿ������ʣ��β��뵽pc��ָ�ڵ��
    L1->Next=NULL; ///�����Ǹ�����ĿҪ������ϲ���ԭ�����ͷ�������ӵġ�
    L2->Next=NULL; //
    return L;
}
