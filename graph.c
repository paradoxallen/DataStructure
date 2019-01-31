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
