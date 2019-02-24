//银行排队问题

//1.单队列多窗口服务：银行有K个窗口提供服务，所有顾客按到达时间排队，当有窗口空闲时，下一位顾客即去该窗口处理事务 
//单队列多窗口服务模拟队列定义
typedef struct People ElementType;
struct People{
	//顾客类型
	int T;	//顾客到达时间 
	int P; 	//顾客事物被处理的时间 
};

typedef int Position;
struct QNode{
	//队列结点 
	ElementType *Data;	//顾客数组
	Position Front, Rear;	//队列的头，尾指针
	int MaxSize;	//队列最大容量 
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
		printf("队列满。");
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
		printf("队列空。");
		return ERROR; 
	}
	else{
		Q->Front = (Q->Front+1)%Q->MaxSize;
		return Q->Data[Q->Front];
	}
}

//单队列多窗口服务模拟主函数 
int main(){
	int N;	//顾客总数
	Queue Q;	//顾客队列
	int i;
	ElementType X;
	
	scanf("%d", &N);	//读取顾客人数
	Q = CreateQueue(N);	//建立空的顾客队列
	
	for(i=0; i<N; i++){
		//顾客依次入列
		scanf("%d%d", &X.T, &X.P);
		AddQ(Q, X); 
	} 
	
	//打印出N位顾客的平均等待时间
	printf("Average waiting time = %.If minute(s). \n", QueueingAtBank(Q, N));
	
	DestroyQueue(Q);
	return 0; 
}

//单队列多窗口服务模拟核心处理函数 
double QueueAtBank(Queue Q, int N){
	//根据顾客队列Q和人数N，返回顾客平均等待时间
	struct People Next;	//下一位顾客
	int K;	//营业窗口个数
	int TotalTime;	//全体顾客等待中时间
	int CurrentTime;	//当前时间，开门营业时为0
	int Window[MaxWindow];	//营业窗口需要处理事务的时间长度
	int WaitTime;	//相邻两次窗口空闲之间所要等待的时间
	int WinAvail;	//空闲窗口的位置
	int i, j;
	
	scanf("%d", &K);	//读入营业窗口个数
	if(N<K) return 0;	//窗口比人数多无需等待
	
	//初始化
	for(i=0; i<K; i++){
		Window[i] = 0;
	} 
	TotalTime = 0;
	//
	
	while(!IsEmpty(Q)){
		//单队列非空，持续操作
		
		//第一步：处理掉当前最短的事务，得到下一个空闲窗口
		WinAvail = FindNextWindow(Window, K, &WaitTime);
		CurrentTime += WaitTime;
		
		//第二步：下一位顾客出列
		Next = DeleteQ(Q);
		if(CurrentTime >= Next.T){
			//如果顾客已经到达等待
			TotalTime += CurrentTime - Next.T;	//累计等待时间 
		} 
		else{
			//如果顾客还没到
			WaitTime = Next.T - CurrentTime;	//空闲窗口等待顾客的时间
			for(j=0; j<K; j++){
				//刷新所有窗口至顾客到达的状态 
				Window[j] -= WaitTime;
				if(Window[j]<0){
					Window[j] = 0;
				}
			}
			CurrentTime = Next.T;	//更新当前时间为顾客到达时间  
		}
		
		//第三步：顾客Next到WinAvail窗口接受业务
		Window[WinAvail] = Next.P; 
	}
	
	//返回每位顾客的平均等待时间
	return((double)TotalTime/(double)N); 
}

//单队列多窗口服务模拟FindNextWindow函数
int FindNextWindow(int W[], int K, int *WaitTime){
	//给定K个窗口W[]的状态，返回下一个空闲窗口的位置
	//以及在相邻两次窗口空闲之间所等待的时间WaitTime
	int WinAvail;	//下一个空闲窗口的位置
	int MinW = MaxProc+1;	//最短事务处理时间，初始化为超过最大值
	int i;
	
	for(i=0; i<K; i++){
		//扫描每个窗口，找到最短事物
		if(W[i]<MinW){
			MinW = W[i];
			WinAvail = i;
		} 
	} 
	*WaitTime = MinW;	//最短事务处理时间就是两次空窗间的等待时间
	for(i=0; i<k; i++){
		W[i] - MinW;	//刷新所有窗口的事务处理状态 
	} 
	
	return WinAvail;	//返回下一个空窗的位置 
} 


//2.单队列多窗口+VIP服务：当队列没有VIP客户时，VIP窗口为普通顾客服务；当VIP窗口空闲且队列中有VIP客户等待时，排在最前面的VIP客户享受该窗口的服务。
//同时，当轮到某VIP窗口出列时，若VIP窗口非空，该客户可以选择空闲的普通窗口 
//单队列多窗口+VIP服务模拟队列定义
typedef struct People ElementType;
struct People{
	//顾客类型
	int T;	//顾客到达时间 
	int P; 	//顾客事物被处理的时间 
	int VIP;	//VIP标志：1VIP，0普通，-1删除 
};

typedef int Position;
struct QNode{
	//队列结点 
	ElementType *Data;	//顾客数组
	Position Front, Rear;	//队列的头，尾指针
	int MaxSize;	//队列最大容量 
	//下列是VIP子列对应元素
	Position VIPFront, VIPRear;
	int *VIPCustomer;
	int *VIPSize;	//队列中VIP的数量 
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

//单队列多窗口+VIP服务模拟核心处理函数
double QueueAtBank(Queue Q, int N){
	//根据顾客队列Q和人数N，返回顾客平均等待时间
	struct People Next;	//下一位顾客
	int K;	//营业窗口个数
	int TotalTime;	//全体顾客等待中时间
	int CurrentTime;	//当前时间，开门营业时为0
	int Window[MaxWindow];	//营业窗口需要处理事务的时间长度
	int WaitTime;	//相邻两次窗口空闲之间所要等待的时间
	int WinAvail;	//空闲窗口的位置
	int i, j;
	
	int VIPWindow;	//VIP窗口编号 
	
	scanf("%d%d", &K, &VIPWindow);	//读入营业窗口个数和VIP窗口编号 
	if(N<K) return 0;	//窗口比人数多无需等待
	
	//初始化
	for(i=0; i<K; i++){
		Window[i] = 0;
	} 
	TotalTime = 0;
	//
	
	while(!IsEmpty(Q)){
		//单队列非空，持续操作
		
		//第一步：处理掉当前最短的事务，得到下一个空闲窗口
		WinAvail = FindNextWindow(Window, K, &WaitTime);
		CurrentTime += WaitTime;
		
		//第二步：下一位顾客出列
		if((WinAvail==VIPWindow)&&(IsVipHere(Q, CurrentTime))){
			Next = DeleteVIP(Q);	//如果VIP窗口空且有VIP在队伍中 
		} 
		else{
			Next = DeleteQ(Q);	
		} 
		if(Next.T==EmptyQ){
			break;	//如果收到队列已空的信号，退出循环 
		}
		
		if(CurrentTime >= Next.T){
			//如果顾客已经到达等待
			TotalTime += CurrentTime - Next.T;	//累计等待时间 
		} 
		else{
			//如果顾客还没到
			WaitTime = Next.T - CurrentTime;	//空闲窗口等待顾客的时间
			for(j=0; j<K; j++){
				//刷新所有窗口至顾客到达的状态 
				Window[j] -= WaitTime;
				if(Window[j]<0){
					Window[j] = 0;
				}
			}
			CurrentTime = Next.T;	//更新当前时间为顾客到达时间  
		}
		
		//第三步：顾客Next到WinAvail窗口接受业务
		Window[WinAvail] = Next.P; 
	}
	
	//返回每位顾客的平均等待时间
	return((double)TotalTime/(double)N); 
}

//单队列多窗口服务模拟FindNextWindow函数
int FindNextWindow(int W[], int K, int *WaitTime){
	//给定K个窗口W[]的状态，返回下一个空闲窗口的位置
	//以及在相邻两次窗口空闲之间所等待的时间WaitTime
	int WinAvail;	//下一个空闲窗口的位置
	int MinW = MaxProc+1;	//最短事务处理时间，初始化为超过最大值
	int i;
	
	for(i=0; i<K; i++){
		//扫描每个窗口，找到最短事物
		if(W[i]<MinW){
			MinW = W[i];
			WinAvail = i;
		} 
	} 
	*WaitTime = MinW;	//最短事务处理时间就是两次空窗间的等待时间
	for(i=0; i<k; i++){
		W[i] - MinW;	//刷新所有窗口的事务处理状态 
	} 
	
	return WinAvail;	//返回下一个空窗的位置 
} 

//单队列多窗口+VIP服务模拟DeleteQ函数
bool VIPIsEmpty(Queue Q){
	return(Q->VIPSize==0);
} 

ElementType DeleteVIP(Queue Q){
	//令VIP子列队首的客户出列
	ElementType X;
	Position P;
	
	if(!VIPIsEmpty(Q)){
		//如果存在VIP客户
		//获得队首客户在顾客队列中的位置
		P = Q->VIPCustomer[Q->VIPFront];
		//将该位置从VIP子列中删除
		Q->VIPFront++;
		Q->VIPSize--;
		Q->Data[P].VIP = -1;	//懒惰删除顾客队列中的VIP
		X.T = Q->Data[P].T;
		X.P = Q->Data[P].P; 
	} 
	else{
		//如果没有VIP客户，则做普通出列
		X = DeleteQ(Q); 
	}
	return X;
}

#define EmptyQ -1	//队列空的信号
ElementType DeleteQ(Queue Q){
	//令Q队首的顾客出列
	ElementType X;
	
	//将位于队列前端的被懒惰删除的顾客真正删除
	while(Q->Data[Q->Front].VIP = -1){
		Q->Front++;
	} 
	if(IsEmpty(Q)){
		//如果清除后发现队列已空，返回空信号
		X.T = EmptyQ;
		return X; 
	}
	if(Q->Data[Q->Front].VIP = 1){
		X.DeleteVIP(Q);	//令队首的VIP客户出列 
	}
	else{
		//普通顾客出列
		X.T = Q->Data[Q->Front].T;
		X.P = Q->Data[Q->Front].P; 
	}
	//删除队首的顾客
	Q->Front++;
	return X; 
	
} 
