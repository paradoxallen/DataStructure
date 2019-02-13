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


//最短路径Dijkstra算法 
Vertex FindMinDist(MGraph Graph, int dist[], int collocted[]){
	//返回未被收录定点中的最小者
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
	
	//初始化
	for(V=0; V<Graph->Nv; V++){
		dist[V] = Graph->G[S][V];
		path[V] = -1;
		collected[V] = false;
	} 
	
	//起点收进集合
	dist[S] = 0;
	collected[S] = true;
	
	while(1){
		//V=未收入顶点中dist最小者
		V = FindMinDist(Graph, dist, collected) ;
		if(V==ERROR){
			break; //若这样的V不存在，算法结束 
		}
	} 
	collected[V] = true;
	for(W=0; W<Graph->Nv; W++){
		//若W是V的邻接点并且未收录
		if(collected[W]==false && Graph->G[V][W]<INFINITY){
			if(Graph->G[V][W]<0){
				return false; //若有负边，返回错误 
			}
			if(dist[V]+Graph[V][W] < dist[W]){
				//若收录V使得dist[W]变小 
				dist[W] = dist[V] + Graph->G[V][W]；
				path[W] = V; 
			}
		} 
	} 
	return true;
}


//Floyd算法
bool Floyd(MGraph Graph, WeightType D[][MaxVertexNum], Vertex path[][MaxVertexNum]){
	Vertex i, j, k;
	
	//初始化
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


//邻接矩阵储存图的Prim算法
#define ERROR -1

int Prim(MGraph Graph, LGraph MST){
	//将最小生成树保存为邻接表的图MST，返回最小权重值
	WeightType dist[MaxVertexNum], TotalWeight;
	Vertex parent[MaxVertexNum], V, W;
	int VCount;
	Edge E;
	
	//初始化，默认初始点下标为0
	for(V=0; V<Graph->Nv; V++){
		//若无边这定义为INFINITY
		dist[V] = Graph->G[0][V];
		parent[V] = 0; //定义所有父节点都是0 
	} 
	TotalWeight = 0; //初始化权重和
	VCount = 0;  //初始化收录的顶点数
	
	//创建包含所有顶点但没有边的图，邻接表版本
	MST = CreateGraph(Graph->Nv);
	E = (Edge)malloc(sizeof(struct ENode)); //建立空的边节点
	
	//将初始点0收录进MST
	dist[0] = 0;
	VCount++;
	parent[0] = -1; //树根 
	
	while(1){
		V = FindMinDist(Graph, Dist);
		//V=未收录顶点中dist最小者
		if(V==ERROR){
			break;//若这样的V不存在，算法结束 
		} 
		
		//将V及相应的边<parent[V],V>收录进MST
		E->V1 = parent[V];
		E->V2 = V;
		E->Weight = dist[V];
		InsertEdge(MST, E);
		TotalWeight += dist[V];
		dist[V] = 0;
		VCount++;
		
		for(W=0; W<Graph->Nv; W++){
			if(dist[W]!=0 && Graph->G[V][W]<INFINTY){
				//若W是V的临界点并且未被收录
				if(Graph->G[V][W]<dist[W]){
					//若收录V使得dist[W]变小
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


//Kruskal算法的伪代码
int Kruskal(LGraph Graph, LGraph MST){
	//将最小生成树保存为邻接表储存的图MST，返回最小权重和
	MST = 包含所有顶点但没有边的图
	while(MST中收集的边不到Graph->Nv-1条 && 原图的边集E非空){
		从E中选择最小代价边(V, W)；//引入最小堆完成
		从E中删除该边(V，W)
		if((V, w)的选取不在MST中构成回路) //此判断由并查集的find完成 
			将(V, W)加入MST；//此步由并查集的Union完成
		else
			彻底丢弃(V, W) 
	} 
	if(MST中收集的边不到Graph->Nv-1条)
		return ERROR;
	else
		return 最小权重和; 
} 


//拓扑排序算法伪代码
bool TopSort(Graph Graph, Vertex TopOrder[]){
	//对graph进行拓扑排序，TopOrder顺序储存排序后的顶点下标
	
	//遍历图，得到各顶点的入度Indergree[]
	for(cnt=0; cnt<Graph->Nv; cnt++){
		V = 为输出的入度为0的顶点;
		if(这样的V不存在){
			printf("图中有回路");
			break;
		} 
		TopOrder[cnt] = V; //将V存为结果序列的下一个元素
		//将V及其出边从图中删除
		for(V的每个邻接点W){
			Indegree--; 
		} 
	} 
	if(cnt != Graph->Nv){
		return false; //说明图中有回路，返回错误 
	}
	else{
		return true;
	}
} 

//改进后的拓扑排序算法
bool TopSort(LGraph Graph, Vertex TopOrder[]) {
	//对graph进行拓扑排序，TopOrder顺序储存排序后的顶点下标
	int Indegree[MaxVertexNum], cnt;
	Vertex V;
	PtrToAdjVNode W;
	Queue Q = CreateQueue(Graph->Nv);
	
	//初始化Indegree[]
	for(V=0; V<Graph->Nv; V++){
		Indegree[V] = 0;
	} 
	
	//遍历图，得到Indegree[]
	for(V=0; V<Graph->Nv; V++){
		for(W=Graph->G[V].FirstEdge; W; W=W->Next){
			Indegree[W->AdjV]++; //对有向边<V， W->AdjV>累计终点的入度 
		}
	}
	
	//将所有入度为0的顶点入列
	for(V=0; V<Graph->Nv; V++){
		if(Indegree[V]==0){
			AddQ(Q, V);
		}
	} 
	
	//下面进入拓扑排序
	cnt = 0;
	while(!IsEmpty(Q)){
		V = DeleteQ(Q); //弹出一个入度为0的顶点
		TopOrder[cnt++] = V; //将其存为结果序列的下一个元素
		//对V的每个邻接点W->AdjV;
		for(W=Graph->G[V].FirstEdge; W; W=W->Next){
			if(--Indegree[W->AdjV]==0){
				//若删除V使得W->AdjV入度为零,则该顶点入列 
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


//统计路径长度不超过6的定点数比例（六度空间）
#define SIX 6
int Visited[MaxVertexNum];

void InitializeVisited(int Nv){
	Vertex V;
	for(V=0; V<Nv; V++){
		Visited[V] = false;
	}
} 

int SDS_BFS(LGraph Graph, Vertex S){
	//以S为出发点对Graph进行6层BFS搜索
	Queue Q;
	Vertex V, Last, Tail;
	PtrToAdjVNode W;
	int Count, Level;
	
	Q = CreateQueue(MaxSize); //创建空队列
	Visited[S] = true; //标记S已访问
	Count = 1; //统计人数从1开始
	Level = 0; //起始点定义为0层
	Last = S;  //该层只有S一个顶点，是该层被访问的最后一个顶点
	AddQ(Q, S);//S入队列
	
	while(!IsEmpty(Q)) {
		V = DeleteQ(Q); //弹出V
		for(W=Graph->G[V].FirstEdge; W; W=W->Next){ //访问V的每个邻接点 
			if(!Visited[W->AdjV]){  //若邻接点未被访问 
				Visited[W->AdjV] = true; //标记访问 
				Count++;               //统计人数
				Tail = W->AdjV;      //当前层尾
				AddQ(Q, W->AdjV);   //该邻接点入队列 
			}
		}
		if(V==Last){ //如果上一层的最后一个顶点弹出 
			Level++; //层数递增 
			Last = Tail; //更新当前层尾作为被访问的最后一个顶点 
		} 
		if(Level==SIX){
			break;
		}
	}
	DestroyQueue(Q);
	return Count;
}

void Six_Degrees_of_Separation(LGraph Graph){
	//用邻接表储存图，对每个顶点检验六度空间理论
	Vertex V;
	int count;
	
	for(V=0; V<Graph->Nv; V++){
		InitializeVisited(Graph->Nv);
		count = SDS_BFS(Graph, V);
		printf("顶点%d的六度覆盖比例=%.2f%%\n", V, 100.0*(double)count/(double)Graph->Nv);
	} 
} 
