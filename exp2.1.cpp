#include<stdio.h>
#include<stdlib.h>
int time=0;//用来记录每个事件发生的时刻
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
int q2num=0;//用来记录队列2的人数 
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
int main(){
	int t,m;
	int id;
	QNode p,p1;
	int total1;//用来 判断“在此检查过程中，一旦银行资金总额少于或等于刚才第一个队列中最后一个客户(第二种业务)被接待之前的数额，或者本次已将第二个队列检查或处理了一遍，就停止检查” 
	InitQueue(Q1);InitQueue(Q2);
	scanf("%d %d %d %d",&N,&total,&close_time,&average_time);
	int wait[N+1];//记录每个用户的等待时间 
	for(int i=0;i<=N;++i){
		wait[i]=0;
	}
	for(int i=1;i<=N;++i){
		scanf("%d %d",&m,&t);
		p=(QNode)malloc(sizeof(customer));//用来记录每次进入的顾客的信息
		p->in_time=t;
		p->money=m; 
		p->id =i;
		if(m>0||total+m>=0){
			p->wait_time=0;
			time=t+average_time;
			wait[i]=0; 
			total+=m;
			printf("%d号在%d时到达银行，与%d时办完手续离开，此时银行有存款%d\n",i,t,time,total);
		}
		else{
			printf("%d号在%d时到达银行需要存钱%d,此时银行有存款%d，不够\n",i,t,m,total);
			EnQueue(Q2,p);
			q2num++;
			printf("1.此时队列中有%d人\n",q2num);
		}
		if(m>0&&q2num>0){
			int k=1;//用来记录是否遍历完全 
				total1=total-m;//用来 判断“在此检查过程中，一旦银行资金总额少于或等于刚才第一个队列中最后一个客户(第二种业务)被接待之前的数额，或者本次已将第二个队列检查或处理了一遍，就停止检查” 
				for(k=1;k<=q2num&&total>total1;++k){
				p1=(QNode)malloc(sizeof(customer));
				DeQueue(Q2,p1);
				printf("%d号需要交易%d元，而此时银行存款为%d，若交易则存款为%d\n",p1->id,p1->money,total,total+p1->money );
				if(total+p1->money>=0) {
					id=p1->id;
					wait[id]=time-p1->in_time ;
					printf("%d号等待了%d-%d=%d",id,time,p1->in_time,wait[id]);
					time+=average_time;
					q2num--;
					total+=m;
					printf("%d号在%d时后，从银行中交易了%d元，银行余额为%d\n",id,time-10,m,total);
				}
				else{
					EnQueue(Q2,p1);
					
				}
			} 
		}
		
	}
	printf("2.此时队列中有%d人\n",q2num);
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
