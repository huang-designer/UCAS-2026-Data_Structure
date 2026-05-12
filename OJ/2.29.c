#include <stdio.h>

typedef struct{
  char data[100];
  int len;
}SqList;

void CreatList(SqList *L,char arr[],int n){
  L->len=n;
  for(int i=0;i<n;++i){
    L->data[i]=arr[i];
  }
}

int IsBoth(SqList B,SqList C,char x){
  int i=0,j=0;
  while(i<B.len && j<C.len){
    if(x==B.data[i] && x==C.data[j])
      return 1;
    else if(x > B.data[i])
      i++;
    else
      j++;
  }
  return 0;
}

void FilterA(SqList *A, SqList B, SqList C)
{
  int j = 0;
  for (int i = 0; i < A->len; i++){
    if (!IsBoth(B, C, A->data[i])){
      A->data[j++] = A->data[i];
    }
  }
  A->len = j;
}

int ReadCharArr(char arr[100]){
  char a;
  int len=0;
  while(scanf("%c",&a)==1){
    if(a == '\n') break;
    if(a == ',') continue;
    arr[len++] = a;
  }
  return len;
}

void PrintList(SqList A){
  for(int i=0;i<A.len-1;++i){
    printf("%c",A.data[i]);
    printf(",");
  }
  printf("%c",A.data[A.len-1]);
  printf("\n");
}

int main()
{
  SqList A, B, C;
  char a[100], b[100], c[100];
  int na, nb, nc;

  na = ReadCharArr(a);
  nb = ReadCharArr(b);
  nc = ReadCharArr(c);

  CreatList(&A, a, na);
  CreatList(&B, b, nb);
  CreatList(&C, c, nc);

  FilterA(&A, B, C);
  PrintList(A);

  return 0;
}
