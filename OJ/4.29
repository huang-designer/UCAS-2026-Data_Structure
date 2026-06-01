#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node{
  char data;
  struct Node *succ;
  struct Node *next;
}Node,*String;

String CreateString(char s[],int m){
  Node *head = (Node*)malloc(sizeof(Node));
  head->succ=NULL;
  head->next=NULL;
  Node *tail=head;
  
  for(int i=0;i<m;i++){
    Node *NewNode = (Node*)malloc(sizeof(Node));
    NewNode->data=s[i];
    NewNode->succ=NULL;
    NewNode->next=tail;
    tail->succ=NewNode;
    tail=NewNode;
  }
  return head;
}

void getnext(String T,int m){
  Node *head=T;
  Node *p=head->succ;
  Node *q=head;
  if(p == NULL) return;
  p->next=head;

  while(p->succ!=NULL){
    if(q==head || p->data == q->data){
      p=p->succ;
      q=q->succ;
      p->next=q;
    }else{
      q=q->next;
    }
  }
}

int KMPMatch(String S, String T, int n, int m) {
    Node *i = S->succ;
    Node *j = T->succ;
    int pos = 0;

    while (i != NULL && j != NULL) {
        if (i->data == j->data) {
            i = i->succ;
            j = j->succ;
            pos++;
        }
        else {
            j = j->next;
            if (j == T) {
                i = i->succ;
                pos++;
                j = j->succ;
            }
        }
    }

    if (j == NULL) return pos - m;
    else return -1;
}

int main() {
    int n, m;
    char s[1000], t[1000];
    scanf("%d %d", &n, &m);
    scanf("%s", s);
    scanf("%s", t);

    String S = CreateString(s, n);
    String T = CreateString(t, m);
    getnext(T, m);
    int ans = KMPMatch(S, T, n, m);
    printf("%d\n", ans);

    return 0;
}
