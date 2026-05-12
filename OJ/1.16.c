#include<stdio.h>
int main(){
  int x,y,z;
  int temp;
  scanf("%d",&x);
  scanf("%d",&y);
  scanf("%d",&z);
  int s[3] = {x,y,z};
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3-i; j++){
        if(j < 2 && s[j] < s[j+1]){
            temp = s[j];
            s[j] = s[j+1];
            s[j+1] = temp;
        }
    }
  }
  for(int k = 0; k<3; k++){
    printf("%d ",s[k]);
  }
  return 0;
}
