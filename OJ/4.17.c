#include <stdio.h>
#include <string.h>

void Replace(char S[100],char T[100],char V[100]){
  char result[100]="";
  int i=0;
  int lenS=strlen(S);
  int lenT=strlen(T);
  while(i<=lenS-lenT){
    int match=1;
    for(int j=0;j<lenT;j++){
      if(S[i+j]!=T[j]) {
        match=0;
        break;
      }
    }
    if(match){
      strcat(result,V);
      i=i+lenT;
    }else{
      strncat(result, &S[i],1);
      i++;
    }
  }
  while (i < lenS) {
    strncat(result, &S[i], 1);
    i++;
  }
  strcpy(S, result);   
}

int main(){
    char S[100],T[100],V[100];
    scanf("%s %s %s",S,T,V);
    Replace(S, T, V);
    printf("%s\n",S);
    return 0;
}
