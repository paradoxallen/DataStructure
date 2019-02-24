//��ͨ�������⣺���������κ���������䶼����ʵ�ֿ��ٽ�ͨ 

//1.�����·�������⣺�г�ÿ������·ֱ����ͨ�ĳ��������ٻ���Ҫ�������������·�Ϳ��Դﵽ��ͨĿ�� 
//��ͨ���������㺯��
int CountConnectedComponents(LGraph Graph){
	//����ͼGraph����ͨ���ĸ���
	Vertex V;
	int cnt = 0;
	
	//��ȫ�ֱ���Visited[]��ʼ��Ϊfalse
	InitializeVisited(Graph->Nv);
	//ÿһ��DFS��Ӧһ����ͨ��
	for(V=0; V<Graph->Nv; V++){
		if(!Visited[V]){
			DFS(Graph, V);
			cnt++; 
		}
	} 
	return cnt;
} 

//��һ�ַ��������ò��鼯ͳ����ͨ������
typedef Vertex ElementType;

void Initialization(SetType S, int N){
	//���ϳ�ʼ��
	int i;
	for(i=0; i<N; i++){
		S[i] = -1;
	} 
} 

void InputConnection(SetType S, int M){
	//����M���ߣ������б������Ľ�㲢��ͬһ����
	Vertex U, V;	//��¼����Ľ��
	Vertex Root1, Root2;	//��¼���������ڵļ��ϵĸ��ڵ�
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
	//���㼯��S����ͨ���ĸ���
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
	int N, M;	//������N������·��M 
	
	scanf("%d%d", &N, &M);
	Initialization(S, N);
	InputConnection(S, M);
	printf("��Ҫ�����·%d��\n", CountConnectedComponents(S, N)-1);
	
	return 0; 
}


//2.��ͳɱ��������⣻�г��п��ܽ���ɿ���·����������·�ĳɱ�����ͨ������Ҫ����ͳɱ�
//Kruskal�㷨����
int Kruskal(LGraph Graph, LGraph MST){
	//����С����������Ϊ�ڽӱ����ͼMST��������СȨ�غ�
	WeightType TotalWeight;
	int ECount, NextEdge;
	SetType VSet;	//��������
	Edge ESet;	//������
	
	InitializeVSet(VSet, Graph->Nv);	//��ʼ�����㲢�鼯
	ESet = (Edge)malloc(sizeof(struct ENode)*Graph->Ne);
	InitializeESet(Graph, ESet);	//��ʼ���ߵ���С��
	
	//�����������ж��㵫û�бߵ�ͼ��ע�����ڽӱ�汾
	MST = CreateGraph(Graph->Nv);
	TotalWeight = 0;	//��ʼ��Ȩ�غ�
	ECount = 0;	//��ʼ����¼�ı���
	
	NextEdge = Graph->Nv;	//��ʼ���߼��Ĺ�ģ
	while(ECount<Grapg->Nv-1){
		//���ռ��ı߲����Թ�����ʱ
		NextEdge = GetEdge(ESet, NextEdge);	//�ӱ߼��еõ���С�ߵ�λ��
		if(NextEdge<0){
			//�߼��ѿ�
			break; 
		} 
		//����ñߵļ��벻���ɻ�·�������˽�㲻����ͬһ��ͨ��
		if(CheckCycle(VSet, ESet[NextEdge].V1, ESet[NextEdge].V2)==true){
			//���ñ߲���MST
			InsertEdge(MST, ESet+NextEdge);
			TotalWeight += ESet[NextEdge].Weight;	//�ۼ�Ȩ��
			ECount++;	//�������б���+1 
		} 
	} 
	if(ECount<Graph->Nv-1){
		TotalWeight = -1;	//���ô����־����ʾ������������ 
	} 
	
	return TotalWeight;
} 

//���ٵõ���С�ߵĺ���
void PercDown(Edge ESet, int p, int N){
	//�ı�PercDown(MaxHeap H, int p)
	//��N��Ԫ�صı���������ESet[p]Ϊ�����Ӷѵ���Ϊ����Weight����С��
	int Parent, Child;
	struct ENode X;
	
	X = ESet[p];	//ȡ�����ڵ��ŵ�ֵ
	for(Parent=p; (Parent*2+1)<N; Parent=Child){
		Child = Parent*2+1;
		if((Child!=N-1)&&(ESet[Child].Weight>ESet[Child+1].Weight){
			Child++;	//Childָ�������ӽ��Ľ�С�� 
		}
		if(X.Weight<=ESet[Child].Weight){
			break;	//�ҵ��˺��ʵ�λ�� 
		} 
		else{
			//����X
			ESet[Parent] = ESet[Child]; 
		}
	} 
	ESet[Parent] = X;
} 


void InitializeESet(LGraph Graph, Edge ESet){
	//��ͼ�ıߴ�������ESet�����ҳ�ʼ��Ϊ��С��
	Vertex V;
	PtrToAdjVNode W;
	int ECount;
	
	//��ͼ�ıߴ�������ESet
	ECount = 0;
	for(V=0; V<Graph->Nv; V++){
		for(W=Graph->G[V].FirstEdge; W; W=W->Next){
			if(V<W->AdjV){
				//�����ظ�¼������ͼ�ıߣ�ֻ��V1<V2�ı�
				ESet[ECount].V1 = V;
				ESet[ECount].V2 = W->AdjV;
				ESet[ECount++].Weight = W->Weight; 
			}
		}
	} 
	//��ʼ��Ϊ��С��
	for(ECount=Graph->Ne/2; ECount>0; ECount--){
		PercDown(ESet, ECount; Graph->Ne);
	} 
	
}

int GetEdge(Edge ESet, int CurrentSize){
	//������ǰ�ѵĴ�СCurrentSize������ǰ��С��λ�õ�����������
	
	//����С�ߺ͵�ǰ�����һ��λ�õı߽���
	Swap(&ESet[0], &ESet[CurrentSize-1]);
	//��ʣ�µĶѼ�������Ϊ��С��
	PercDown(ESet, 0, CurrentSize-1);
	
	return CurrentSize-1;	//������С������λ�� 
}

//����·�ĺ���
bool CheckCycle(SetType VSet, Vertex V1, Vertex V2){
	//�������V1��V2�ı��Ƿ������е���С�������Ӽ��й��ɻ�·
	Vertex Root1, Root2;
	
	Root1 = Find(VSet, V1);	//�õ�V1������ͨ������
	Root2 = FInd(Vset, V2);	//�õ�V2������ͨ������
	
	if(Root1==Root2){
		//��V1��V2�Ѿ���ͨ����ñ߲�Ҫ
		return false; 
	} 
	else{
		//����ñ߿��Ա��ռ���ͬʱ��V1��V2����ͬһ��ͨ��
		Union(VSet, Root1, Root2);
		return true; 
	}
} 
