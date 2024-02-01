#include<stdio.h>
#include<stdlib.h>
int time=0;//������¼ÿ���¼�������ʱ��
int N,total,close_time,average_time;
typedef struct customer{
	int in_time;
	int wait_time;
	int money;
	int id;
	customer *next;
}customer,*QNode;
typedef struct Queue{
	customer *front;
	customer *rear;
}Queue;
Queue Q1,Q2;
int q2num=0;//������¼����2������ 
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
int main(){
	int t,m;
	int id;
	QNode p,p1;
	int total1;//���� �жϡ��ڴ˼������У�һ�������ʽ��ܶ����ڻ���ڸղŵ�һ�����������һ���ͻ�(�ڶ���ҵ��)���Ӵ�֮ǰ��������߱����ѽ��ڶ������м�������һ�飬��ֹͣ��顱 
	InitQueue(Q1);InitQueue(Q2);
	scanf("%d %d %d %d",&N,&total,&close_time,&average_time);
	int wait[N+1];//��¼ÿ���û��ĵȴ�ʱ�� 
	for(int i=0;i<=N;++i){
		wait[i]=0;
	}
	for(int i=1;i<=N;++i){
		scanf("%d %d",&m,&t);
		p=(QNode)malloc(sizeof(customer));//������¼ÿ�ν���Ĺ˿͵���Ϣ
		p->in_time=t;
		p->money=m; 
		p->id =i;
		if(m>0||total+m>=0){
			p->wait_time=0;
			time=t+average_time;
			wait[i]=0; 
			total+=m;
			printf("%d����%dʱ�������У���%dʱ���������뿪����ʱ�����д��%d\n",i,t,time,total);
		}
		else{
			printf("%d����%dʱ����������Ҫ��Ǯ%d,��ʱ�����д��%d������\n",i,t,m,total);
			EnQueue(Q2,p);
			q2num++;
			printf("1.��ʱ��������%d��\n",q2num);
		}
		if(m>0&&q2num>0){
			int k=1;//������¼�Ƿ������ȫ 
				total1=total-m;//���� �жϡ��ڴ˼������У�һ�������ʽ��ܶ����ڻ���ڸղŵ�һ�����������һ���ͻ�(�ڶ���ҵ��)���Ӵ�֮ǰ��������߱����ѽ��ڶ������м�������һ�飬��ֹͣ��顱 
				for(k=1;k<=q2num&&total>total1;++k){
				p1=(QNode)malloc(sizeof(customer));
				DeQueue(Q2,p1);
				printf("%d����Ҫ����%dԪ������ʱ���д��Ϊ%d������������Ϊ%d\n",p1->id,p1->money,total,total+p1->money );
				if(total+p1->money>=0) {
					id=p1->id;
					wait[id]=time-p1->in_time ;
					printf("%d�ŵȴ���%d-%d=%d",id,time,p1->in_time,wait[id]);
					time+=average_time;
					q2num--;
					total+=m;
					printf("%d����%dʱ�󣬴������н�����%dԪ���������Ϊ%d\n",id,time-10,m,total);
				}
				else{
					EnQueue(Q2,p1);
					
				}
			} 
		}
		
	}
	printf("2.��ʱ��������%d��\n",q2num);
	while(q2num>0){
		p1=(QNode)malloc(sizeof(customer));
		DeQueue(Q2,p1);
		id=p1->id ;
		wait[id]=close_time-p1->in_time ;
		q2num--;
		
	}
	int sum=0;
	for(int i=1;i<=N;++i){
		printf("wait[%d]=%d\n",i,wait[i]);
		sum+=wait[i];
	}
	
	printf("average=%d",sum/N); 
	
return 0;
}
