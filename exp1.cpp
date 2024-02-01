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
	float	coef;//ϵ�� 
	int		expn;//ָ�� 
}term,elemtype;//���ﶨ����elemtype 
typedef struct LNode{//������� 
	elemtype 	data;
	struct LNode *next;
}*Link,*Position;

/*typedef struct {//�������� 
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
	p->data.coef=e.coef;//ָ������Ҫָ��ṹ���е�Ԫ��Ҫ��->
	p->data.expn=e.expn;
}
void ElemInsert(Link &p,Link p2){//������ʽ�е�������������ʽ��,p1Ϊ����ʽ��ͷ����ָ��,p2ΪҪ����Ľ���ָ�� 
	  Link p1=p;
	  //printf("a��%d��",p->data.expn); 
	  while(p1->next !=NULL&&p2->data .expn >p1->next->data.expn ){//�������ж���һ������Ƿ���ں��ٱȽϽ���ָ�� 
	  	p1=p1->next ; 
	  
	  }
	  
	 //printf("b��%d��",p->data.expn);
	  if(p1->next !=NULL&&p2->data .expn ==p1->next->data.expn){//ǰ����Ҫ���� p1->next !=NULL��û����������е�ʱ�����ֱ��ͣ�� 
	  	p1->next->data.coef+=p2->data .coef;
	  	//printf("1\n");
	  }
	  else {
	   // printf("2\n");
	  	(p->data.expn)++;//ͷ����ָ���Ŀռ�������Ŷ���ʽ������
	  	p2->next =p1->next ;
	  	p1->next =p2;
	  	p1=p;//�����Ӧ��ָ�뷵�ص�ͷ���
	  }
}
void CreatPolyn(Link &p){
	//����m���ϵ����ָ����������ʾһԪ����ʽ����������P
	LNode *h;
	p->data.expn =0;
	p->next =NULL;  
	//InitList(p);
	h=p ;
	elemtype e;
	//e.coef =0;e.expn =-1;SetCurElem(h,e);
	Link p2;
	for(int i=1;e.expn !=10000;++i){
		printf("�������%d���ϵ����ָ������ָ����10000ʱ��ʾ�������\n",i);
		scanf("%f %d",&e.coef,&e.expn  );
		if(e.expn !=10000){
		
		
		p2=(Link)malloc(sizeof(LNode));
		p2->data =e;
		ElemInsert(h,p2);
	//	printf("c��%d��",p->data.expn); 
		}
	}
	
 
}//���ﻹûд��
 
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
		printf("�ö���ʽ������");return 0;
	}
	Link p1=p;
	int num=p1->data.expn;
	printf("����ʽ����Ϊ%d\n",num);

	int i=1;
	while(i<=num){
		p1=p1->next;
		float coef= p1->data.coef;
		int expn=p1->data.expn;
		printf("%f %d\n",coef ,expn);
		i++;//�����ҵ����bug���Ҹո���仰û�ӣ����ÿ�����е�ʱ�����е���ӡ������ͣ�ˣ� 
	}  
	//printf("hhhhh"); 
	//free��p1�� ;��������仰��������仰�������ֵ�ͣ 
}
int PolynLength(Link p){
	
}
void AddPolyn(Link &pa,Link pb,Link pc){//pb,pc��Ӻ󣬰�Ԫ�ط���p1 ���������е�������paΪʲôҲҪ�����ò�������Ϊ�G��û�ӵ�ʱ�����ͱ����� 
	Link p1,p2,p3,p4;
	int i=1,j=1,pblen,pclen;//������¼�Ƿ񵽽��ĵ�ĩβ
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
			//printf("������");printf("sum=%f",sum);
					if (sum!=0.0){
						p1->data =p2->data ;p1->data.coef =sum;pa->data.expn++;
						++i;++j;p2=p2->next ;p3=p3->next ;p4=(Link)malloc(sizeof(LNode));
						p1->next =p4;
						p1=p1->next ;break;
					}
					else {++i;++j;p2=p2->next ;p3=p3->next ;break;}//ÿһ��case����һ��Ҫ�ǵü�break����Ⱦ�ͻ����ִ����ȥ 
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
void Subtractpolyn(Link &pa,Link pb,Link pc){//����ʽpb-pc 
	Link p1,p2,p3,p4;
	int i=1,j=1,pblen,pclen;//������¼�Ƿ񵽽��ĵ�ĩβ
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
				p1->data=p2->data ;pa->data.expn++;p2=p2->next ;++i;printf("-1�����+1\n");
				p4=(Link)malloc(sizeof(LNode));
				p1->next =p4;
				p1=p1->next ;
			}
			if(c==0){
					sub=p2->data.coef -p3->data.coef ;
					if (sub!=0.0){
						p1->data =p2->data ;p1->data.coef =sub;pa->data.expn++;
						++i;++j;p2=p2->next ;p3=p3->next ;printf("0�����+1\n");
						p4=(Link)malloc(sizeof(LNode));
		                p1->next =p4;
					    p1=p1->next ;
					}
					else {++i;++j;p2=p2->next ;p3=p3->next ;
					    
					}
			}
			if(c==1){
			printf("%d ",c );printf("%d%d ",p2->data.expn  ,p3->data.expn );p1->data=p3->data;p1->data.coef=-p1->data.coef;pa->data.expn++;p3=p3->next ;++j;printf("1�����+1\n");
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
		printf("ִ������仰1\n");
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
	float sum=0;//������¼f(x)��ֵ 
	int i=1;
	while(i<=len){
		p1=p1->next;
		float coef= p1->data.coef;
		int expn=p1->data.expn;
		if(x==0&&expn==-1){
			printf("����");return 0;
		}
		else{
			sum+=coef*pow(x,expn);
			i++;
		}
	}  
	printf("������ֵΪ%f",sum);
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
		printf("��ѡ��Ľ���Ѿ������ö���ʽ�����һ�������");
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
	p->data.expn--;//ɾ����Ԫ��֮��Ҫ�ǵø�����ʽ�ĳ��ȼ�1���տ�ʼ��û�������Ȼ���ҵ����������ʽ�ĺ����ǣ���Ϊ����ʽ���������ˣ�����ָ��Ӧ����ָ����ָ���ˣ����������е������� 
}
ChangeCoef(Link &p,int n ,float coef,int expn){//������ʽp�ĵ�n������ϵ����Ϊcoef
	/* Link p1=p;
	 int i;
	 p1=p1->next ;
	 if(n>p1->data.expn){
	 	printf("�˶���ʽû�е�%d�����",n);
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
	printf("1.�����µĽ��\n2.ɾ�����н��\n3.�޸����н���ϵ��\n");
	scanf("%d",&c);
	int n;
	switch(c){
		case 1:printf("���������ϵ��������");scanf("%f %d",&e.coef,&e.expn);p1->data=e;ElemInsert(p,p1);break; //�����p�Ƕ����� 
		case 2:printf("Ҫɾ���ڼ�����㣿");scanf("%d",&n);DeletNode(p,n);break;
		case 3:printf("������Ҫ�ı�ڼ�������ϵ������ϵ����Ϊ����ָ����Ϊ��\n");scanf("%d %f %d",&n,&coef,&expn);ChangeCoef(p,n,coef,expn);break;
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
	float sum1=0;float sum2=0;//������¼f(x)��ֵ 
	int i=1;
	elemtype lnx1,lnx2;//������¼ln 
	int flag=0;//������¼�Ƿ���lnx 
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
		printf("������ֵΪ%f",sum2-sum1);
	}
	else{
		printf("������ֵΪ%f-%fln(%f)+%fln(%f)",sum2-sum1,lnx1.coef,x1,lnx2.coef ,x2);
	}

	
}
int main(){
	Link p[10];//ʮ������ʽ��ͷָ�룬ָ��ͷ��� 
	//��ʹ��ָ��ʱָ�벻��Ϊ�գ��Ҹտ�ʼ��Ϊ���ԭ�򣬳��򼸺���û��ʼ�ܾͽ����� 
	int pnum=0;//������¼��ǰ����ʽ�ĸ��� 
	int c,time;
	float x1,x2;
	int xiaohui[10];
    while(1){
	printf("1.���벢��������ʽ\n2.�������ʽ\n3.��ͣ�����ʽ���\n4.������ʽ���\n5.��ֵ\n");
	printf("6.����\n7.���\n8.�޸�\n9.��������\n10.����ʽ��΢��\n11.����ʽ�Ĳ�������\n12.����ʽ�Ķ�����\n");
	scanf("%d",&c);
	if(c==9) return 0; 
	switch(c){
		case 1:p[pnum]=(Link)malloc(sizeof(LNode));
				CreatPolyn(p[pnum]);
				pnum++; 
				break;
		case 2:printf("����Ҫ����ڼ�������ʽ�����㿪ʼ��\n");
				int i;
				scanf("%d",&i);
				if(i>=pnum){printf("�������ʽ������ѽ\n");break;	}
				PrintPolyn(p[i]);
				break;
		case 3:int n1,n2;
			   printf("��������/Ůʿ��Ҫ������������ʽ����أ�\n"); 
			   scanf("%d %d",&n1,&n2);
			   if(n1>=pnum ||n2>=pnum) {printf("������˼����ѡ���������ʽ�����������ڰ�\n");break;} 
			   printf("���ϣ���Ͱ����Ѷ���ʽ���������\n");
			   AddPolyn(p[pnum],p[n1],p[n2]);// ���ú���ʱ����ǰ�治Ҫ�Ӳ������� 
			   printf("����Ӻ�õ����¶���ʽ��С�İ���ŵ���%d������ʽ����\n",pnum);
			   pnum++;//��pnum������ʽ�ǻ�û�ù��ģ������Ҿ����õ���Ȼ����++ 
			   break;
		case 4:
			   printf("��������/Ůʿ��Ҫ������������ʽ����أ�������ĵڶ������ᱻ��Ϊ�����Ķ���ʽ\n"); 
			   scanf("%d %d",&n1,&n2);
			   if(n1>=pnum ||n2>=pnum) {printf("������˼����ѡ���������ʽ�����������ڰ�\n");break;} 
			   printf("���ϣ���Ͱ����Ѷ���ʽ���\n");
			   Subtractpolyn(p[pnum],p[n1],p[n2]); 
			   printf("�������õ����¶���ʽ��С�İ���ŵ���%d������ʽ����\n",pnum);
			   pnum++; 
			   break;   
		case 5:printf("������x�Լ���Ҫ��x�����ĸ�����ʽ");float x;
				scanf("%f %d",&x,&n1);//scanf�����ǵü�Ӧ�ò��� 
				if(n1>=pnum){printf("������˼����ѡ���������ʽ�����������ڰ�\n");break;}
				function(x,p[n1]) ;break;
		case 6: printf("��������Ҫ���ٵĶ���ʽ");
				scanf("%d",&n1);
				if(n1>=pnum){printf("������˼����ѡ���������ʽ�����������ڰ�\n");break;}
				DestoryPoly(p[n1]);break;
		case 7:printf("��������Ҫ��յĶ���ʽ");
				scanf("%d",&n1);
				if(n1>=pnum){printf("������˼����ѡ���������ʽ�����������ڰ�\n");break;}
				ClearPoly(p[n1]);break;
		case 8:printf("��Ҫ�޸��ĸ�����ʽ�������룺");
			   scanf("%d",&n1);
			   if(n1>=pnum){printf("������˼����ѡ���������ʽ�����������ڰ�\n");break;}
			   EditPoly(p[n1]);break;
		case 10:printf("��Ҫ΢���ĸ�����ʽ�������룺");
			   scanf("%d",&n1);
			   if(n1>=pnum){printf("������˼����ѡ���������ʽ�����������ڰ�\n");break;}
			   printf("��Ҫ΢�ּ��Σ�");
			   scanf("%d",&time); 
 				for(int i=1;i<=time;++i){
 					if(i>1){
 						DifferentialPoly(p[pnum],p[pnum-1]);pnum++;
					 }
					 else{DifferentialPoly(p[pnum],p[n1]);pnum++;
					 }
				 }
				 printf("������%d��\n",pnum-1);
			   break;
		case 11:printf("��Ҫ���������ĸ�����ʽ�������룺");
			   scanf("%d",&n1);
			   if(n1>=pnum){printf("������˼����ѡ���������ʽ�����������ڰ�\n");break;}
			   IndefinitePoly(p[pnum],p[n1]);pnum++;printf("������%d��\n",pnum-1);
			   break;
		case 12:printf("��Ҫ�������ĸ�����ʽ�������룺");
			   scanf("%d",&n1);
			   if(n1>=pnum){printf("������˼����ѡ���������ʽ�����������ڰ�\n");break;}
			   printf("���������޺�����");
			   scanf("%f %f",&x1,&x2); 
			   DefinitePoly(p[pnum],p[n1],x1,x2);pnum++;printf("����������%d��\n",pnum-1);
			   break;
		//case 9:return 0; 
	}
	}
	
} 
