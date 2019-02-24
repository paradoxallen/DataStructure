//畅通工程问题：整个地区任何两个城镇间都可以实现快速交通 

//1.建设道路数量问题：列出每条快速路直接连通的城镇，问最少还需要建设多少条快速路就可以达到畅通目标 
//连通集个数计算函数
int CountConnectedComponents(LGraph Graph){
	//计算图Graph中连通集的个数
	Vertex V;
	int cnt = 0;
	
	//将全局变量Visited[]初始化为false
	InitializeVisited(Graph->Nv);
	//每一次DFS对应一个连通集
	for(V=0; V<Graph->Nv; V++){
		if(!Visited[V]){
			DFS(Graph, V);
			cnt++; 
		}
	} 
	return cnt;
} 

//另一种方法：利用并查集统计连通集个数
typedef Vertex ElementType;

void Initialization(SetType S, int N){
	//集合初始化
	int i;
	for(i=0; i<N; i++){
		S[i] = -1;
	} 
} 

void InputConnection(SetType S, int M){
	//读入M条边，并将有边相连的结点并入同一集合
	Vertex U, V;	//记录输入的结点
	Vertex Root1, Root2;	//记录输入结点所在的集合的根节点
	int i;
	
	for(i=0; i<M; i++){
		scanf("%d%d", &U, &V);
		Root1 = Find(S, U);
		Root2 = Find(S, V);
	} 
	if(Root1 != Root2){
		Union(S, Root1, Root2);
	}
}

int CountConnectedComponents(SetType S, int N){
	//计算集合S中连通集的个数
	int i, cnt = 0;
	
	for(i=0; i<N; i++){
		if(S[i]<0){
			cnt++;
		}
	} 
	return cnt;
}

int main(){
	SetType S;
	int N, M;	//城镇数N，快速路数M 
	
	scanf("%d%d", &N, &M);
	Initialization(S, N);
	InputConnection(S, M);
	printf("需要建设道路%d条\n", CountConnectedComponents(S, N)-1);
	
	return 0; 
}


//2.最低成本建设问题；列出有可能建设成快速路的若干条道路的成本，求畅通工程需要的最低成本
//Kruskal算法函数
int Kruskal(LGraph Graph, LGraph MST){
	//将最小生成树保存为邻接表储存的图MST，返回最小权重和
	WeightType TotalWeight;
	int ECount, NextEdge;
	SetType VSet;	//顶点数组
	Edge ESet;	//边数组
	
	InitializeVSet(VSet, Graph->Nv);	//初始化顶点并查集
	ESet = (Edge)malloc(sizeof(struct ENode)*Graph->Ne);
	InitializeESet(Graph, ESet);	//初始化边的最小堆
	
	//创建包含所有顶点但没有边的图，注意用邻接表版本
	MST = CreateGraph(Graph->Nv);
	TotalWeight = 0;	//初始化权重和
	ECount = 0;	//初始化收录的边数
	
	NextEdge = Graph->Nv;	//初始化边集的规模
	while(ECount<Grapg->Nv-1){
		//当收集的边不足以构成树时
		NextEdge = GetEdge(ESet, NextEdge);	//从边集中得到最小边的位置
		if(NextEdge<0){
			//边集已空
			break; 
		} 
		//如果该边的加入不构成回路，即两端结点不属于同一连通集
		if(CheckCycle(VSet, ESet[NextEdge].V1, ESet[NextEdge].V2)==true){
			//将该边插入MST
			InsertEdge(MST, ESet+NextEdge);
			TotalWeight += ESet[NextEdge].Weight;	//累计权重
			ECount++;	//生成树中边数+1 
		} 
	} 
	if(ECount<Graph->Nv-1){
		TotalWeight = -1;	//设置错误标志，表示生成树不存在 
	} 
	
	return TotalWeight;
} 

//快速得到最小边的函数
void PercDown(Edge ESet, int p, int N){
	//改编PercDown(MaxHeap H, int p)
	//将N个元素的边数组中以ESet[p]为根的子堆调整为关于Weight的最小堆
	int Parent, Child;
	struct ENode X;
	
	X = ESet[p];	//取出根节点存放的值
	for(Parent=p; (Parent*2+1)<N; Parent=Child){
		Child = Parent*2+1;
		if((Child!=N-1)&&(ESet[Child].Weight>ESet[Child+1].Weight){
			Child++;	//Child指向左右子结点的较小者 
		}
		if(X.Weight<=ESet[Child].Weight){
			break;	//找到了合适的位置 
		} 
		else{
			//下滤X
			ESet[Parent] = ESet[Child]; 
		}
	} 
	ESet[Parent] = X;
} 


void InitializeESet(LGraph Graph, Edge ESet){
	//将图的边存入数组ESet，并且初始化为最小堆
	Vertex V;
	PtrToAdjVNode W;
	int ECount;
	
	//将图的边存入数组ESet
	ECount = 0;
	for(V=0; V<Graph->Nv; V++){
		for(W=Graph->G[V].FirstEdge; W; W=W->Next){
			if(V<W->AdjV){
				//避免重复录入无向图的边，只收V1<V2的边
				ESet[ECount].V1 = V;
				ESet[ECount].V2 = W->AdjV;
				ESet[ECount++].Weight = W->Weight; 
			}
		}
	} 
	//初始化为最小堆
	for(ECount=Graph->Ne/2; ECount>0; ECount--){
		PercDown(ESet, ECount; Graph->Ne);
	} 
	
}

int GetEdge(Edge ESet, int CurrentSize){
	//给定当前堆的大小CurrentSize，将当前最小边位置弹出并调整堆
	
	//将最小边和当前堆最后一个位置的边交换
	Swap(&ESet[0], &ESet[CurrentSize-1]);
	//将剩下的堆继续调整为最小堆
	PercDown(ESet, 0, CurrentSize-1);
	
	return CurrentSize-1;	//返回最小边所在位置 
}

//检查回路的函数
bool CheckCycle(SetType VSet, Vertex V1, Vertex V2){
	//检查连接V1和V2的边是否在现有的最小生成树子集中构成回路
	Vertex Root1, Root2;
	
	Root1 = Find(VSet, V1);	//得到V1所在连通集名称
	Root2 = FInd(Vset, V2);	//得到V2所在连通集名称
	
	if(Root1==Root2){
		//若V1和V2已经连通，则该边不要
		return false; 
	} 
	else{
		//否则该边可以被收集，同时将V1和V2并入同一连通集
		Union(VSet, Root1, Root2);
		return true; 
	}
} 
