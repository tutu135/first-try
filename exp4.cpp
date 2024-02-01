#include<stdio.h>
#include<stdlib.h>
//利用邻接矩阵的存储方式
#define INFINITY 1000000
#define MAX_VERTEX_NUM 20
typedef struct {
	int ** arcs;
	int vexnum,arcnum;
}MGraph;//因为三个实验均为无向图，所以就不存顶点类型了，利用一个邻接矩阵来表示他们之间边的权即可，也不需要存放顶点表，因为每一个序号就是顶点本身
int AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM]={0};//邻接矩阵,0表示之间没通路 
int visited[MAX_VERTEX_NUM+1]={0};
typedef struct customer{
	int id;
	customer *next;
}customer,*QNode;
typedef struct Queue{
	customer *front;
	customer *rear;
}Queue;
Queue Q; 
int InitQueue(Queue &q){
	q.front=(QNode)malloc(sizeof(customer));
	q.rear =q.front ;
	q.front->next =NULL;
}
int EnQueue(Queue &q,QNode &e){
	//e=(QNode)malloc(sizeof(customer));
	q.rear->next =e;
	q.rear=e;
}
int DeQueue(Queue &q,QNode &e){
	if (q.front ==q.rear)
		return 0;
	e=q.front->next ;//front结点不放数据 
	q.front->next =e->next ;
	if(q.rear==e) q.rear=q.front;  
}
int DFS(MGraph G, int v){
	printf("%d ",v);
	visited[v]=1;
	for(int i=1;i<=G.vexnum ;++i){
		if(AdjMatrix[v][i]==1 && visited[i]==0)	DFS(G,i);
	}
}
int DFS1(MGraph G, int v,int s,int v0){//用于判断环的遍历 
	//printf("%d ",v);
	visited[v]=1;
	for(int i=1;i<=G.vexnum ;++i){
		if(AdjMatrix[v][i]==-1&&visited[v]==0 && (v==v0&&i==s)==0 )	DFS1(G,i,s,v0);//-1表示i和v在同一个连通分量中 
	} 
}
int DF(MGraph G,int s){//s为遍历的其实顶点编号 
	for(int v=s;v<=G.vexnum;++v){
		if(!(visited[v])) DFS(G,v);//printf("keyi");
	}
	for(int v=1;v<s;++v){
		if(!(visited[v])) DFS(G,v);
	}
}
int DF1(MGraph G,int s,int t){//用于判断环的定义 
	 int v=0;
	 
	 for(int i=1;i<=G.vexnum ;++i){
	 	visited[i]=0;
	 }
	 for(int i=1;i<=G.vexnum &&v==0;++i){
	 	if(AdjMatrix[s][i]==-1){
	 		v=i; 
		 }
	 }//找到连通分量中v的第一个邻接结点 
	 if(v==0) return 0; 
	 int tmp=AdjMatrix[s][t];
	 AdjMatrix[s][t]=-1;//使是s,t在同一连通分量中，判断是否成环 
	 AdjMatrix[t][s]=-1;
	 int v0=v;
	 DFS1(G,v,s,v0);//从连通分量的第一个邻接结点开始遍历  
	 AdjMatrix[s][t]=tmp;
	 AdjMatrix[t][s]=tmp;
	  if(visited[s]==1)	return 1;//有环 
	  else return 0;
}
int	BF(MGraph G,int s){
	QNode p,e;
	e=(QNode)malloc(sizeof(customer)); 
	InitQueue(Q);
	int v=s,u;
	//printf("LAILE");
	for(v=s;v<=G.vexnum ;++v){
		//printf("visited[%d]=%d",v,visited[v]);
		if(!(visited[v])) {
			visited[v]=1;
			printf("%d ",v);
			p=(QNode)malloc(sizeof(customer));
			p->id=v;
			EnQueue(Q,p);
			while(Q.front !=Q.rear ){
				DeQueue(Q,e);
				u=e->id;
				for(int k=1;k<=G.vexnum ;++k){
					if(AdjMatrix[u][k]==1&&visited[u]==0){
						visited[u]=1;
						p=(QNode)malloc(sizeof(customer));
						p->id=k;
						EnQueue(Q,p);
					}
				}
			}
		}
	}
	for(v=1;v<=s;++v){
		if(!visited[v]) {
			visited[v]=1;
			printf("%d",v);
			p=(QNode)malloc(sizeof(customer));
			p->id=v;
			EnQueue(Q,p);
			while(Q.front !=Q.rear ){
				DeQueue(Q,e);
				 u=e->id;
				for(int k=1;k<=G.vexnum ;++k){
					if(AdjMatrix[u][k]==1&&visited[u]!=0){
						visited[u]=0;
						p=(QNode)malloc(sizeof(customer));
						p->id=k;
						EnQueue(Q,p);
					}
				}
			}
		}
	}
}
int TraversingGraph(MGraph G){
	scanf("%d %d",&G.vexnum,&G.arcnum  );//顶点数和边数
	int i=1,s;
	for(i=1;i<=G.arcnum;++i ){
		int a,b;
		//printf("请输入a 和b");
		scanf("%d %d",&a,&b);
		AdjMatrix[a][b]=1;AdjMatrix[b][a]=1;		
	} 
	//printf("请输入s"); 
	scanf("%d",&s);
	for(i=1;i<=G.vexnum ;++i){
		for(int j=1;j<=G.vexnum ;++j){
			printf("%d\t",AdjMatrix[i][j]);
		}
		printf("\n");
	}
	DF(G,s);
	for(int k=0;k<=G.vexnum ;k++) {
		visited[k]=0;
	//	printf("1.visited[%d]=%d    ",k,visited[k]);	
	}
	printf("\n");
	BF(G,s);
}

int minimun(int a[],int n){
	int min=0;//这里记录编号 
	int j=1;
	while(min==0){
		if(a[j]!=0){
			min=j;//先找一个edge来令其为最小 
		}
		++j;
	}
	for(int i=1;i<=n;++i){
		if(a[i]<a[min] && a[i]>0){
			min=i;
		}
	}
	return min;
}
int Connect(MGraph G,int s,int t){//判断是否有环包含s，t两点 
	DF1(G,s,t);
}
int minimun1(MGraph G){
	int min=1000;
	for(int i=1;i<=G.vexnum ;++i){
		for(int j=1;j<=G.vexnum ;++j){
			if(AdjMatrix[i][j]>0&&AdjMatrix[i][j]<min&&Connect( G,i,j)==0){
				min=AdjMatrix[i][j];
				AdjMatrix[i][j]=-1;AdjMatrix[j][i]=-1;
			}
		}
	}
	return min;
}
int Prim(MGraph G){//从一号顶点开始 
	int closedge[G.vexnum +1];//辅助数组
	int k=1,sum=0;
	closedge[k]=0; //u0为一号顶点、
	for(int j=2;j<=G.vexnum ;++j){
		
		if(AdjMatrix[k][j]!=0){
				closedge[j]=AdjMatrix[k][j];//这里有个缺陷就是当AdjMatrix[][]=0使表示他们间距离无穷大，但这里的closedge=0时又表示再同一个集合中，，不过问题应该不大,这个理还是会产生功能问题的 
		}
		else{
			closedge[j]=100;
		}
		printf("edge[%d]=%d \n ",j,closedge[j]);
	} 
	for(int i=1;i<G.vexnum ;++i){
		k=minimun(closedge,G.vexnum );//找到边最短的对应编号 
		printf("k=%d   ",k);
		sum+=closedge[k];
		closedge[k]=0;
		for(int j=1;j<=G.vexnum ;++j){
			if(AdjMatrix[j][k]<closedge[j]&& AdjMatrix[j][k]>0){
				closedge[j]=AdjMatrix[j][k];
			}
			printf("edge[%d]=%d  ",j,closedge[j]);
		}
	}
	printf("in Prim sum=%d",sum); 
}
int Kruskal(MGraph G){
	int sum=0;
	for(int i=1;i<=G.vexnum-1;++i){
		sum+=minimun1(G);
	}
	printf("in kruskal sum =%d",sum);
}
int MCST(MGraph G){
	scanf("%d %d",&G.vexnum,&G.arcnum  );
	int i=1;
	for(i=1;i<=G.arcnum;++i ){
		int a,b,c;
		//printf("请输入a 和b");
		scanf("%d %d %d",&a,&b,&c);
		AdjMatrix[a][b]=c;AdjMatrix[b][a]=c;		
	}
	for(i=1;i<=G.vexnum ;++i){
		for(int j=1;j<=G.vexnum ;++j){
			printf("%d\t",AdjMatrix[i][j]);
		}
		printf("\n");
	}
	Prim(G);
	Kruskal(G);
}
int ShortestPath(MGraph G){
		scanf("%d %d",&G.vexnum,&G.arcnum  );
	int i=1,min;
	for(i=1;i<=G.arcnum;++i ){
		int a,b,c;
		//printf("请输入a 和b");
		scanf("%d %d %d",&a,&b,&c);
		AdjMatrix[a][b]=c;AdjMatrix[b][a]=c;		
	}
	for(i=1;i<=G.vexnum ;++i){
		for(int j=1;j<=G.vexnum ;++j){
			printf("%d\t",AdjMatrix[i][j]);
		}
		printf("\n");
	}
	int final[G.vexnum +1]={0};
	int D[G.vexnum +1]={0};
	int P[G.vexnum +1][G.vexnum +1]={0};
	int s,t,v,w;//起点和终点 j 
	scanf("%d %d",&s,&t);
	for( v=1;v<=G.vexnum ;++v){
		if(AdjMatrix[v][s]==0){
			D[v]=INFINITY;
		}
		else{
			D[v]=AdjMatrix[v][s];
		}
		for(int w=1;w<=G.vexnum ;++w){
			P[v][w]=0;
		}
		if(D[v]<INFINITY){
			P[v][s]=1;P[v][v]=1;
	}
	}
		D[s]=0;final[s]=1;
		for(i=2;i<=G.vexnum ;++i){
			min=INFINITY;
			for(int w=1;w<=G.vexnum ;++w){
				if(!(final[w])){
					if(D[w]<min){
						v=w;min=D[w];
					}
				}
				
			}
		
		final[v]=1;
		for( w=1;w<=G.vexnum ;++w){
			if(!final[w]&&(min+AdjMatrix[v][w]<D[w])){
				D[w]=min+AdjMatrix[v][w];
				*P[w]=*P[v];P[w][w]=1;
			}
		}
	}
	printf("shortestpath is%d",D[t]);
}
int main(){
	MGraph G; 
	int c;
	printf("1、图的遍历\n2、求通讯网的最小代价生成树\n3、铁路交通网的最短路径\n"); 
	scanf("%d",&c);
	switch(c){
		case 1:TraversingGraph(G);break;
		case 2:MCST(G);break;
		case 3:ShortestPath(G);break;
		;
	}
	//每次做完一个题目后exe都重启一下，这样就不用把数据再清零了 
} 
