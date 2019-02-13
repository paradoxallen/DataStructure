//�ڽӾ����ʾ��
#define MaxVertexNum 100
#define INFINITY 65535
typedef int Vertex;
typedef int WeightType;
typedef char DataType;


typedef struct GNode *PtrToGNode;  //ͼ�ڵ�Ķ���
struct GNode{
	int Nv;  //������ 
	int Ne;  //����
	WeightType G[MaxVertexNum][MaxVertexNum];  //�ڽӾ���
	DataType Data[MaxVertexNum]; //�涥������� 
	//�����������ݣ���ʱData[]���Բ��ó��� 
}; 
typedef PtrToGNode MGraph;


//�ڽӾ����ʾ--������ͼ�ĳ�ʼ������
typedef struct ENode *PtrToENode  //�ߵĶ���
struct ENode{
	Vertex V1, V2;  //�����
	WeightType Weight; // Ȩ�� 
}; 
typedef PtrToENode Edge;

MGraph CreateGraph(int VertexNum){
	//��ʼ��һ���ж���û�бߵ�ͼ
	Vertex V, W;
	MGraph Graph;
	
	Graph = (MGraph)malloc(sizeof(struct GNode));
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	
	//��ʼ���ڽӾ���Ĭ�϶����0��ʼ
	for(V=0; V<Graph->Nv; V++){
		for(W=0; W<Graph->Nv; W++){
			Graph->G[V][W] = INFINITY;
		}
	} 
	
	return Graph;
}

void InsertEdge(MGraph, Edge E){
	Graph->G[E->V1][E->V2] = E->Weight;
	Graph->G[E->V2][E->V1] = E->Weight;//��������ͼ 
}
 

MGraph BuildGraph(){
	MGraph Graph;
	Edge E;
	Vertex V;
	int Nv, i;
	
	scanf("%d", &Nv);
	Graph = CreateGraph(Nv);
	
	scanf("%d", &(Graph->Ne));
	if(Graph->Ne != 0){
		E = (Edge)malloc(sizeof(struct ENode));
		for(i=0; i<Graph->Ne; i++){
			scanf("%d%d%d", &E->V1, &E->V2, &E->Weight);
			InsertEdge(Graph, E);
		}
	} 
	
	for(V=0; V<Graph->Nv; V++){
		scanf("%c", &(Graph->Data[V]));
	}
	
	return Graph;
} 


//�ڽӱ��ʾ��
#define MaxVertexNum 100
typedef int Vertex;
typedef int WeightType;
typedef char DataType;

typedef struct ENode *PtrToENode; //�ߵĶ���
struct ENode{
	Vertex V1, V2;
	WeightType Weight;
}; 
typedef PtrToENode Edge;

typedef struct AdjVNode *PtrToAdjVNode; //�ڽӵ�Ķ��� 
struct AdjVNode{
	Vertex AdjV; //�ڽӵ��±�
	WeightType Weight;
	PtrToAdjVNode Next; 
};

typedef struct Vnode{
	//�����ͷ��㶨��
	PtrToAdjVNode FirstEdge;
	DataType Data; //ע��ܶ�����¶��㣬��ʱdata�ɲ����� 
} AdjList[MaxVertexNum];

typedef struct GNode *PtrToGNode; //ͼ�ڵ�Ķ���
struct GNode{
	int Nv;
	int Ne;
	AdjList G; //�ڽӱ� 
}; 
typedef PtrToGNode Lgraph;


//�ڽӱ��ʾ--����ͼ�ĳ�ʼ��
LGraph CreateGraph(int VertexNum){
	//��ʼ���ж����ޱߵ�ͼ 
	Vertex V;
	LGraph Graph;
	
	Graph = (LGraph)malloc(sizeof(struct GNode));
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	
	//��ʼ���ڽӱ�ͷָ��
	for(V=0; V<Graph->Nv; V++){
		Graph->G[V].FirstEdge = NULL;
	} 
	return Graph;
} 

void InsertEdge(LGraph Graph, Edege E){
	PtrToAdjVNode NewNode;
	
	//����<V1,V2>
	//ΪV2�����µ��ڽӵ� 
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->V2;
	NewNode->Weight = E->Weight; 
	//V2����V1�ı�ͷ
	NewNode->Next = Graph->G[E->V1].FirstEdge;
	Graph->G[E->V1].FisrtEdge = NewNode;
	
	//��������ͼ����Ҫ����<V2,V1> 
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->V1;
	NewNode->Weight = E->Weight; 
	//V2����V1�ı�ͷ
	NewNode->Next = Graph->G[E->V2].FirstEdge;
	Graph->G[E->V2].FisrtEdge = NewNode;
}

LGraph BuildGraph(){
	LGraph Graph;
	Edge E;
	Vertex V;
	int Nv, i;
	
	scanf("%d", &Nv);
	Graph = CreateGraph(Nv);
	
	scanf("%d", &(Graph->Ne));
	if(Graph->Ne != 0){
		E = (Edge)malloc(sizeof(struct ENode));
		for(i=0; i<Graph->Ne; i++){
			scanf("%d%d%d", &E->V1, &E->V2, &E->Weight);
			InsertEdge(Graph, E);
		}
	} 
	
	for(V=0; V<Graph->Nv; V++){
		scanf("%c", &(Graph->G[V].Data));
	}
	
	return Graph;
}

//�ڽӱ��������ȱ���
void Visit(Vertex V){
	printf("���ڷ��ʶ���%d\n", V);
} 
//Visited[]Ϊȫ�ֱ������Ѿ���ʼ��Ϊfalse
void DFS(LGraph Graph, Vertex V, void(*Visit)(Vertex)){
	//��V�������DFS
	 PtrToAdjVNode W;
	 
	 Visit(V);
	 Visited[V] = true;
	 
	 for(W=Graph->G[V].FirstEdge; W; W=W->Next){
	 	if(!Visited[W->AdjV])
	 }
} 


//�ڽӾ��󴢴�ͼ�Ĺ�����ȱ���
bool IsEdge(MGraph Graph, Vertex V, Vertex W){
	return Graph->G[V][M]<INFINITY?true:false;
} 

void BFS(MGraph Graph, Vertex S, void(*Visit)(Vertex)){
	Queue Q;
	Vertex V, W;
	
	Q = CreateQueue(MaxSize);
	
	Visit(S);
	Visited[S] = true;
	AddQ(Q, S);
	
	while(!IsEmpty(Q)){
		V = DeleteQ(Q);
		for(W=0; W<Graph->Nv, W++){
			if(!Visited[W] && IsEdge(Graph, V, W)){
				Visit(W);
				Visited[W] = true;
				AddQ(Q, W);
			}
		}
	}
}


//���·��Dijkstra�㷨 
Vertex FindMinDist(MGraph Graph, int dist[], int collocted[]){
	//����δ����¼�����е���С��
	Vertex MinV, V;
	int MinDist = INFINITY;
	
	for(V=0; V<Graph->Nv; V++){
		if(collected[V]==false &&dist[V]<MinDist){
			MinDist = Dist[V];
			MinV = V;
		}
	}
	if(MinDist<INFINITY){
		return MinV;
	}
	else{
		return ERROR;
	}
}

bool Dijkstra(MGraph Graph, int dist[], int path[], Vertex S){
	int colloected[MaxVertexNum];
	Vertex V, W;
	
	//��ʼ��
	for(V=0; V<Graph->Nv; V++){
		dist[V] = Graph->G[S][V];
		path[V] = -1;
		collected[V] = false;
	} 
	
	//����ս�����
	dist[S] = 0;
	collected[S] = true;
	
	while(1){
		//V=δ���붥����dist��С��
		V = FindMinDist(Graph, dist, collected) ;
		if(V==ERROR){
			break; //��������V�����ڣ��㷨���� 
		}
	} 
	collected[V] = true;
	for(W=0; W<Graph->Nv; W++){
		//��W��V���ڽӵ㲢��δ��¼
		if(collected[W]==false && Graph->G[V][W]<INFINITY){
			if(Graph->G[V][W]<0){
				return false; //���и��ߣ����ش��� 
			}
			if(dist[V]+Graph[V][W] < dist[W]){
				//����¼Vʹ��dist[W]��С 
				dist[W] = dist[V] + Graph->G[V][W]��
				path[W] = V; 
			}
		} 
	} 
	return true;
}


//Floyd�㷨
bool Floyd(MGraph Graph, WeightType D[][MaxVertexNum], Vertex path[][MaxVertexNum]){
	Vertex i, j, k;
	
	//��ʼ��
	for(i=0; i<Graph->Nv; i++){
		for(j=0; j<Graph->Nv; j++){
			D[i][j] = Graph->G[i][j];
			path[i][j] = -1;
		}
	} 
	
	for(k=0; k<Graph->Nv; k++){
		for(i=0; i<Graph->Nv; i++){
			for(j=0; j<Graph->Nv; j++){
				if(D[i][k]+D[k][j]<D[[i][j]){
					D[i][j] = D[i][k]+D[i][j];
					if(i==j && D[i][j]<0){
						return false;
					} 
					path[i][j] = k;
				}
			}
		}
	}
	return true;
} 


//�ڽӾ��󴢴�ͼ��Prim�㷨
#define ERROR -1

int Prim(MGraph Graph, LGraph MST){
	//����С����������Ϊ�ڽӱ��ͼMST��������СȨ��ֵ
	WeightType dist[MaxVertexNum], TotalWeight;
	Vertex parent[MaxVertexNum], V, W;
	int VCount;
	Edge E;
	
	//��ʼ����Ĭ�ϳ�ʼ���±�Ϊ0
	for(V=0; V<Graph->Nv; V++){
		//���ޱ��ⶨ��ΪINFINITY
		dist[V] = Graph->G[0][V];
		parent[V] = 0; //�������и��ڵ㶼��0 
	} 
	TotalWeight = 0; //��ʼ��Ȩ�غ�
	VCount = 0;  //��ʼ����¼�Ķ�����
	
	//�����������ж��㵫û�бߵ�ͼ���ڽӱ�汾
	MST = CreateGraph(Graph->Nv);
	E = (Edge)malloc(sizeof(struct ENode)); //�����յı߽ڵ�
	
	//����ʼ��0��¼��MST
	dist[0] = 0;
	VCount++;
	parent[0] = -1; //���� 
	
	while(1){
		V = FindMinDist(Graph, Dist);
		//V=δ��¼������dist��С��
		if(V==ERROR){
			break;//��������V�����ڣ��㷨���� 
		} 
		
		//��V����Ӧ�ı�<parent[V],V>��¼��MST
		E->V1 = parent[V];
		E->V2 = V;
		E->Weight = dist[V];
		InsertEdge(MST, E);
		TotalWeight += dist[V];
		dist[V] = 0;
		VCount++;
		
		for(W=0; W<Graph->Nv; W++){
			if(dist[W]!=0 && Graph->G[V][W]<INFINTY){
				//��W��V���ٽ�㲢��δ����¼
				if(Graph->G[V][W]<dist[W]){
					//����¼Vʹ��dist[W]��С
					dist[W] = Graph->G[V][W];
					parent[W] = V; 
				} 
			}
		} 
	} 
	if(VCount < Graph->Nv){
		TotalWeight = ERROR;
	}
	
	return TotalWeight;
} 


//Kruskal�㷨��α����
int Kruskal(LGraph Graph, LGraph MST){
	//����С����������Ϊ�ڽӱ����ͼMST��������СȨ�غ�
	MST = �������ж��㵫û�бߵ�ͼ
	while(MST���ռ��ı߲���Graph->Nv-1�� && ԭͼ�ı߼�E�ǿ�){
		��E��ѡ����С���۱�(V, W)��//������С�����
		��E��ɾ���ñ�(V��W)
		if((V, w)��ѡȡ����MST�й��ɻ�·) //���ж��ɲ��鼯��find��� 
			��(V, W)����MST��//�˲��ɲ��鼯��Union���
		else
			���׶���(V, W) 
	} 
	if(MST���ռ��ı߲���Graph->Nv-1��)
		return ERROR;
	else
		return ��СȨ�غ�; 
} 


//���������㷨α����
bool TopSort(Graph Graph, Vertex TopOrder[]){
	//��graph������������TopOrder˳�򴢴������Ķ����±�
	
	//����ͼ���õ�����������Indergree[]
	for(cnt=0; cnt<Graph->Nv; cnt++){
		V = Ϊ��������Ϊ0�Ķ���;
		if(������V������){
			printf("ͼ���л�·");
			break;
		} 
		TopOrder[cnt] = V; //��V��Ϊ������е���һ��Ԫ��
		//��V������ߴ�ͼ��ɾ��
		for(V��ÿ���ڽӵ�W){
			Indegree--; 
		} 
	} 
	if(cnt != Graph->Nv){
		return false; //˵��ͼ���л�·�����ش��� 
	}
	else{
		return true;
	}
} 

//�Ľ�������������㷨
bool TopSort(LGraph Graph, Vertex TopOrder[]) {
	//��graph������������TopOrder˳�򴢴������Ķ����±�
	int Indegree[MaxVertexNum], cnt;
	Vertex V;
	PtrToAdjVNode W;
	Queue Q = CreateQueue(Graph->Nv);
	
	//��ʼ��Indegree[]
	for(V=0; V<Graph->Nv; V++){
		Indegree[V] = 0;
	} 
	
	//����ͼ���õ�Indegree[]
	for(V=0; V<Graph->Nv; V++){
		for(W=Graph->G[V].FirstEdge; W; W=W->Next){
			Indegree[W->AdjV]++; //�������<V�� W->AdjV>�ۼ��յ����� 
		}
	}
	
	//���������Ϊ0�Ķ�������
	for(V=0; V<Graph->Nv; V++){
		if(Indegree[V]==0){
			AddQ(Q, V);
		}
	} 
	
	//���������������
	cnt = 0;
	while(!IsEmpty(Q)){
		V = DeleteQ(Q); //����һ�����Ϊ0�Ķ���
		TopOrder[cnt++] = V; //�����Ϊ������е���һ��Ԫ��
		//��V��ÿ���ڽӵ�W->AdjV;
		for(W=Graph->G[V].FirstEdge; W; W=W->Next){
			if(--Indegree[W->AdjV]==0){
				//��ɾ��Vʹ��W->AdjV���Ϊ��,��ö������� 
				AddQ(Q, W->AdjV); 
			}
		} 
	} 
	
	if(cnt != Graph->Nv){
		return false;
	} 
	else{
		return true;
	}
}


//ͳ��·�����Ȳ�����6�Ķ��������������ȿռ䣩
#define SIX 6
int Visited[MaxVertexNum];

void InitializeVisited(int Nv){
	Vertex V;
	for(V=0; V<Nv; V++){
		Visited[V] = false;
	}
} 

int SDS_BFS(LGraph Graph, Vertex S){
	//��SΪ�������Graph����6��BFS����
	Queue Q;
	Vertex V, Last, Tail;
	PtrToAdjVNode W;
	int Count, Level;
	
	Q = CreateQueue(MaxSize); //�����ն���
	Visited[S] = true; //���S�ѷ���
	Count = 1; //ͳ��������1��ʼ
	Level = 0; //��ʼ�㶨��Ϊ0��
	Last = S;  //�ò�ֻ��Sһ�����㣬�Ǹò㱻���ʵ����һ������
	AddQ(Q, S);//S�����
	
	while(!IsEmpty(Q)) {
		V = DeleteQ(Q); //����V
		for(W=Graph->G[V].FirstEdge; W; W=W->Next){ //����V��ÿ���ڽӵ� 
			if(!Visited[W->AdjV]){  //���ڽӵ�δ������ 
				Visited[W->AdjV] = true; //��Ƿ��� 
				Count++;               //ͳ������
				Tail = W->AdjV;      //��ǰ��β
				AddQ(Q, W->AdjV);   //���ڽӵ������ 
			}
		}
		if(V==Last){ //�����һ������һ�����㵯�� 
			Level++; //�������� 
			Last = Tail; //���µ�ǰ��β��Ϊ�����ʵ����һ������ 
		} 
		if(Level==SIX){
			break;
		}
	}
	DestroyQueue(Q);
	return Count;
}

void Six_Degrees_of_Separation(LGraph Graph){
	//���ڽӱ���ͼ����ÿ������������ȿռ�����
	Vertex V;
	int count;
	
	for(V=0; V<Graph->Nv; V++){
		InitializeVisited(Graph->Nv);
		count = SDS_BFS(Graph, V);
		printf("����%d�����ȸ��Ǳ���=%.2f%%\n", V, 100.0*(double)count/(double)Graph->Nv);
	} 
} 
