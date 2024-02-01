#include <stdio.h>
/*#define TRUE 		1
#define FALSE 		0
#define OK			1
#define ERROR 		0
#define INFEASIBLE 	-1
#define OVERFLOW	-2	
typedef	int	Status;
*/
#define LIST_INIT_SIZE 	100
#define INCREAMENT 		10
#include<malloc.h>
#include<math.h>

typedef struct {
	float	coef;//系数 
	int		expn;//指数 
}term,elemtype;//这里定义了elemtype 
typedef struct LNode{//结点类型 
	elemtype 	data;
	struct LNode *next;
}*Link,*Position;

/*typedef struct {//链表类型 
	Link head,tail; 
	int len;
 }LinkList;
typedef LinkList polynomial;*/ 
/*int InitList( LinkList &L){
	L.head =(LNode*)malloc(sizeof(LNode));
	L.len =0;
	L.tail =NULL;
	
}*/
int cmp(term a,term b){
	if(a.expn>b.expn )		 return 1;
	else if(a.expn <b.expn )	return -1;
	else			         return 0;
}

void SetCurElem(Link p,elemtype e){
	p->data.coef=e.coef;//指针类型要指向结构体中的元素要用->
	p->data.expn=e.expn;
}
void ElemInsert(Link &p,Link p2){//将多项式中的项有序插入多项式中,p1为多项式的头结点的指针,p2为要插入的结点的指针 
	  Link p1=p;
	  //printf("a有%d项",p->data.expn); 
	  while(p1->next !=NULL&&p2->data .expn >p1->next->data.expn ){//这里先判断下一个结点是否存在后再比较结点的指数 
	  	p1=p1->next ; 
	  
	  }
	  
	 //printf("b有%d项",p->data.expn);
	  if(p1->next !=NULL&&p2->data .expn ==p1->next->data.expn){//前面需要加上 p1->next !=NULL，没叫这句我运行的时候程序直接停了 
	  	p1->next->data.coef+=p2->data .coef;
	  	//printf("1\n");
	  }
	  else {
	   // printf("2\n");
	  	(p->data.expn)++;//头结点的指数的空间用来存放多项式的项数
	  	p2->next =p1->next ;
	  	p1->next =p2;
	  	p1=p;//插入后应将指针返回到头结点
	  }
}
void CreatPolyn(Link &p){
	//输入m项的系数和指数，建立表示一元多项式的有序链表P
	LNode *h;
	p->data.expn =0;
	p->next =NULL;  
	//InitList(p);
	h=p ;
	elemtype e;
	//e.coef =0;e.expn =-1;SetCurElem(h,e);
	Link p2;
	for(int i=1;e.expn !=10000;++i){
		printf("请输入第%d项的系数与指数：当指数项10000时表示输入结束\n",i);
		scanf("%f %d",&e.coef,&e.expn  );
		if(e.expn !=10000){
		
		
		p2=(Link)malloc(sizeof(LNode));
		p2->data =e;
		ElemInsert(h,p2);
	//	printf("c有%d项",p->data.expn); 
		}
	}
	
 
}//这里还没写完
 
void DestoryPoly(Link &p){
	Link p1=p,p2;
	int num=p1->data.expn;
	p1->data.expn =0;
	p1=p1->next ;
	p2=p1;
	int i=2;
	while(i<=num){
		p1=p1->next;
		free(p2);
		p2=p1;
		i++;
	}  
	p=NULL;
}
int PrintPolyn(Link p){
	if(p==NULL){
		printf("该多项式已销绘");return 0;
	}
	Link p1=p;
	int num=p1->data.expn;
	printf("多项式项数为%d\n",num);

	int i=1;
	while(i<=num){
		p1=p1->next;
		float coef= p1->data.coef;
		int expn=p1->data.expn;
		printf("%f %d\n",coef ,expn);
		i++;//终于找到这个bug，我刚刚这句话没加，结果每次运行的时候运行到打印这程序就停了； 
	}  
	//printf("hhhhh"); 
	//free（p1） ;不能有这句话，加量这句话，程序又得停 
}
int PolynLength(Link p){
	
}
void AddPolyn(Link &pa,Link pb,Link pc){//pb,pc相加后，把元素放在p1 ，不过我有点好奇这个pa为什么也要加引用参数，因为欸我没加的时候程序就报错了 
	Link p1,p2,p3,p4;
	int i=1,j=1,pblen,pclen;//用来记录是否到结点的的末尾
	float sum; 
	
	pblen=pb->data.expn;
	pclen=pc->data.expn; 
	
	p1=(Link)malloc(sizeof(LNode));
	
	pa=p1;
	pa->data.expn=0;
	p4=(Link)malloc(sizeof(LNode));
	p1->next =p4;
	p1=p1->next;
	
	p2=pb->next ;p3=pc->next ;
	
	while(i<=pblen&&j<=pclen){
		switch(cmp(p2->data ,p3->data )){
			case -1:p1->data=p2->data ;pa->data.expn++;p2=p2->next ;++i;p4=(Link)malloc(sizeof(LNode));
				p1->next =p4;
				p1=p1->next ;break;
			case 0 :sum=p2->data.coef +p3->data.coef ;
			//printf("这这这");printf("sum=%f",sum);
					if (sum!=0.0){
						p1->data =p2->data ;p1->data.coef =sum;pa->data.expn++;
						++i;++j;p2=p2->next ;p3=p3->next ;p4=(Link)malloc(sizeof(LNode));
						p1->next =p4;
						p1=p1->next ;break;
					}
					else {++i;++j;p2=p2->next ;p3=p3->next ;break;}//每一个case后面一定要记得加break，不染就会继续执行下去 
			case 1 :p1->data=p3->data ;pa->data.expn++;p3=p3->next ;++j;p4=(Link)malloc(sizeof(LNode));
					p1->next =p4;
					p1=p1->next ;break;
				
		}
	
		
		//printf("expn=%d",pa->data.expn);
	}
	while(i<=pblen){
		p1->data=p2->data ;pa->data.expn++;p2=p2->next ;++i;
		p4=(Link)malloc(sizeof(LNode));
		p1->next =p4;
		p1=p1->next ;
	}
	while(j<=pclen){
		p1->data=p3->data ;pa->data.expn++;p3=p3->next ;++j;
		p4=(Link)malloc(sizeof(LNode));
		p1->next =p4;
		p1=p1->next ;
	}
	
	
}
void Subtractpolyn(Link &pa,Link pb,Link pc){//多项式pb-pc 
	Link p1,p2,p3,p4;
	int i=1,j=1,pblen,pclen;//用来记录是否到结点的的末尾
	float sub; 
	
	pblen=pb->data.expn;
	pclen=pc->data.expn; 
	
	p1=(Link)malloc(sizeof(LNode));
	
	pa=p1;
	pa->data.expn=0;
	p4=(Link)malloc(sizeof(LNode));
	p1->next =p4;
	p1=p1->next;
	
	p2=pb->next ;p3=pc->next ;
	
	while(i<=pblen&&j<=pclen){
		int c;
		c= cmp(p2->data ,p3->data );
		printf("%d ",c );
			if(c==-1){
				p1->data=p2->data ;pa->data.expn++;p2=p2->next ;++i;printf("-1的语句+1\n");
				p4=(Link)malloc(sizeof(LNode));
				p1->next =p4;
				p1=p1->next ;
			}
			if(c==0){
					sub=p2->data.coef -p3->data.coef ;
					if (sub!=0.0){
						p1->data =p2->data ;p1->data.coef =sub;pa->data.expn++;
						++i;++j;p2=p2->next ;p3=p3->next ;printf("0的语句+1\n");
						p4=(Link)malloc(sizeof(LNode));
		                p1->next =p4;
					    p1=p1->next ;
					}
					else {++i;++j;p2=p2->next ;p3=p3->next ;
					    
					}
			}
			if(c==1){
			printf("%d ",c );printf("%d%d ",p2->data.expn  ,p3->data.expn );p1->data=p3->data;p1->data.coef=-p1->data.coef;pa->data.expn++;p3=p3->next ;++j;printf("1的语句+1\n");
		    p4=(Link)malloc(sizeof(LNode));
		    p1->next =p4;
			p1=p1->next ;
			}
		
		
		
		printf("expn=%d ",pa->data.expn);
	}
	while(i<=pblen){
		printf("i=%d,pblen=%d,j=%d,pclen=%d\n",i,pblen,j,pclen);
		printf("data:%f %d\n",p2->data.coef ,p2->data.expn );
		p1->data=p2->data ;pa->data.expn++;p2=p2->next ;++i;
		
		p4=(Link)malloc(sizeof(LNode));
		p1->next =p4;
		p1=p1->next ;
		printf("执行了这句话1\n");
	}
	while(j<=pclen){
		printf("i=%d,pblen=%d,j=%d,pclen=%d\n",i,pblen,j,pclen);
		printf("data:%f %d\n",p3->data.coef ,p3->data.expn );
		p1->data=p3->data;p1->data.coef=-(p1->data.coef);pa->data.expn++;p3=p3->next ;++j;
		p4=(Link)malloc(sizeof(LNode));
		p1->next =p4;
		p1=p1->next ;
		printf("2\n");
	}
	
}
int  function(float x,Link p){
	Link p1=p;
	int len=p1->data.expn;
	float sum=0;//用来记录f(x)的值 
	int i=1;
	while(i<=len){
		p1=p1->next;
		float coef= p1->data.coef;
		int expn=p1->data.expn;
		if(x==0&&expn==-1){
			printf("报错！");return 0;
		}
		else{
			sum+=coef*pow(x,expn);
			i++;
		}
	}  
	printf("代入后的值为%f",sum);
}
void ClearPoly(Link &p){
	/*Link p1=p;
	int num=p1->data.expn;
	p1=p1->next ;
	int i=1;
	while(i<=num){
		p1->data.coef =0;
		p1->data.expn =0;
		p1=p1->next; 
		i++;
	}*/
	Link p1=p,p2;
	int num=p1->data.expn;
	p1->data.expn =0;
	p1=p1->next ;
	p2=p1;
	int i=2;
	while(i<=num){
		p1=p1->next;
		free(p2);
		p2=p1;
		i++;  
}} 
void DeletNode(Link &p,int n){
	int i=1;
	Link p1=p,p2;
	p1=p1->next ;
	if(n>p->data.expn){
		printf("您选择的结点已经超过该多项式的最后一个结点了");
	}
	else if(n==1){
		p->next=p->next->next;
	}	
	else{
		while(i<n){
			p2=p1;
			p1=p1->next; 
			++i;
		}
		if(n==p->data.expn){
			p2->next =NULL;
			free(p1);
			
		}
		else {
			p2->next=p1->next ;
			free(p1);
		}
	}
	p->data.expn--;//删除了元素之后要记得给多项式的长度减1，刚开始我没加这个，然后我调用输出多项式的函数是，因为多项式长度忘减了，所以指针应该是指到空指针了，结果程序就中道崩殂了 
}
ChangeCoef(Link &p,int n ,float coef,int expn){//将多项式p的第n个结点的系数改为coef
	/* Link p1=p;
	 int i;
	 p1=p1->next ;
	 if(n>p1->data.expn){
	 	printf("此多项式没有第%d个结点",n);
	 }
	 else{
	 	while(i<n){
	 		++i;
	 		p1=p1->next ;
		}
		p1->data.coef=coef;} */
	Link p1;
	p1=(Link)malloc(sizeof(LNode));
	p1->data.coef =coef;p1->data.expn =expn;
	DeletNode(p,n);ElemInsert(p,p1);
	 
}
void EditPoly(Link &p){
	int n1,c;
	elemtype e;
	float coef;
	int expn;
	Link p1;p1=(Link)malloc(sizeof(LNode));
	printf("1.插入新的结点\n2.删除已有结点\n3.修改已有结点的系数\n");
	scanf("%d",&c);
	int n;
	switch(c){
		case 1:printf("请输入结点的系数和项数");scanf("%f %d",&e.coef,&e.expn);p1->data=e;ElemInsert(p,p1);break; //这里的p是定义在 
		case 2:printf("要删除第几个结点？");scanf("%d",&n);DeletNode(p,n);break;
		case 3:printf("请输入要改变第几个结点的系数？将系数改为？将指数改为？\n");scanf("%d %f %d",&n,&coef,&expn);ChangeCoef(p,n,coef,expn);break;
	} 
	 
}


void DifferentialPoly(Link &p,Link p1){
   	 
	 Link p2,p3;
   	  p=(Link)malloc(sizeof(LNode));
   	  p->data.expn =0;
   	  p->next =NULL; 
   	int num;int i=1;
	   num=p1->data.expn ;	
	   p2=p1;
	   p2=p2->next ;
	   
	   //printf("dao\n");	
	while(i<=num){
		//printf("dao%d\n",i);
		if(p2->data.expn !=0){
		//	printf("p2->data.expn=%d",p2->data.expn);
			p3=(Link)malloc(sizeof(LNode));
			p3->data.coef =p2->data.coef*p2->data.expn ;
			p3->data.expn =p2->data.expn -1;
			//printf("here");
			ElemInsert(p,p3);	
			//printf("hahah");
		}
		i++;
		p2=p2->next ;
	}  
}
int IndefinitePoly(Link &p,Link p1){
	Link p2,p3;
   	  p=(Link)malloc(sizeof(LNode));
   	  p->data.expn =0;
   	  p->next =NULL; 
   	int num;int i=1;
	   num=p1->data.expn ;	
	   p2=p1;
	   p2=p2->next ;
	   
	   //printf("dao\n");	
	while(i<=num){
		//printf("dao%d\n",i);
		if(p2->data.expn ==-1){
			//printf("p2->data.expn=%d",p2->data.expn);
			p3=(Link)malloc(sizeof(LNode));
			p3->data.coef =p2->data.coef ;
			p3->data.expn =1000;
			//printf("here");
			ElemInsert(p,p3);	
		//	printf("hahah");
		}
		else{
			p3=(Link)malloc(sizeof(LNode));
			p3->data.coef =p2->data.coef/(p2->data.expn+1) ;
			p3->data.expn=(p2->data.expn+1);
			//printf("here");
			ElemInsert(p,p3);
		}
		i++;
		p2=p2->next ;
	}  
}
void DefinitePoly(Link &p0,Link p,float x1,float x2){
	p0=(Link)malloc(sizeof(LNode));
	IndefinitePoly(p0,p);
	Link p1=p0;
	int len=p1->data.expn;
	float sum1=0;float sum2=0;//用来记录f(x)的值 
	int i=1;
	elemtype lnx1,lnx2;//用来记录ln 
	int flag=0;//用来记录是否有lnx 
	printf("dao1");
	
	while(i<=len){
		p1=p1->next;
		float coef= p1->data.coef;
		int expn=p1->data.expn;
		if (expn!=1000){
			sum1+=coef*pow(x1,expn);
			i++;
			printf("dao1i=%d\n",i);
		}
		else{
			lnx1=p1->data ;
			printf("dao2i=%d",i);
			++i;
			flag=1;
		}
	} 
	i=1;  p1=p0;
	while(i<=len){
		p1=p1->next;
		float coef= p1->data.coef;
		int expn=p1->data.expn;
		if (expn!=1000){
			sum2+=coef*pow(x2,expn);
			i++;
		}
		else{
			lnx2=p1->data ;++i;flag=1;
		}
	}  
	if(flag==0){
		printf("代入后的值为%f",sum2-sum1);
	}
	else{
		printf("代入后的值为%f-%fln(%f)+%fln(%f)",sum2-sum1,lnx1.coef,x1,lnx2.coef ,x2);
	}

	
}
int main(){
	Link p[10];//十个多项式的头指针，指向头结点 
	//当使用指针时指针不能为空，我刚开始因为这个原因，程序几乎还没开始跑就结束了 
	int pnum=0;//用来记录当前多项式的个数 
	int c,time;
	float x1,x2;
	int xiaohui[10];
    while(1){
	printf("1.输入并创建多项式\n2.输出多项式\n3.求和：多项式相加\n4.求差：多项式相减\n5.求值\n");
	printf("6.销毁\n7.清空\n8.修改\n9.结束程序\n10.多项式的微分\n11.多项式的不定积分\n12.多项式的定积分\n");
	scanf("%d",&c);
	if(c==9) return 0; 
	switch(c){
		case 1:p[pnum]=(Link)malloc(sizeof(LNode));
				CreatPolyn(p[pnum]);
				pnum++; 
				break;
		case 2:printf("你想要输出第几个多项式（从零开始）\n");
				int i;
				scanf("%d",&i);
				if(i>=pnum){printf("这个多项式不存在呀\n");break;	}
				PrintPolyn(p[i]);
				break;
		case 3:int n1,n2;
			   printf("请问先生/女士您要将哪两个多项式相加呢？\n"); 
			   scanf("%d %d",&n1,&n2);
			   if(n1>=pnum ||n2>=pnum) {printf("不好意思，您选的这个多项式啊，它不存在啊\n");break;} 
			   printf("好嘞，这就帮您把多项式相加起来哈\n");
			   AddPolyn(p[pnum],p[n1],p[n2]);// 调用函数时参数前面不要加参数类型 
			   printf("您相加后得到的新多项式，小的帮你放到第%d个多项式中了\n",pnum);
			   pnum++;//第pnum个多项式是还没用过的，所以我就先用掉，然后再++ 
			   break;
		case 4:
			   printf("请问先生/女士您要将哪两个多项式相减呢？您输入的第二个将会被作为被减的多项式\n"); 
			   scanf("%d %d",&n1,&n2);
			   if(n1>=pnum ||n2>=pnum) {printf("不好意思，您选的这个多项式啊，它不存在啊\n");break;} 
			   printf("好嘞，这就帮您把多项式相减\n");
			   Subtractpolyn(p[pnum],p[n1],p[n2]); 
			   printf("您相减后得到的新多项式，小的帮你放到第%d个多项式中了\n",pnum);
			   pnum++; 
			   break;   
		case 5:printf("请输入x以及您要将x带入哪个多项式");float x;
				scanf("%f %d",&x,&n1);//scanf函数记得加应用参数 
				if(n1>=pnum){printf("不好意思，您选的这个多项式啊，它不存在啊\n");break;}
				function(x,p[n1]) ;break;
		case 6: printf("请输入您要销毁的多项式");
				scanf("%d",&n1);
				if(n1>=pnum){printf("不好意思，您选的这个多项式啊，它不存在啊\n");break;}
				DestoryPoly(p[n1]);break;
		case 7:printf("请输入您要清空的多项式");
				scanf("%d",&n1);
				if(n1>=pnum){printf("不好意思，您选的这个多项式啊，它不存在啊\n");break;}
				ClearPoly(p[n1]);break;
		case 8:printf("您要修改哪个多项式？请输入：");
			   scanf("%d",&n1);
			   if(n1>=pnum){printf("不好意思，您选的这个多项式啊，它不存在啊\n");break;}
			   EditPoly(p[n1]);break;
		case 10:printf("您要微分哪个多项式？请输入：");
			   scanf("%d",&n1);
			   if(n1>=pnum){printf("不好意思，您选的这个多项式啊，它不存在啊\n");break;}
			   printf("您要微分几次？");
			   scanf("%d",&time); 
 				for(int i=1;i<=time;++i){
 					if(i>1){
 						DifferentialPoly(p[pnum],p[pnum-1]);pnum++;
					 }
					 else{DifferentialPoly(p[pnum],p[n1]);pnum++;
					 }
				 }
				 printf("放在了%d中\n",pnum-1);
			   break;
		case 11:printf("您要不定积分哪个多项式？请输入：");
			   scanf("%d",&n1);
			   if(n1>=pnum){printf("不好意思，您选的这个多项式啊，它不存在啊\n");break;}
			   IndefinitePoly(p[pnum],p[n1]);pnum++;printf("放在了%d中\n",pnum-1);
			   break;
		case 12:printf("您要定积分哪个多项式？请输入：");
			   scanf("%d",&n1);
			   if(n1>=pnum){printf("不好意思，您选的这个多项式啊，它不存在啊\n");break;}
			   printf("请输入下限和上限");
			   scanf("%f %f",&x1,&x2); 
			   DefinitePoly(p[pnum],p[n1],x1,x2);pnum++;printf("不定放在了%d中\n",pnum-1);
			   break;
		//case 9:return 0; 
	}
	}
	
} 
