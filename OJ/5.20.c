#include<stdio.h>


int main(){
    int r,c;
    scanf("%d %d",&r,&c);
    int a[r][c];
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            scanf("%d",&a[i][j]);
        }
    }

    int sign = 0;
    
    for(int i = r-1; i >= 0; i--){
        for(int j = c-1; j >= 0; j--){
            if(a[i][j]){
                if(sign){
                    printf("+");
                }
                sign = 1;
                if(a[i][j]!=1 || a[i][j]==1 && i==0 && j==0){
                    printf("%d",a[i][j]);
                }
                if(i){
                    printf("xE%d",i);
                }
                if(j){
                    printf("yE%d",j);
                }
            }
        }
    }
    return 0;
}
