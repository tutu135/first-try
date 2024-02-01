#include<stdio.h>
#include<stdlib.h>
int n;//关键字字数
int p;//除留余数中的p 
typedef struct{
	int *elem;
	int count;//当前元素个数 
	int size;//当前容量，但我觉得在该实验中不要这个也没关系书上的 
}HashTable1;
typedef struct Node{
	int key;
	Node *next;
}Node;
typedef struct{
	Node *elem;
	int count;
	int size;
}HashTable2;
//HashTable1 HT1;
//HashTable2 HT2;
void CreateHT1(int n,int p,int a[]){
	int HT1[p]={0};
	int index,i,j,key;
	int time1[p]={0},time2[p]={0};//分别用来记录成功查找次数和不成功查找次数，后面虽然要用到average，但这里用整型应该没关系吧 
	int times;//用来临时记录次数
	float average1=0,average2=0;//记录总查找次数 
	for(i=1;i<=n;i++){//开始创建哈希表 ,刚开始这里写成了i<=p; 
		times=0;
		key=a[i];
		//printf("key=%d",a[i]); 
		index=key%p;
		while(HT1[index]!=0){
			index++;
			index=index%p;//虽然书上Hi=（H（key）+di）mod m，这里是H(key)不表，di++；而我们的程序是index++，但这其实最终的值是一样的 
			times++;
		}
		HT1[index]=key;
		time1[index]=++times;
		printf("time1[%d]=%d\n",index,time1[index]);
	}
	printf("哈希表的地址：\t") ;
	for(i=0;i<p;++i){
		printf("%d\t",i);
		if(i%19==18){
			printf("\n\t\t");
		}
	}
	printf("\n表中的关键字：\t") ;
	for(i=0;i<p;++i){
		printf("%d\t",HT1[i]);
		if(i%19==18){
			printf("\n\t\t");
		}
	}
	printf("\n成功查找次数：\t") ;
	for(i=0;i<p;++i){
		printf(" %d\t",time1[i]);
		average1+=time1[i];
		if(i%19==18){
			printf("\n\t\t");
		}
	}
	average1=average1/n;//注意求成功查找次数时是除以n，而求失败次数是除以p 
	times=1; 
	int k=0;
	while(time1[k]!=0){
		++k;
	}
	for(i=k;i>=0;--i){//求查找失败的平均长度 
		if(time1[i]==0){
			time2[i]=1;
			times=1;
		}
		else{
			times++;
			time2[i]=times;
		}
	}
	for(i=p-1;i>k;--i){//求查找失败的平均长度 
		if(time1[i]==0){
			time2[i]=1;
			times=1;
		}
		else{
			times++;
			time2[i]=times;
		}
	}
	
	
	printf("\n失败查找次数：\t") ;
	for(i=0;i<p;++i){
		printf(" %d\t",time2[i]);
		average2+=time2[i]; 
		//printf(" average2=%f ",average2) ;
		if(i%19==18){
			printf("\n\t\t");
		}
	}
	average2=average2/p;
	printf("\n查找成功的平均查找长度：%f",average1);
	printf("\n查找失败的平均查找长度：%f",average2);
	printf("\n");
	
}
void CreateHT2(int n,int p,int a[]){ 
	Node *HT2[p]={NULL};//HT[index]只起指针作用，不存放数据,不对，他指针就是指向了数据的 
	int time1[p]={0},time2[p]={0};//分别用来记录成功查找次数和不成功查找次数，后面虽然要用到average，但这里用整型应该没关系吧 
	int times;//用来临时记录次数
	float average1=0,average2=0,n1=0;//n1用来记录HT[i] !=NULL的个数，用来计算查找成功的次数 
	int index,i,j,key;
	Node *hp; 
	for(i=1;i<=n;i++){//开始创建哈希表 
		key=a[i];
		printf("key=%d ",a[i]); 
		index=key%p;
		if(HT2[index]!=NULL){
			times=0;
			printf("1");
			hp=HT2[index];
			while(hp->next!=NULL){//刚开始我这里写的是hp=hp->next;
								 //但这里运行的时候可能有个问题，就是hp如果被赋值了NULL， 
								 //程序可能会终止 
			hp=hp->next;
			times++;
			}
			time1[index]=++times;
			printf("here\n");
			hp->next =(Node*)malloc(sizeof(Node));
			hp=hp->next;
			hp->key =key;
			hp->next =NULL;//看来这句话还是挺重要的，但为什么我以前的时候好像没加这句话都不会报错 
		} 
		else{
			printf("2\n");
			hp=(Node*)malloc(sizeof(Node));
			hp->key =key;
			hp->next =NULL;
			HT2[index]=hp;
			
			
		} 
	}
	for(i=0;i<p;++i){//输出 这里是小于p 
		printf("地址为%d的关键字:",i);
		if(HT2[i]!=NULL){
			times=1;
			hp=HT2[i];
			while(hp!=NULL){
				n1++;
				printf("%d ",hp->key );
				average1+=times;
				printf("%d \t",times++);
				if(i%19==18){
					printf("\n");
				}
				hp=hp->next ;
			} 
			time2[i]=times;
			printf("失败查找次数为%d",time2[i]);
			average2+=time2[i]; 
		}
		else{
			printf("- 0 失败查找次数为1");
			average2+=1;
		}
		printf("\n");
	}
	printf("HT2creat successful!"); 
	average1=average1/n1;
	average2=average2/p;
	printf("\n查找成功的平均查找长度：%f",average1);
	printf("\n查找失败的平均查找长度：%f",average2);
	printf("\n");
}
int main(){
	FILE *fp;
   int num;//用来从文件中读入数字 
   fp = fopen("D:\\1大学\\数据结构\\实验\\hush_t\\hush1.txt", "r");
   if (fp == NULL) {
      printf("无法打开文件\n");
      return 1;
   }
   fscanf(fp, "%d", &n);
   printf("n=%d\n",n);//读入关键字数； 
   int i=1,a[1000]={0};
   while (i<=n) {
      fscanf(fp, "%d", &a[i]) != EOF;
	  printf("%d ", a[i]);
	  ++i;
   }
	fscanf(fp, "%d", &p) ;//读入p 
	printf("\n%d\n",p);
   fclose(fp);
	CreateHT1(n,p,a);
	CreateHT2(n,p,a);
   return 0;

	
	 
}

