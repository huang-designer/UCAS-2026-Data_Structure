#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
typedef struct{
  char data[MAXSIZE];
  int top;
}stack;

//初始化栈
void InitStack(stack *s){
  s->top=-1;
}
//判断栈是否为空
int IsEmpty(stack *s){
  return s->top == -1;
}
//压栈
int push(stack *s,char x){
  if(s->top == MAXSIZE-1){
    return 0;
  }
  s->data[++s->top]=x;
  return 1;
}
//出栈
int pop(stack *s,char *x){
  if(IsEmpty(s)) return 0;
  *x=s->data[s->top--];
  return 1;
}

int main(){
  stack s;
  InitStack(&s);
  char m,n;
  int ok=1;
  scanf("%c",&m);
  while(m!='&'){
    push(&s,m);
    scanf("%c",&m);
  }
  scanf("%c",&m);
  while(m!='@'){
    pop(&s,&n);
    if (n != m) {
      ok = 0;
      break;
    }
    scanf("%c", &m);
  }
  if (!IsEmpty(&s)) ok = 0;
  printf("%d", ok);
  return 0;
}



