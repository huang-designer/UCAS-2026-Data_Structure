#include <stdio.h>
#include <string.h>

int StrCompare(char S[100],char T[100]){
  int i;
  for(i=0;S[i]!='\0' && T[i]!='\0';i++){
    if(S[i]<T[i]) return -1;
    if(S[i]>T[i]) return 1;
  }
  if(S[i]=='\0' && T[i]=='\0') return 0;
  if(S[i]=='\0' && T[i]!='\0') return -1;
  if(S[i]!='\0' && T[i]=='\0') return 1;
}

int main(){
  char s[100],t[100];
  scanf("%s %s",s,t);
  int x = StrCompare(s,t);
  printf("%d",x);
  return 0;
}
