#include<stdio.h>
#include<stdlib.h>
//�����ڽӾ���Ĵ洢��ʽ
#define INFINITY 1000000
#define MAX_VERTEX_NUM 20
typedef struct {
	int ** arcs;
	int vexnum,arcnum;
}MGraph;//��Ϊ����ʵ���Ϊ����ͼ�����ԾͲ��涥�������ˣ�����һ���ڽӾ�������ʾ����֮��ߵ�Ȩ���ɣ�Ҳ����Ҫ��Ŷ������Ϊÿһ����ž��Ƕ��㱾��
int AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM]={0};//�ڽӾ���,0��ʾ֮��ûͨ· 
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
	e=q.front->next ;//front��㲻������ 
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
int DFS1(MGraph G, int v,int s,int v0){//�����жϻ��ı��� 
	//printf("%d ",v);
	visited[v]=1;
	for(int i=1;i<=G.vexnum ;++i){
		if(AdjMatrix[v][i]==-1&&visited[v]==0 && (v==v0&&i==s)==0 )	DFS1(G,i,s,v0);//-1��ʾi��v��ͬһ����ͨ������ 
	} 
}
int DF(MGraph G,int s){//sΪ��������ʵ������ 
	for(int v=s;v<=G.vexnum;++v){
		if(!(visited[v])) DFS(G,v);//printf("keyi");
	}
	for(int v=1;v<s;++v){
		if(!(visited[v])) DFS(G,v);
	}
}
int DF1(MGraph G,int s,int t){//�����жϻ��Ķ��� 
	 int v=0;
	 
	 for(int i=1;i<=G.vexnum ;++i){
	 	visited[i]=0;
	 }
	 for(int i=1;i<=G.vexnum &&v==0;++i){
	 	if(AdjMatrix[s][i]==-1){
	 		v=i; 
		 }
	 }//�ҵ���ͨ������v�ĵ�һ���ڽӽ�� 
	 if(v==0) return 0; 
	 int tmp=AdjMatrix[s][t];
	 AdjMatrix[s][t]=-1;//ʹ��s,t��ͬһ��ͨ�����У��ж��Ƿ�ɻ� 
	 AdjMatrix[t][s]=-1;
	 int v0=v;
	 DFS1(G,v,s,v0);//����ͨ�����ĵ�һ���ڽӽ�㿪ʼ����  
	 AdjMatrix[s][t]=tmp;
	 AdjMatrix[t][s]=tmp;
	  if(visited[s]==1)	return 1;//�л� 
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
	scanf("%d %d",&G.vexnum,&G.arcnum  );//�������ͱ���
	int i=1,s;
	for(i=1;i<=G.arcnum;++i ){
		int a,b;
		//printf("������a ��b");
		scanf("%d %d",&a,&b);
		AdjMatrix[a][b]=1;AdjMatrix[b][a]=1;		
	} 
	//printf("������s"); 
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
	int min=0;//�����¼��� 
	int j=1;
	while(min==0){
		if(a[j]!=0){
			min=j;//����һ��edge������Ϊ��С 
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
int Connect(MGraph G,int s,int t){//�ж��Ƿ��л�����s��t���� 
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
int Prim(MGraph G){//��һ�Ŷ��㿪ʼ 
	int closedge[G.vexnum +1];//��������
	int k=1,sum=0;
	closedge[k]=0; //u0Ϊһ�Ŷ��㡢
	for(int j=2;j<=G.vexnum ;++j){
		
		if(AdjMatrix[k][j]!=0){
				closedge[j]=AdjMatrix[k][j];//�����и�ȱ�ݾ��ǵ�AdjMatrix[][]=0ʹ��ʾ���Ǽ��������󣬵������closedge=0ʱ�ֱ�ʾ��ͬһ�������У�����������Ӧ�ò���,������ǻ������������� 
		}
		else{
			closedge[j]=100;
		}
		printf("edge[%d]=%d \n ",j,closedge[j]);
	} 
	for(int i=1;i<G.vexnum ;++i){
		k=minimun(closedge,G.vexnum );//�ҵ�����̵Ķ�Ӧ��� 
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
		//printf("������a ��b");
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
		//printf("������a ��b");
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
	int s,t,v,w;//�����յ� j 
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
	printf("1��ͼ�ı���\n2����ͨѶ������С����������\n3����·��ͨ�������·��\n"); 
	scanf("%d",&c);
	switch(c){
		case 1:TraversingGraph(G);break;
		case 2:MCST(G);break;
		case 3:ShortestPath(G);break;
		;
	}
	//ÿ������һ����Ŀ��exe������һ�£������Ͳ��ð������������� 
} 
