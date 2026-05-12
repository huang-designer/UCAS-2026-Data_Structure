#include <stdio.h>
#define MAXSIZE 100

typedef struct{
  char data[MAXSIZE];
  int top;
}stack;

void InitStack(stack *s) {
    s->top = -1;
}

int Push(stack *s, char ch) {
    if (s->top == MAXSIZE - 1) return 0;
    s->data[++s->top] = ch;
    return 1;
}

int Pop(stack *s, char *ch) {
    if (s->top == -1) return 0;
    *ch = s->data[s->top--];
    return 1;
}

int main(){
  stack s;
  InitStack(&s);
  char ch,temp;
  char str[MAXSIZE];
  int i = 0, len = 0;
  int ok = 1;
  while ((ch = getchar()) != '@') {
    str[i++] = ch;
    Push(&s, ch);
  }
  len = i;
  for (i = 0; i < len; i++) {
    Pop(&s, &temp);
    if (str[i] != temp) {
      ok = 0;
      break;
    }
  }
  printf("%d", ok);
  return 0;
}
