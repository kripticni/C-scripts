#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct fifo{
  int podatak;
  struct fifo* sledeci;
}Fifo;

typedef struct list{
  int value;
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
}

void NtreeRead(Ntree* root, int passdown, List* lista){
  bool check=0;
  if(root->zero!=NULL){NtreeRead(root->zero, passdown*10, lista); check=1;}
  if(root->one!=NULL){NtreeRead(root->one, passdown*10+1,lista); check=1;}
  if(root->two!=NULL){NtreeRead(root->two, passdown*10+2, lista); check=1;}
  if(root->three!=NULL){NtreeRead(root->three, passdown*10+3, lista); check=1;}
  if(root->four!=NULL){NtreeRead(root->four, passdown*10+4, lista); check=1;}
  if(root->five!=NULL){NtreeRead(root->five, passdown*10+5, lista); check=1;}
  if(root->six!=NULL){NtreeRead(root->six, passdown*10+6, lista); check=1;}
  if(root->seven!=NULL){NtreeRead(root->seven, passdown*10+7, lista); check=1;}
  if(root->eight!=NULL){NtreeRead(root->eight, passdown*10+8, lista); check=1;}
  if(root->nine!=NULL){NtreeRead(root->nine, passdown*10+9, lista); check=1;}
  if(check==0){
    List* novi=(List*)malloc(sizeof(List));
    novi->freq=root->count;
    novi->value=passdown;
    novi->sledeci=lista->sledeci;
    lista->sledeci=novi;
  }
}

//i=0;i<n;i++
//j=i+1;j<n;j++
void SelectionSortAndSize(List* lista, int* n){
  List* i=lista;

  while(i!=NULL){
    List* j=i->sledeci;
    List* min=i;
    while(j!=NULL){
      if(j->freq<min->freq){
        min=j;
      }
      j=j->sledeci;
    }
    int pom=min->value;
    min->value=i->value;
    i->value=pom;
    pom=min->freq;
    min->freq=i->freq;
    i->freq=pom;
    i=i->sledeci;
    *n=*n + 1;
  }
}

void stampaj(List* lista){
  printf("CHAR : FREQ\n");
  while(lista!=NULL){
    printf("%i:%i\n", lista->value, lista->freq);
    lista=lista->sledeci;
  }
}

void FindRemove(List* lista, int x){
  while(lista!=NULL){
    if(lista->sledeci->value==x){
      List* brisi=lista->sledeci;
      lista->sledeci=lista->sledeci->sledeci;
      free(brisi);
    }
    lista=lista->sledeci;
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
  Ntree* root=(Ntree*)malloc(sizeof(Ntree));
  root->count=0;

  Fifo* pocetak=NULL;
  Fifo* kraj=NULL;

  char input[1024];
  fgets(input,1023,stdin);
  input[strcspn(input,"\n")]='\0';

  int len=strlen(input);
  int i=0;

  //while(input[i]==' '){i++;}
  //int depth=i;
  //while(input[i]!=' '){i++;}
  //depth=i-depth+1;
  while(i<len && input[i]!='\0'){
    if(input[i]!=' ' && input[i]!='\0'){
      do{
      insert(&pocetak, &kraj, ((int)input[i])-48);
      i++;
      }while(input[i]!=' ' && input[i]!='\0');
      NtreeAlloc(root, &pocetak, &kraj);
    }else{
      i++;
    }
  }

  List* lista=(List*)malloc(sizeof(List));
  lista->value=-1;
  lista->freq=root->count;
  lista->sledeci=NULL;
  
  NtreeRead(root, 0, lista);

  int n=0;
  SelectionSortAndSize(lista->sledeci, &n);

  printf("Unique characters: %i", n);
  stampaj(lista->sledeci);
  //finished initial freq search
  //TODO: Make it work when there is leading zeroes, likely needs structural changes in both the writing and reading function
  //TODO: Make it work when there is two different characters that begin in the same way, probably just checking the sums would be sufficient but its gonna take a hit on performance
  

  char str[1023];
  char replace[1022];

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
  while(i<n){
    if(str[j]==input[i]){
      i++;
      j++;
    }else{
      if(j!=0) j=kmptable[j-1];
      else i++;
    }
  if(j==slen){
      printf("\nNadjen na %i", i-j);
      int start=i-j;
      int diff=slen-rlen;
      if (diff > 0) {
        int z = start;
        while (z < len - diff) {
          input[z] = input[z + diff];
          z++;
        }
      } else if (diff < 0) {
        int z = len - 1;
        while (z >= start - diff) {
          input[z] = input[z + diff];
          z--;
        }
      }

      for (int z = 0; z < rlen; z++) {
        input[start + z] = replace[z];
      }

      input[len - diff] = '\0';
      j=kmptable[j-1];
    }
  }


  puts(input);
  return 0;
}
