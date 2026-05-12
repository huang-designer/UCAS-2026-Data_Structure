#include<stdio.h>

int main(){
  int score[5][3]={0};
  char gender;
  char xiangmu [20];
  char school;
  int grade;
  while(scanf("%s %c %c %d",&xiangmu,&gender,&school,&grade)==4){
    int xuexiao=school-'A';
    if(gender=='M'){
      score[xuexiao][0]+=grade;
    }else{
      score[xuexiao][1]+=grade;
    }
  }
  
  int i;
  for(i=0;i<=4;++i){
    if (score[i][0] > 0) {
            printf("%c M %d\n",i+'A',score[i][0]);
    }
    if (score[i][1] > 0) {
      printf("%c F %d\n",i+'A',score[i][1]);
    }
    score[i][2]=score[i][0]+score[i][1];
    if (score[i][2] > 0) {
    printf("%c %d\n",i+'A',score[i][2]);
    }
  }
  
  return 0;
}
