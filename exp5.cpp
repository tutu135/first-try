#include<stdio.h>
#include<stdlib.h>
int n;//�ؼ�������
int p;//���������е�p 
typedef struct{
	int *elem;
	int count;//��ǰԪ�ظ��� 
	int size;//��ǰ���������Ҿ����ڸ�ʵ���в�Ҫ���Ҳû��ϵ���ϵ� 
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
	int time1[p]={0},time2[p]={0};//�ֱ�������¼�ɹ����Ҵ����Ͳ��ɹ����Ҵ�����������ȻҪ�õ�average��������������Ӧ��û��ϵ�� 
	int times;//������ʱ��¼����
	float average1=0,average2=0;//��¼�ܲ��Ҵ��� 
	for(i=1;i<=n;i++){//��ʼ������ϣ�� ,�տ�ʼ����д����i<=p; 
		times=0;
		key=a[i];
		//printf("key=%d",a[i]); 
		index=key%p;
		while(HT1[index]!=0){
			index++;
			index=index%p;//��Ȼ����Hi=��H��key��+di��mod m��������H(key)����di++�������ǵĳ�����index++��������ʵ���յ�ֵ��һ���� 
			times++;
		}
		HT1[index]=key;
		time1[index]=++times;
		printf("time1[%d]=%d\n",index,time1[index]);
	}
	printf("��ϣ��ĵ�ַ��\t") ;
	for(i=0;i<p;++i){
		printf("%d\t",i);
		if(i%19==18){
			printf("\n\t\t");
		}
	}
	printf("\n���еĹؼ��֣�\t") ;
	for(i=0;i<p;++i){
		printf("%d\t",HT1[i]);
		if(i%19==18){
			printf("\n\t\t");
		}
	}
	printf("\n�ɹ����Ҵ�����\t") ;
	for(i=0;i<p;++i){
		printf(" %d\t",time1[i]);
		average1+=time1[i];
		if(i%19==18){
			printf("\n\t\t");
		}
	}
	average1=average1/n;//ע����ɹ����Ҵ���ʱ�ǳ���n������ʧ�ܴ����ǳ���p 
	times=1; 
	int k=0;
	while(time1[k]!=0){
		++k;
	}
	for(i=k;i>=0;--i){//�����ʧ�ܵ�ƽ������ 
		if(time1[i]==0){
			time2[i]=1;
			times=1;
		}
		else{
			times++;
			time2[i]=times;
		}
	}
	for(i=p-1;i>k;--i){//�����ʧ�ܵ�ƽ������ 
		if(time1[i]==0){
			time2[i]=1;
			times=1;
		}
		else{
			times++;
			time2[i]=times;
		}
	}
	
	
	printf("\nʧ�ܲ��Ҵ�����\t") ;
	for(i=0;i<p;++i){
		printf(" %d\t",time2[i]);
		average2+=time2[i]; 
		//printf(" average2=%f ",average2) ;
		if(i%19==18){
			printf("\n\t\t");
		}
	}
	average2=average2/p;
	printf("\n���ҳɹ���ƽ�����ҳ��ȣ�%f",average1);
	printf("\n����ʧ�ܵ�ƽ�����ҳ��ȣ�%f",average2);
	printf("\n");
	
}
void CreateHT2(int n,int p,int a[]){ 
	Node *HT2[p]={NULL};//HT[index]ֻ��ָ�����ã����������,���ԣ���ָ�����ָ�������ݵ� 
	int time1[p]={0},time2[p]={0};//�ֱ�������¼�ɹ����Ҵ����Ͳ��ɹ����Ҵ�����������ȻҪ�õ�average��������������Ӧ��û��ϵ�� 
	int times;//������ʱ��¼����
	float average1=0,average2=0,n1=0;//n1������¼HT[i] !=NULL�ĸ���������������ҳɹ��Ĵ��� 
	int index,i,j,key;
	Node *hp; 
	for(i=1;i<=n;i++){//��ʼ������ϣ�� 
		key=a[i];
		printf("key=%d ",a[i]); 
		index=key%p;
		if(HT2[index]!=NULL){
			times=0;
			printf("1");
			hp=HT2[index];
			while(hp->next!=NULL){//�տ�ʼ������д����hp=hp->next;
								 //���������е�ʱ������и����⣬����hp�������ֵ��NULL�� 
								 //������ܻ���ֹ 
			hp=hp->next;
			times++;
			}
			time1[index]=++times;
			printf("here\n");
			hp->next =(Node*)malloc(sizeof(Node));
			hp=hp->next;
			hp->key =key;
			hp->next =NULL;//������仰����ͦ��Ҫ�ģ���Ϊʲô����ǰ��ʱ�����û����仰�����ᱨ�� 
		} 
		else{
			printf("2\n");
			hp=(Node*)malloc(sizeof(Node));
			hp->key =key;
			hp->next =NULL;
			HT2[index]=hp;
			
			
		} 
	}
	for(i=0;i<p;++i){//��� ������С��p 
		printf("��ַΪ%d�Ĺؼ���:",i);
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
			printf("ʧ�ܲ��Ҵ���Ϊ%d",time2[i]);
			average2+=time2[i]; 
		}
		else{
			printf("- 0 ʧ�ܲ��Ҵ���Ϊ1");
			average2+=1;
		}
		printf("\n");
	}
	printf("HT2creat successful!"); 
	average1=average1/n1;
	average2=average2/p;
	printf("\n���ҳɹ���ƽ�����ҳ��ȣ�%f",average1);
	printf("\n����ʧ�ܵ�ƽ�����ҳ��ȣ�%f",average2);
	printf("\n");
}
int main(){
	FILE *fp;
   int num;//�������ļ��ж������� 
   fp = fopen("D:\\1��ѧ\\���ݽṹ\\ʵ��\\hush_t\\hush1.txt", "r");
   if (fp == NULL) {
      printf("�޷����ļ�\n");
      return 1;
   }
   fscanf(fp, "%d", &n);
   printf("n=%d\n",n);//����ؼ������� 
   int i=1,a[1000]={0};
   while (i<=n) {
      fscanf(fp, "%d", &a[i]) != EOF;
	  printf("%d ", a[i]);
	  ++i;
   }
	fscanf(fp, "%d", &p) ;//����p 
	printf("\n%d\n",p);
   fclose(fp);
	CreateHT1(n,p,a);
	CreateHT2(n,p,a);
   return 0;

	
	 
}

