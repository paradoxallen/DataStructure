//�����Ŷ�����

//1.�����жര�ڷ���������K�������ṩ�������й˿Ͱ�����ʱ���Ŷӣ����д��ڿ���ʱ����һλ�˿ͼ�ȥ�ô��ڴ������� 
//�����жര�ڷ���ģ����ж���
typedef struct People ElementType;
struct People{
	//�˿�����
	int T;	//�˿͵���ʱ�� 
	int P; 	//�˿����ﱻ�����ʱ�� 
};

typedef int Position;
struct QNode{
	//���н�� 
	ElementType *Data;	//�˿�����
	Position Front, Rear;	//���е�ͷ��βָ��
	int MaxSize;	//����������� 
};
typedef struct QNode *Queue;

 
Queue CreateQueue(int MaxSize){
	Queue Q = (Queue)malloc(sizeof(struct QNode));
	Q->Data = (ElementType *)malloc(MaxSize*sizeof(ElementType));
	Q->Front = Q->Rear = 0;
	Q->MaxSize = MaxSize;
	return Q;
}

bool IsFull(Queue Q){
	return((Q->Rear+1)%Q->MaxSize==Q->Front);
}

bool AddQ(Queue Q, ElementType X){
	if(IsFull(Q)){
		printf("��������");
		return false;
	}
	else{
		Q->Rear = (Q->Rear+1)%Q->MaxSize;
		Q->Data[Q->Rear] = X;
		return true;
	}
}

bool IsEmpty(Queue Q){
	return(Q->Front == Q->Rear);
}

ElementType DeleteQ(Queue Q){
	if(IsEmpty(Q)){
		printf("���пա�");
		return ERROR; 
	}
	else{
		Q->Front = (Q->Front+1)%Q->MaxSize;
		return Q->Data[Q->Front];
	}
}

//�����жര�ڷ���ģ�������� 
int main(){
	int N;	//�˿�����
	Queue Q;	//�˿Ͷ���
	int i;
	ElementType X;
	
	scanf("%d", &N);	//��ȡ�˿�����
	Q = CreateQueue(N);	//�����յĹ˿Ͷ���
	
	for(i=0; i<N; i++){
		//�˿���������
		scanf("%d%d", &X.T, &X.P);
		AddQ(Q, X); 
	} 
	
	//��ӡ��Nλ�˿͵�ƽ���ȴ�ʱ��
	printf("Average waiting time = %.If minute(s). \n", QueueingAtBank(Q, N));
	
	DestroyQueue(Q);
	return 0; 
}

//�����жര�ڷ���ģ����Ĵ����� 
double QueueAtBank(Queue Q, int N){
	//���ݹ˿Ͷ���Q������N�����ع˿�ƽ���ȴ�ʱ��
	struct People Next;	//��һλ�˿�
	int K;	//Ӫҵ���ڸ���
	int TotalTime;	//ȫ��˿͵ȴ���ʱ��
	int CurrentTime;	//��ǰʱ�䣬����ӪҵʱΪ0
	int Window[MaxWindow];	//Ӫҵ������Ҫ���������ʱ�䳤��
	int WaitTime;	//�������δ��ڿ���֮����Ҫ�ȴ���ʱ��
	int WinAvail;	//���д��ڵ�λ��
	int i, j;
	
	scanf("%d", &K);	//����Ӫҵ���ڸ���
	if(N<K) return 0;	//���ڱ�����������ȴ�
	
	//��ʼ��
	for(i=0; i<K; i++){
		Window[i] = 0;
	} 
	TotalTime = 0;
	//
	
	while(!IsEmpty(Q)){
		//�����зǿգ���������
		
		//��һ�����������ǰ��̵����񣬵õ���һ�����д���
		WinAvail = FindNextWindow(Window, K, &WaitTime);
		CurrentTime += WaitTime;
		
		//�ڶ�������һλ�˿ͳ���
		Next = DeleteQ(Q);
		if(CurrentTime >= Next.T){
			//����˿��Ѿ�����ȴ�
			TotalTime += CurrentTime - Next.T;	//�ۼƵȴ�ʱ�� 
		} 
		else{
			//����˿ͻ�û��
			WaitTime = Next.T - CurrentTime;	//���д��ڵȴ��˿͵�ʱ��
			for(j=0; j<K; j++){
				//ˢ�����д������˿͵����״̬ 
				Window[j] -= WaitTime;
				if(Window[j]<0){
					Window[j] = 0;
				}
			}
			CurrentTime = Next.T;	//���µ�ǰʱ��Ϊ�˿͵���ʱ��  
		}
		
		//���������˿�Next��WinAvail���ڽ���ҵ��
		Window[WinAvail] = Next.P; 
	}
	
	//����ÿλ�˿͵�ƽ���ȴ�ʱ��
	return((double)TotalTime/(double)N); 
}

//�����жര�ڷ���ģ��FindNextWindow����
int FindNextWindow(int W[], int K, int *WaitTime){
	//����K������W[]��״̬��������һ�����д��ڵ�λ��
	//�Լ����������δ��ڿ���֮�����ȴ���ʱ��WaitTime
	int WinAvail;	//��һ�����д��ڵ�λ��
	int MinW = MaxProc+1;	//���������ʱ�䣬��ʼ��Ϊ�������ֵ
	int i;
	
	for(i=0; i<K; i++){
		//ɨ��ÿ�����ڣ��ҵ��������
		if(W[i]<MinW){
			MinW = W[i];
			WinAvail = i;
		} 
	} 
	*WaitTime = MinW;	//���������ʱ��������οմ���ĵȴ�ʱ��
	for(i=0; i<k; i++){
		W[i] - MinW;	//ˢ�����д��ڵ�������״̬ 
	} 
	
	return WinAvail;	//������һ���մ���λ�� 
} 


//2.�����жര��+VIP���񣺵�����û��VIP�ͻ�ʱ��VIP����Ϊ��ͨ�˿ͷ��񣻵�VIP���ڿ����Ҷ�������VIP�ͻ��ȴ�ʱ��������ǰ���VIP�ͻ����ܸô��ڵķ���
//ͬʱ�����ֵ�ĳVIP���ڳ���ʱ����VIP���ڷǿգ��ÿͻ�����ѡ����е���ͨ���� 
//�����жര��+VIP����ģ����ж���
typedef struct People ElementType;
struct People{
	//�˿�����
	int T;	//�˿͵���ʱ�� 
	int P; 	//�˿����ﱻ�����ʱ�� 
	int VIP;	//VIP��־��1VIP��0��ͨ��-1ɾ�� 
};

typedef int Position;
struct QNode{
	//���н�� 
	ElementType *Data;	//�˿�����
	Position Front, Rear;	//���е�ͷ��βָ��
	int MaxSize;	//����������� 
	//������VIP���ж�ӦԪ��
	Position VIPFront, VIPRear;
	int *VIPCustomer;
	int *VIPSize;	//������VIP������ 
};
typedef struct QueueRecord *Queue;

bool VIPIsFull(Queue Q);
bool AddVIP(Queue Q);
bool VIPIsEmpty(Queue Q);
ElementType DeleteVIP(Queue Q);

Queue CreateQueue(int MaxSize);
bool IsFull(Queue Q);
bool AddQ(Queue Q);
bool IsEmpty(Queue Q);
ElementType DeleteQ(Queue Q);

//�����жര��+VIP����ģ����Ĵ�����
double QueueAtBank(Queue Q, int N){
	//���ݹ˿Ͷ���Q������N�����ع˿�ƽ���ȴ�ʱ��
	struct People Next;	//��һλ�˿�
	int K;	//Ӫҵ���ڸ���
	int TotalTime;	//ȫ��˿͵ȴ���ʱ��
	int CurrentTime;	//��ǰʱ�䣬����ӪҵʱΪ0
	int Window[MaxWindow];	//Ӫҵ������Ҫ���������ʱ�䳤��
	int WaitTime;	//�������δ��ڿ���֮����Ҫ�ȴ���ʱ��
	int WinAvail;	//���д��ڵ�λ��
	int i, j;
	
	int VIPWindow;	//VIP���ڱ�� 
	
	scanf("%d%d", &K, &VIPWindow);	//����Ӫҵ���ڸ�����VIP���ڱ�� 
	if(N<K) return 0;	//���ڱ�����������ȴ�
	
	//��ʼ��
	for(i=0; i<K; i++){
		Window[i] = 0;
	} 
	TotalTime = 0;
	//
	
	while(!IsEmpty(Q)){
		//�����зǿգ���������
		
		//��һ�����������ǰ��̵����񣬵õ���һ�����д���
		WinAvail = FindNextWindow(Window, K, &WaitTime);
		CurrentTime += WaitTime;
		
		//�ڶ�������һλ�˿ͳ���
		if((WinAvail==VIPWindow)&&(IsVipHere(Q, CurrentTime))){
			Next = DeleteVIP(Q);	//���VIP���ڿ�����VIP�ڶ����� 
		} 
		else{
			Next = DeleteQ(Q);	
		} 
		if(Next.T==EmptyQ){
			break;	//����յ������ѿյ��źţ��˳�ѭ�� 
		}
		
		if(CurrentTime >= Next.T){
			//����˿��Ѿ�����ȴ�
			TotalTime += CurrentTime - Next.T;	//�ۼƵȴ�ʱ�� 
		} 
		else{
			//����˿ͻ�û��
			WaitTime = Next.T - CurrentTime;	//���д��ڵȴ��˿͵�ʱ��
			for(j=0; j<K; j++){
				//ˢ�����д������˿͵����״̬ 
				Window[j] -= WaitTime;
				if(Window[j]<0){
					Window[j] = 0;
				}
			}
			CurrentTime = Next.T;	//���µ�ǰʱ��Ϊ�˿͵���ʱ��  
		}
		
		//���������˿�Next��WinAvail���ڽ���ҵ��
		Window[WinAvail] = Next.P; 
	}
	
	//����ÿλ�˿͵�ƽ���ȴ�ʱ��
	return((double)TotalTime/(double)N); 
}

//�����жര�ڷ���ģ��FindNextWindow����
int FindNextWindow(int W[], int K, int *WaitTime){
	//����K������W[]��״̬��������һ�����д��ڵ�λ��
	//�Լ����������δ��ڿ���֮�����ȴ���ʱ��WaitTime
	int WinAvail;	//��һ�����д��ڵ�λ��
	int MinW = MaxProc+1;	//���������ʱ�䣬��ʼ��Ϊ�������ֵ
	int i;
	
	for(i=0; i<K; i++){
		//ɨ��ÿ�����ڣ��ҵ��������
		if(W[i]<MinW){
			MinW = W[i];
			WinAvail = i;
		} 
	} 
	*WaitTime = MinW;	//���������ʱ��������οմ���ĵȴ�ʱ��
	for(i=0; i<k; i++){
		W[i] - MinW;	//ˢ�����д��ڵ�������״̬ 
	} 
	
	return WinAvail;	//������һ���մ���λ�� 
} 

//�����жര��+VIP����ģ��DeleteQ����
bool VIPIsEmpty(Queue Q){
	return(Q->VIPSize==0);
} 

ElementType DeleteVIP(Queue Q){
	//��VIP���ж��׵Ŀͻ�����
	ElementType X;
	Position P;
	
	if(!VIPIsEmpty(Q)){
		//�������VIP�ͻ�
		//��ö��׿ͻ��ڹ˿Ͷ����е�λ��
		P = Q->VIPCustomer[Q->VIPFront];
		//����λ�ô�VIP������ɾ��
		Q->VIPFront++;
		Q->VIPSize--;
		Q->Data[P].VIP = -1;	//����ɾ���˿Ͷ����е�VIP
		X.T = Q->Data[P].T;
		X.P = Q->Data[P].P; 
	} 
	else{
		//���û��VIP�ͻ���������ͨ����
		X = DeleteQ(Q); 
	}
	return X;
}

#define EmptyQ -1	//���пյ��ź�
ElementType DeleteQ(Queue Q){
	//��Q���׵Ĺ˿ͳ���
	ElementType X;
	
	//��λ�ڶ���ǰ�˵ı�����ɾ���Ĺ˿�����ɾ��
	while(Q->Data[Q->Front].VIP = -1){
		Q->Front++;
	} 
	if(IsEmpty(Q)){
		//���������ֶ����ѿգ����ؿ��ź�
		X.T = EmptyQ;
		return X; 
	}
	if(Q->Data[Q->Front].VIP = 1){
		X.DeleteVIP(Q);	//����׵�VIP�ͻ����� 
	}
	else{
		//��ͨ�˿ͳ���
		X.T = Q->Data[Q->Front].T;
		X.P = Q->Data[Q->Front].P; 
	}
	//ɾ�����׵Ĺ˿�
	Q->Front++;
	return X; 
	
} 
