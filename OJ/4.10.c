#include <stdio.h>

int main(){
  char arr[100];
  char ch;
  int len=0;
  while(scanf("%c",&ch)==1 && ch!='\n'){
    arr[len++]=ch;
  }
  arr[len]='\0';
  for(int i=len-1;i>=0;i--){
    printf("%c",arr[i]);
  }
  printf("\n");
  return 0;
}
