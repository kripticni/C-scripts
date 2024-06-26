#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct head{
  struct node* zero;
  struct node* one;
  int freq;
  int afreq;
}Head;

typedef struct node{
  struct tail* zero;
  struct tail* one;
  struct tail* two;
  struct tail* three;
  struct tail* four;
  struct tail* five;
  struct tail* six;
  struct tail* seven;
  struct tail* eight;
  struct tail* nine;
}Node;

typedef struct tail{
  struct head* zero;
  struct head* one;
  struct head* two;
  struct head* three;
  struct head* four;
  struct head* five;
  struct head* six;
  struct head* seven;
  struct head* eight;
  struct head* nine;
}Tail;

typedef struct pipe{
  uint8_t podatak;
  struct pipe* sledeci;
}Pipe;

typedef struct list{
  char str[128];
  int afreq;
  struct list* sledeci;
}List;

void make(Pipe** pocetak, Pipe** kraj, int x){
  Pipe* novi=(Pipe*)malloc(sizeof(Pipe*));
  novi->sledeci=NULL;
  novi->podatak=x;
  (*pocetak)=novi;
  (*kraj)=novi;
}

void insert(Pipe **kraj, int x){
  Pipe* novi=(Pipe*)malloc(sizeof(Pipe));
  novi->sledeci=NULL;
  novi->podatak=x;
  (*kraj)->sledeci=novi;
  (*kraj)=novi;
}

int delete(Pipe **pocetak, Pipe **kraj){
  int retval=(*pocetak)->podatak;
  if((*pocetak)==(*kraj)){
    free((*pocetak));
    (*pocetak)=NULL;
    (*kraj)=NULL;
    return retval;
  }
  Pipe* novi=(*pocetak);
  (*pocetak)=(*pocetak)->sledeci;
  free(novi);
  return retval;
}

void stampaj(List* lista){
  printf("\n");
  while(lista!=NULL){
    printf("%s:%i\n", lista->str, lista->afreq);
    lista=lista->sledeci;
  }
}

void HeadAlloc(Head* root, Pipe** pocetak, Pipe** kraj);

Head* TailAlloc(Tail* root, int x){
  switch(x%10){
    case 0:
      if(root->zero==NULL)root->zero=(Head*)calloc(1,sizeof(Head));
      return root->zero;
    case 1:
      if(root->one==NULL)root->one=(Head*)calloc(1,sizeof(Head));
      return root->one;
    case 2:
      if(root->two==NULL)root->two=(Head*)calloc(1,sizeof(Head));
      return root->two;
    case 3:
      if(root->three==NULL)root->three=(Head*)calloc(1,sizeof(Head));
      return root->three;
    case 4:
      if(root->four==NULL)root->four=(Head*)calloc(1,sizeof(Head));
      return root->four;
    case 5:
      if(root->five==NULL)root->five=(Head*)calloc(1,sizeof(Head));
      return root->five;
    case 6:
      if(root->six==NULL)root->six=(Head*)calloc(1,sizeof(Head));
      return root->six;
    case 7:
      if(root->seven==NULL)root->seven=(Head*)calloc(1,sizeof(Head));
      return root->seven;
    case 8:
      if(root->eight==NULL)root->eight=(Head*)calloc(1,sizeof(Head));
      return root->eight;
    case 9: 
      if(root->nine==NULL)root->nine=(Head*)calloc(1,sizeof(Head));
      return root->nine;
  }
  return NULL;
}

Head* NodeAlloc(Node* root, int x){
  switch((x%100)/10){
    case 0:
      if(root->zero==NULL)root->zero=(Tail*)calloc(1,sizeof(Tail));
      return TailAlloc(root->zero, x);
    case 1:
      if(root->one==NULL)root->one=(Tail*)calloc(1,sizeof(Tail));
      return TailAlloc(root->one, x);
    case 2:
       if(root->two==NULL)root->two=(Tail*)calloc(1,sizeof(Tail));
      return TailAlloc(root->two, x);
    case 3:
       if(root->three==NULL)root->three=(Tail*)calloc(1,sizeof(Tail));
      return TailAlloc(root->three, x);
    case 4:
       if(root->four==NULL)root->four=(Tail*)calloc(1,sizeof(Tail));
      return TailAlloc(root->four, x);
    case 5:
       if(root->five==NULL)root->five=(Tail*)calloc(1,sizeof(Tail));
      return TailAlloc(root->five, x);
    case 6:
       if(root->six==NULL)root->six=(Tail*)calloc(1,sizeof(Tail));
      return TailAlloc(root->six, x);
    case 7:
      if(root->seven==NULL)root->seven=(Tail*)calloc(1,sizeof(Tail));
      return TailAlloc(root->seven, x);
    case 8:
      if(root->eight==NULL)root->eight=(Tail*)calloc(1,sizeof(Tail));
      return TailAlloc(root->eight, x);
    case 9:
       if(root->nine==NULL)root->nine=(Tail*)calloc(1,sizeof(Tail));
      return TailAlloc(root->nine, x);
  }
  return NULL;
}

void HeadAlloc(Head* root, Pipe** pocetak, Pipe** kraj){
  do{
    int podatak=delete(pocetak, kraj);
    if(podatak/100){
      if(root->one==NULL)root->one=(Node*)calloc(1,sizeof(Node));
      root=NodeAlloc(root->one, podatak);
    }else{
      if(root->zero==NULL)root->zero=(Node*)calloc(1,sizeof(Node));
      root=NodeAlloc(root->zero, podatak);
    }
    root->freq++;
  }while((*pocetak)!=NULL);
  root->afreq++;
}


void kmp(char* str, int m, int* niz){
  int j=0;
  int i=1;
  niz[0]=0;
  while(i<m){
    if(str[i]==str[j]){
      niz[i]=j+1;
      i++;
      j++;
    }else{
      if(j!=0)j=niz[j-1];
      else{
        niz[i]=0;
        i++;
      }
    }
  }
}

void ReadHead(Head* root, List* lista, char passdown[], int i, int ascii);

void ReadTail(Tail* root, List* lista, char passdown[], int i, int ascii){
  if(root->zero!=NULL)ReadHead(root->zero, lista, passdown, i+1, ascii*10);
  if(root->one!=NULL)ReadHead(root->one, lista, passdown, i+1, ascii*10+1);
  if(root->two!=NULL)ReadHead(root->two, lista, passdown, i+1, ascii*10+2);
  if(root->three!=NULL)ReadHead(root->three, lista, passdown, i+1, ascii*10+3);
  if(root->four!=NULL)ReadHead(root->four, lista, passdown, i+1, ascii*10+4);
  if(root->five!=NULL)ReadHead(root->five, lista, passdown, i+1, ascii*10+5);
  if(root->six!=NULL)ReadHead(root->six, lista, passdown, i+1, ascii*10+6);
  if(root->seven!=NULL)ReadHead(root->seven, lista, passdown, i+1, ascii*10+7);
  if(root->eight!=NULL)ReadHead(root->eight, lista, passdown, i+1, ascii*10+8);
  if(root->nine!=NULL)ReadHead(root->nine, lista, passdown, i+1, ascii*10+9);
}

void ReadNode(Node* root, List* lista, char passdown[], int i, int ascii){
  if(root->zero!=NULL)ReadTail(root->zero, lista, passdown, i, ascii*10);
  if(root->one!=NULL)ReadTail(root->one, lista, passdown, i, ascii*10+1);
  if(root->two!=NULL)ReadTail(root->two, lista, passdown, i, ascii*10+2);
  if(root->three!=NULL)ReadTail(root->three, lista, passdown, i, ascii*10+3);
  if(root->four!=NULL)ReadTail(root->four, lista, passdown, i, ascii*10+4);
  if(root->five!=NULL)ReadTail(root->five, lista, passdown, i, ascii*10+5);
  if(root->six!=NULL)ReadTail(root->six, lista, passdown, i, ascii*10+6);
  if(root->seven!=NULL)ReadTail(root->seven, lista, passdown, i, ascii*10+7);
  if(root->eight!=NULL)ReadTail(root->eight, lista, passdown, i, ascii*10+8);
  if(root->nine!=NULL)ReadTail(root->nine, lista, passdown, i, ascii*10+9);
}

void ReadHead(Head* root, List* lista, char passdown[], int i, int ascii){
  passdown[i]=(char)ascii;
  if(root->zero!=NULL)ReadNode(root->zero, lista, passdown, i, 0);
  if(root->one!=NULL)ReadNode(root->one, lista, passdown, i, 1);
  if(root->afreq>0){
    passdown[i+1]='\0';
    List* novi=(List*)malloc(sizeof(List));
    strcpy(novi->str, passdown);
    novi->afreq=root->afreq;
    novi->sledeci=lista->sledeci;
    lista->sledeci=novi;
  }
}


void SelectionSortIVelicina(List* lista, int* n){
  List* i=lista;

  while(i!=NULL){
    List* j=i->sledeci;
    List* min=i;
    while(j!=NULL){
      if(j->afreq>min->afreq){
        min=j;
      }
      j=j->sledeci;
    }
    char str[32];
    strcpy(str, min->str);
    strcpy(min->str, i->str);
    strcpy(i->str, str);
    int pom=min->afreq;
    min->afreq=i->afreq;
    i->afreq=pom;
    i=i->sledeci;
    *n=*n + 1;
  }
}


int main(){
  FILE* dat;

  char odluka[128];

  printf("Unesite ime datoteke ili stdin: ");
  fgets(odluka, 127, stdin);
  odluka[strcspn(odluka, "\n")]='\0';

  if(strcmp(odluka, "stdin")!=0){
    dat=fopen(odluka, "r");
  }else{
    dat=stdin;
  }

  char* input=malloc(65);
  int maxlen=64;
  int len=0;

  char ch;
  while((ch = fgetc(dat)) != EOF){
    if(len >= maxlen){
      maxlen += 8; 
      char* temp=realloc(input, maxlen+1);
      if(temp==NULL){
        fprintf(stderr, "Greska pri alokaciji!\n");
        free(input);
        return 1;
      }
      input=temp;
    }
    input[len]=(char)ch;
    len++;
  }
  input[len]='\0';

  Pipe *pocetak, *kraj;
  List* lista;
  Head* root;

  int maxstrlen=0, substrlen, i;

  root=(Head*)calloc(1, sizeof(Head));
  lista=(List*)calloc(1, sizeof(List));
  pocetak=NULL;
  kraj=NULL;


  len=strlen(input);

  while(i<len && input[i]!='\0'){
    if(input[i]!=' ' && input[i]!='\n' && input[i]!='\0'){
      substrlen=i;
      make(&pocetak, &kraj, (int)input[i]);
      i++;
      while(input[i]!=' ' && input[i]!='\0' && input[i]!='\n'){
      insert(&kraj, (int)input[i]);
      i++;
      }
      substrlen=i-substrlen;
      if(substrlen>maxstrlen) maxstrlen=substrlen;
      HeadAlloc(root, &pocetak, &kraj);
    }else{
      i++;
    }
  }
  maxstrlen=maxstrlen+1; //for the terminator

  char passdown[maxstrlen];
  int nstr=0;

  ReadHead(root, lista, passdown, -1, 0);
  SelectionSortIVelicina(lista, &nstr);

  printf("Unikatne reci: %i\nREC:FREKVENCIJA", nstr);
  stampaj(lista);

  char str[1023];
  char replace[1022];

  printf("\n\nUnesite rec koju zelite da zamenite: ");
  fgets(str, 1022, stdin);
  printf("Unesite rec sa kojom zelite da prethodnu zamenite: ");
  fgets(replace, 1021, stdin);

  str[strcspn(str, "\n")]='\0';
  replace[strcspn(replace, "\n")]='\0';
  int slen=strlen(str);
  int rlen=strlen(replace);

  int kmptable[slen];
  kmp(str, slen, kmptable);

  int j=0;
  i=0;
  while(i<len){
    if(str[j]==input[i]){
      i++;
      j++;
    }else{
      if(j!=0) j=kmptable[j-1];
      else i++;
    }
    if(j==slen){
      if((input[i-j-1]!=' ' && i-j!=0) || (input[i]!=' ' && i!=len))goto skip;
      //printf("\nNadjen na %i\n", i-j);
      int start = i - j;
      int end = start + rlen;
      if (rlen > slen) {
        memmove(&input[start + rlen], &input[start + slen], len - start - slen + 1);
      } else if (rlen < slen) {
        memmove(&input[end], &input[start + slen], len - start - slen + 1);
      }

      strncpy(&input[start], replace, rlen);

      len = strlen(input);
    skip:
      j=kmptable[j-1];
    }
  }
  puts(input);

  if(strcmp(odluka,"stdin")==0){
    getchar();
    printf("Unesite ime datoteke: ");
    fgets(odluka, 127, stdin);
    odluka[strcspn(odluka, "\n")] = '\0';
  }
  if(strcmp(odluka,"stdin")==0){
    printf("Ne moze se pisati u stdin.");
    if(dat)fclose(dat);
    return 0;
  }
  dat=fopen(odluka,"w");
  if (!dat) {
      fprintf(stderr, "Greska pri otvaranju %s\n", odluka);
      exit(1);
  }
  fprintf(dat, "%s", input);
  fclose(dat);
  return 0;
  }

