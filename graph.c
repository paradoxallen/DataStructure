//邻接矩阵表示法
#define MaxVertexNum 100
#define INFINITY 65535
typedef int Vertex;
typedef int WeightType;
typedef char DataType;


typedef struct GNode *PtrToGNode;  //图节点的定义
struct GNode{
	int Nv;  //顶点数 
	int Ne;  //边数
	WeightType G[MaxVertexNum][MaxVertexNum];  //邻接矩阵
	DataType Data[MaxVertexNum]; //存顶点的数据 
	//若顶点无数据，此时Data[]可以不用出现 
}; 
typedef PtrToGNode MGraph;


//邻接矩阵表示--无向网图的初始化程序
typedef struct ENode *PtrToENode  //边的定义
struct ENode{
	Vertex V1, V2;  //有向边
	WeightType Weight; // 权重 
}; 
typedef PtrToENode Edge;

MGraph CreateGraph(int VertexNum){
	//初始化一个有顶点没有边的图
	Vertex V, W;
	MGraph Graph;
	
	Graph = (MGraph)malloc(sizeof(struct GNode));
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	
	//初始化邻接矩阵，默认顶点从0开始
	for(V=0; V<Graph->Nv; V++){
		for(W=0; W<Graph->Nv; W++){
			Graph->G[V][W] = INFINITY;
		}
	} 
	
	return Graph;
}

void InsertEdge(MGraph, Edge E){
	Graph->G[E->V1][E->V2] = E->Weight;
	Graph->G[E->V2][E->V1] = E->Weight;//若是无向图 
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


//邻接表表示法
#define MaxVertexNum 100
typedef int Vertex;
typedef int WeightType;
typedef char DataType;

typedef struct ENode *PtrToENode; //边的定义
struct ENode{
	Vertex V1, V2;
	WeightType Weight;
}; 
typedef PtrToENode Edge;

typedef struct AdjVNode *PtrToAdjVNode; //邻接点的定义 
struct AdjVNode{
	Vertex AdjV; //邻接点下标
	WeightType Weight;
	PtrToAdjVNode Next; 
};

typedef struct Vnode{
	//顶点表头结点定义
	PtrToAdjVNode FirstEdge;
	DataType Data; //注意很多情况下顶点，此时data可不出现 
} AdjList[MaxVertexNum];

typedef struct GNode *PtrToGNode; //图节点的定义
struct GNode{
	int Nv;
	int Ne;
	AdjList G; //邻接表 
}; 
typedef PtrToGNode Lgraph;


//邻接表表示--无向图的初始化
LGraph CreateGraph(int VertexNum){
	//初始化有顶点无边的图 
	Vertex V;
	LGraph Graph;
	
	Graph = (LGraph)malloc(sizeof(struct GNode));
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	
	//初始化邻接表头指针
	for(V=0; V<Graph->Nv; V++){
		Graph->G[V].FirstEdge = NULL;
	} 
	return Graph;
} 

void InsertEdge(LGraph Graph, Edege E){
	PtrToAdjVNode NewNode;
	
	//插入<V1,V2>
	//为V2建立新的邻接点 
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->V2;
	NewNode->Weight = E->Weight; 
	//V2插入V1的表头
	NewNode->Next = Graph->G[E->V1].FirstEdge;
	Graph->G[E->V1].FisrtEdge = NewNode;
	
	//若是无向图，还要插入<V2,V1> 
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->V1;
	NewNode->Weight = E->Weight; 
	//V2插入V1的表头
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

//邻接表的深度优先遍历
void Visit(Vertex V){
	printf("正在访问顶点%d\n", V);
} 
//Visited[]为全局变量，已经初始化为false
void DFS(LGraph Graph, Vertex V, void(*Visit)(Vertex)){
	//以V点出发的DFS
	 PtrToAdjVNode W;
	 
	 Visit(V);
	 Visited[V] = true;
	 
	 for(W=Graph->G[V].FirstEdge; W; W=W->Next){
	 	if(!Visited[W->AdjV])
	 }
} 


//邻接矩阵储存图的广度优先遍历
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
