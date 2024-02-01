#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
	unsigned int weight;
	unsigned int parent,lchild,rchild;
}HTNode,* HuffmanTree;//Huffman树的结点
typedef char **HuffmanCode;
HuffmanTree HT;
HuffmanCode HC;
int *w1=(int *)malloc(256*sizeof(int));
char character[1500000];
char compresschar[1500000];
char uncompresschar[1500000];
int uncopmresscharnum=0;
int copmresscharnum=0;//压缩后的01串个数 
int charnum=0;//总的字符数，而不是字符种类
typedef struct{
	int data;
	int freq;
}HUF;
void Select(HuffmanTree HT,int n,int &s1,int &s2){
	int i=1;
	s1=0;s2=0;
	for(i=1;i<=n;++i){
		if(HT[i].parent==0){
			if(s1==0)
				s1=i;
			else if(s2==0 ){
				if(HT[i].weight <HT[s1].weight ){
					s2=s1;
					s1=i;
				}
				else{
					s2=i;
				}
			}
			else if(HT[i].weight <HT[s1].weight){
				s2=s1;
				s1=i;
			}
			else if(HT[i].weight <HT[s2].weight){
				s2=i;
			}
		}
	}
}
void readfile(int*&w1,char *goalfile,int &n,int*&w,HUF *&huf){//n用来记录字符数
	int freq[256]={0};
	int i;
	FILE *fp;
	int ch;
	fp=fopen(goalfile,"rb");
	ch =fgetc(fp);
	while(!feof(fp)){
		charnum++;
		character[charnum]=ch;//从1开始 
		printf("%d",ch);
		printf("%c ch=%d ",ch,ch);
		freq[ch]++;
		w1[ch]=freq[ch];
	    ch=fgetc(fp); 
	}
	//printf("\n");
	fclose(fp);
	for(i=0;i<256;++i){
		if(freq[i]!=0){
			n++;
		//printf("%c freq[%d]=%d\n",i,i,w1[i]);
		}
		else{
			w1[i]=0;
		}
	}
	//printf("n=%d\n",n);
	w=(int*)malloc((n+1)*sizeof(int));
	huf=(HUF*)malloc((n+1)*sizeof(HUF));
	int a[n]={0};
 	i=0;
	 int k=0;
	for(i=0, k=0;i<256;++i){
		if(w1[i]!=0){
			k++;
			a[k]=i;
			huf[k].data=i;
			huf[k].freq =w1[i];
			w[k]=w1[i];
		//printf("a[%d]=%c freq[%d]=%d\n",k,a[k],k,w[k]);
		}
		
	}
	
}
void check(){
	int i;
	for(i=1;i<=charnum;++i){
		printf("%c",character[i]);
	}
}
void HuffmanCoding(HuffmanTree &HT,HuffmanCode &HC,int *w,int n){
	//w存放n个字符的权值，构造赫夫曼树HT，并求出n个字符的赫夫曼编码HC
	printf("star to create a huffman tree\n");
	if(n<1) return;
	int m=2*n-1;//结点数
	HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode));//0号单元未用
	HuffmanTree p;
	int i;
	for (p=HT+1, i=1;i<=n;++i,++p) *p={w[i],0,0,0};
	for(;i<=m;++i,++p) *p={0,0,0,0};
	for(i=n+1;i<=m;++i){//构建Huffman树 
		//在HT[1...i-1中选择parent为0且weight最小的两个结点，其序号分别为s1和s2
	int s1,s2;
	Select(HT,i-1,s1,s2);
	//printf("s1=%d s2=%d\n",s1,s2);
	
	HT[s1].parent =i;HT[s2].parent =i;
	HT[i].lchild=s1;HT[i].rchild =s2;
	HT[i].weight =HT[s1].weight +HT[s2].weight ;	 
	}
	//----从叶子到根逆向求每个字符的Huffman编码
	HC=(HuffmanCode)malloc((n+1)*sizeof(char*));
	char *cd;
	cd=(char*)malloc(n*sizeof(char));
	cd[n-1]='\0';
	int c,f;
	for(i=1;i<=n;++i){
		int start=n-1;
		for(c=i, f=HT[i].parent ;f!=0;c=f,f=HT[f].parent ){
			if(HT[f].lchild==c) cd[--start]='0';
			else cd[--start]='1'; 
		}
		HC[i]=(char *)malloc((n)*sizeof(char));
		strcpy(HC[i],&cd[start]);
		int len;
		len=strlen(HC[i]); 
		while(len%8!=0){
			HC[i][len]='0';
			HC[i][len+1]='\0';
			//printf("%s",HC[i]);
		//	printf("the code can be here   and strlen of HC[%d] is %d\n",i,strlen(HC[i]));
			++len;
		}
	//	printf("%s",HC[i]);
		
	}
	
	free(cd);
	printf(" create successful\n");
} //HuffmanCoding
void HTcheck(HuffmanTree HT,HuffmanCode HC,int n,HUF *huf){
	
	for(int k=1;k<=n;++k){
		printf("HC[%d]=%s\n",k,HC[k]);
		printf("huf[%d].data=%d huf[%d].freq=%d\n",k,huf[k].data ,k,huf[k].freq );
	}
	for(int k=1;k<=2*n-1;++k){
		printf("i=%d weight=%d\tparent=%d\tlch=%d\trch=%d\n",k,HT[k].weight,HT[k].parent ,HT[k].lchild ,HT[k].rchild  );
	}
}
void compress(int n,char a[],char b[],HuffmanCode HC,HUF *huf){
	printf("star to compress");
	int i,k,j,p;
	j=1;//从1开始 
	for(i=1;i<=charnum;++i){
		for(k=1;k<=n;++k){
			if(a[i]==(char)huf[k].data){
				p=0;
				while(HC[k][p]!='\0'){
					//printf("yes");
					b[j]=HC[k][p];
					++j;++p;copmresscharnum++;	
				}		
			}
		}
	} 

	for(i=1;i<=copmresscharnum;++i){
		//printf("yes");
	//	printf("%c",b[i]);
	}
	printf("\n");
	printf("compress successfully\n");
	
}
void uncompress(char a[],char b[],HuffmanTree HT,int n,HUF *huf){
	uncopmresscharnum=0;
	int index=2*n-1;//索引
	int i=1,j=1,k=0;
	int flag;//记录树往哪边走 
	HuffmanTree p;
	for(i=1;i<=copmresscharnum;){
		//printf("here");
		
		//printf("%d",HT[index].lchild );
		p=HT+2*n-1;
		while(HT[index].lchild!=0){
			//printf("a[%d]=%d",i,a[i]);
			
			if(a[i]==48){
				
				index=HT[index].lchild;
				//printf("index=%d",index);
			}
			else{
				index=HT[index].rchild;
				//printf("index=%d",index);
			}
			//printf("a[%d] is %d",i,a[i]);
			++i;
		}
		//printf("index is %d",index);
			while((i)%8!=1){
			
			//printf("a[%d] is %d",i,a[i]);
			++i;
			}
		
		b[j]=(char)huf[index].data   ;
		//printf("b[%d]=%c\n",j,b[j]);
		++j;
		++uncopmresscharnum;
		index=2*n-1;
	}
	//printf("here"); 
	for(i=1;i<=uncopmresscharnum;++i){
		//printf("yes");
		//printf("%c",b[i]);
	}
	printf("decompress successfully");
}
void creatcompressfile(){
	FILE *fp;
	int ch=1;
	fp=fopen("D:\\1大学\\数据结构\\huffman_test\\huffman_test\\2\\result.huf","wb");
	//ch =fgetc(fp);
	while(ch<=copmresscharnum){
		fputc(compresschar[ch],fp);
		++ch;
	}
	
	fclose(fp);
}
void creatdecompressfile(int n,HUF *huf){
	FILE *fp;
	int ch=1;
	fp=fopen("D:\\1大学\\数据结构\\huffman_test\\huffman_test\\2\\result.huf","rb");
	ch =fgetc(fp);
	charnum=0;
	while(!feof(fp)){
		charnum++;
		character[charnum]=ch;//从1开始 
		//printf("%d",ch);
		//printf("%c ch=%d ",ch,ch);
		//freq[ch]++;
		//w1[ch]=freq[ch];
	    ch=fgetc(fp); 
	}
	uncompress(character,uncompresschar, HT, n,huf);
	//printf("\n");
	fclose(fp);
	
	ch=1;
	fp=fopen("D:\\1大学\\数据结构\\huffman_test\\huffman_test\\2\\result2.txt","wb");
	//ch =fgetc(fp);
	while(ch<=uncopmresscharnum){
		fputc(uncompresschar[ch],fp);
		++ch;
	}
	
	fclose(fp);
}
int main(){
	
	int *w;
	HUF *huf;
	int n=0;
	char *goalfile;
	goalfile="D:\\1大学\\数据结构\\huffman_test\\huffman_test\\2\\2_1.txt";
	readfile(w1,goalfile,n,w,huf);
	//check();
	HuffmanCoding(HT,HC,w,n);
	//HTcheck(HT, HC,n,huf);
	compress(n,character,compresschar,HC,huf);
	uncompress(compresschar,uncompresschar, HT, n,huf);
	//printf("%d ",HT[1].weight);
	creatcompressfile();
	creatdecompressfile(n,huf);
	printf("OK!");
}

