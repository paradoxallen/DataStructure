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
