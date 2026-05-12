#include <stdio.h>

int F(int n){
  // = 改成 == 就对了！
  if(n == 0) return 1;
  else if(n > 0) return n * F(n / 2);
  else return -1;
}

int main(){
  int n;
  scanf("%d",&n);
  printf("%d",F(n));
  return 0;
}
