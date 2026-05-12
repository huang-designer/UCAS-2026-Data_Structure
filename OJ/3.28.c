#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
  int data;
  struct Node *next;
}Node;

Node *rear;

void InitList(){
  Node *head=(Node*)malloc(sizeof(Node));
  rear=head;
  head->next=head;
}

void EnList(int x){
  Node *s=(Node*)malloc(sizeof(Node));
  s->data=x;
  s->next=rear->next;
  rear->next=s;
  rear=s;
}

int OutList(){
  Node *head=rear->next;
  Node *p=head->next;
  int x=p->data;
  head->next=p->next;
  if(p==rear) rear=head;
  free(p);
  return x;
}

int main(){
  int len,x;
  scanf("%d",&len);
  InitList();
  getchar();
  for(int i=0;i<len;i++){
    scanf("%d",&x);
    EnList(x);
    if(i!=len-1) scanf(",");
  }
  for(int i=0;i<len;i++){
    printf("%d",OutList());
    if(i!=len-1) printf(",");
  }
  return 0;
}



