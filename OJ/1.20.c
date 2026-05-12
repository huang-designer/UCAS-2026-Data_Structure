#include<stdio.h>

int main(){
  int x,n;
  scanf("%d %d",&x,&n);
  int a[n+1]={0};
  int sum=0;
  for(int i=0;i<n+1;++i){
    scanf("%d",&a[i]);
    int p=1;
    for(int j=0;j<i;++j){
      p*=x;
    }
    sum+=a[i]*p;
  }
  printf("%d",sum);
  return 0;
}
