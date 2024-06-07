#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct fifo{
  char podatak;
  struct fifo* sledeci;
}Fifo;

typedef struct list{
  char value[32];
  int freq;
  struct list* sledeci;
}List;

typedef struct ntree{
  struct ntree* zero;
  struct ntree* one;
  struct ntree* two;
  struct ntree* three;
  struct ntree* four;
  struct ntree* five;
  struct ntree* six;
  struct ntree* seven;
  struct ntree* eight;
  struct ntree* nine;
  int count;
  int acount;
}Ntree;

void insert(Fifo **pocetak, Fifo **kraj, int x){
  Fifo* novi=(Fifo*)malloc(sizeof(Fifo));
  novi->sledeci=NULL;
  novi->podatak=x;
  if((*pocetak)==NULL){
    (*pocetak)=novi;
    (*kraj)=novi;
  }
  (*kraj)->sledeci=novi;
  (*kraj)=novi;
}

int delete(Fifo **pocetak, Fifo **kraj){
  if((*pocetak)==NULL){
    printf("Fifo je prazan.");
    return -1;
  }
  int retval=(*pocetak)->podatak;
  if((*pocetak)==(*kraj)){
    free((*pocetak));
    (*pocetak)=NULL;
    (*kraj)=NULL;
    return retval;
  }
  Fifo* novi=(*pocetak);
  (*pocetak)=(*pocetak)->sledeci;
  free(novi);
  return retval;
}

int readFifo(Fifo **pocetak, Fifo **kraj){
  int retval=delete(pocetak, kraj);
  while((*pocetak)!=NULL){
    retval=retval*10+delete(pocetak, kraj);
  }
  return retval;
}

void NtreeAlloc(Ntree* root, Fifo **pocetak, Fifo** kraj){
  root->count=root->count + 1;
  while((*pocetak)!=NULL){
    int x=delete(pocetak, kraj);
    switch(x){
      case 0:
        if(root->zero==NULL){
          root->zero=(Ntree*)malloc(sizeof(Ntree));
        }
        root=root->zero;
        root->count++;
        break;
      case 1:
        if(root->one==NULL){
          root->one=(Ntree*)malloc(sizeof(Ntree));
        }
        root=root->one;
        root->count++;
        break;
      case 2:
        if(root->two==NULL){
          root->two=(Ntree*)malloc(sizeof(Ntree));
        }
        root=root->two;
        root->count++;
        break;
      case 3:
        if(root->three==NULL){
          root->three=(Ntree*)malloc(sizeof(Ntree));
        }
        root=root->three;
        root->count++;
        break;
      case 4:
        if(root->four==NULL){
          root->four=(Ntree*)malloc(sizeof(Ntree));
        }
        root=root->four;
        root->count++;
        break;
      case 5:
        if(root->five==NULL){
          root->five=(Ntree*)malloc(sizeof(Ntree));
        }
        root=root->five;
        root->count++;
        break;
      case 6:
        if(root->six==NULL){
          root->six=(Ntree*)malloc(sizeof(Ntree));
        } 
        root=root->six;
        root->count++;
        break;
      case 7:
        if(root->seven==NULL){
          root->seven=(Ntree*)malloc(sizeof(Ntree));
        }
        root=root->seven;
        root->count++;
        break;
      case 8:
        if(root->eight==NULL){
          root->eight=(Ntree*)malloc(sizeof(Ntree));
        }
        root=root->eight;
        root->count++;
        break;
      case 9:
        if(root->nine==NULL){
          root->nine=(Ntree*)malloc(sizeof(Ntree));
        }
        root=root->nine;
        root->count++;
        break;
    }
  }
  root->acount++;
}

void NtreeRead(Ntree* root, char passdown[], List* lista, int i){
  if(root->zero!=NULL)passdown[i]='0',NtreeRead(root->zero, passdown, lista, i+1);
  if(root->one!=NULL)passdown[i]='1',NtreeRead(root->one, passdown, lista, i+1);
  if(root->two!=NULL)passdown[i]='2',NtreeRead(root->two, passdown, lista, i+1);
  if(root->three!=NULL)passdown[i]='3',NtreeRead(root->three, passdown, lista, i+1);
  if(root->four!=NULL)passdown[i]='4',NtreeRead(root->four, passdown, lista, i+1);
  if(root->five!=NULL)passdown[i]='5',NtreeRead(root->five, passdown, lista, i+1);
  if(root->six!=NULL)passdown[i]='6',NtreeRead(root->six, passdown, lista, i+1);
  if(root->seven!=NULL)passdown[i]='7',NtreeRead(root->seven, passdown, lista, i+1);
  if(root->eight!=NULL)passdown[i]='8', NtreeRead(root->eight, passdown, lista, i+1);
  if(root->nine!=NULL)passdown[i]='9', NtreeRead(root->nine, passdown, lista, i+1);
  if(root->acount>0){
    passdown[i]='\0';
    List* novi=(List*)malloc(sizeof(List));
    strcpy(novi->value, passdown);
    novi->freq=root->acount;
    novi->sledeci=lista->sledeci;
    lista->sledeci=novi;
  }
}

void NtreeFree(Ntree* root){
    if(root == NULL){
        return;
    }
    NtreeFree(root->zero);
    NtreeFree(root->one);
    NtreeFree(root->two);
    NtreeFree(root->three);
    NtreeFree(root->four);
    NtreeFree(root->five);
    NtreeFree(root->six);
    NtreeFree(root->seven);
    NtreeFree(root->eight);
    NtreeFree(root->nine);

    free(root);
}

//i=0;i<n;i++
//j=i+1;j<n;j++
void SelectionSortAndSize(List* lista, int* n){
  List* i=lista;

  while(i!=NULL){
    List* j=i->sledeci;
    List* min=i;
    while(j!=NULL){
      if(j->freq>min->freq){
        min=j;
      }
      j=j->sledeci;
    }
    char str[32];
    strcpy(str, min->value);
    strcpy(min->value, i->value);
    strcpy(i->value, str);
    int pom=min->freq;
    min->freq=i->freq;
    i->freq=pom;
    i=i->sledeci;
    *n=*n + 1;
  }
}

void stampaj(List* lista){
  printf("CHAR : FREQ\n");
  while(lista!=NULL){
    printf("%s:%i\n", lista->value, lista->freq);
    lista=lista->sledeci;
  }
}

void FindRemove(List** lista, char x[32]) {
    while (*lista != NULL && (*lista)->sledeci != NULL) {
        if (strcmp((*lista)->sledeci->value, x) == 0) {
            List* brisi = (*lista)->sledeci;
            (*lista)->sledeci = (*lista)->sledeci->sledeci;
            free(brisi);
        }
        else {
            *lista = (*lista)->sledeci;
        }
    }
    if (*lista != NULL && strcmp((*lista)->value, x) == 0) {
        List* brisi = *lista;
        *lista = (*lista)->sledeci;
        free(brisi);
    }
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



int main(){
  FILE* dat;

  Fifo* pocetak=NULL;
  Fifo* kraj=NULL;

  char odluka[128];
  printf("Unesite put do datoteke, ili stdin za unos iz programa: ");
  fgets(odluka, 127, stdin);
  odluka[strcspn(odluka,"\n")]='\0';


  char input[1024];

  if(strcmp(odluka, "stdin")==0){ 
    fgets(input,1023,stdin);
    input[strcspn(input,"\n")]='\0';
  }else{
    dat=fopen(odluka, "r");
    if (!dat) {
      fprintf(stderr, "Greska pri otvaranju %s\n", odluka);
      exit(1);
    }
    int i = 0;
    while (fscanf(dat, "%c", &input[i]) == 1) {
        i++;
    }
    input[i] = '\0';
    fclose(dat);
  }

  Ntree* root;
  start:

  root=(Ntree*)malloc(sizeof(Ntree));
  root->count=0;

  
  //ovaj deo funkcionise kao loop
  printf("\nUspesno izvrseno.\n");
  int len=strlen(input);
  int i=0;

  int maxstrlen=0;
  int substrlen;
  //while(input[i]==' '){i++;}
  //int depth=i;
  //while(input[i]!=' '){i++;}
  //depth=i-depth+1;
  while(i<len && input[i]!='\0'){
    if(input[i]!=' ' && input[i]!='\n' && input[i]!='\0'){
      substrlen=i;
      do{
      insert(&pocetak, &kraj, ((int)input[i])-48);
      i++;
      }while(input[i]!=' ' && input[i]!='\0' && input[i]!='\n');
      substrlen=i-substrlen;
      if(substrlen>maxstrlen) maxstrlen=substrlen;
      NtreeAlloc(root, &pocetak, &kraj);
    }else{
      i++;
    }
  }
  maxstrlen=maxstrlen+1; //for the terminator

  List* lista=(List*)malloc(sizeof(List));
  strcpy(lista->value, "\0");
  lista->freq=root->count;
  lista->sledeci=NULL;
  
  char passdown[maxstrlen];
  NtreeRead(root, passdown, lista, 0);

  int n=0;
  SelectionSortAndSize(lista->sledeci, &n);

  printf("Unique characters: %i\n", n);
  stampaj(lista->sledeci);
  //finished initial freq search

  char str[1023];
  char replace[1022];

  while (getchar()!='\n');
  printf("\n\nEnter a string which you want to substitute: ");
  fgets(str, 1022, stdin);
  printf("Enter a string to replace with: ");
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
  FindRemove(&lista, str);
  puts(input);

  printf("Napisi \"write\" da bi uneo promene u datoteku, bilosta drugo za nastavak: ");
  char izbor[7];
  fgets(izbor, 6, stdin);
  if(strcmp(izbor,"write")==0){
    if(strcmp(odluka,"stdin")==0){
      getchar();
      printf("Unesite ime datoteke: ");
      fgets(odluka, 127, stdin);
      odluka[strcspn(odluka, "\n")] = '\0';
    }
    dat=fopen(odluka,"w");
    if (!dat) {
      fprintf(stderr, "Greska pri otvaranju %s\n", odluka);
      exit(1);
    }
    fprintf(dat, "%s", input);
    fclose(dat);
  }else{
    NtreeFree(root);
    root=NULL;
    goto start;
  }
  return 0;
}
