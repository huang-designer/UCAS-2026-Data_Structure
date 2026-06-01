#include<stdio.h>
#include<stdlib.h>
#define MAX 100

typedef struct binode{
    char data;
    int left;
    int right;
    int number;
    struct binode* lchild;
    struct binode* rchild;
} Binode, *Bitree;


int L[MAX] = {0};
int R[MAX] = {0};

int searchson(int u, int v){
    if(L[v]==u||R[v]==u) return 1;
    else if(L[v]!=0 && searchson(u,L[v]))
        return 1;
    else if(R[v]!=0 && searchson(u,R[v]))
        return 1;
    else return 0;
}

int main(){

    int length = 0;
    char c;
    int n;
    while(1){
        scanf("%d%c",&n,&c);
        L[length] = n;
        length++;
        if(c=='\n') break;
    }

    for(int i = 0; i < length; i++){
        scanf("%d%c",&R[i],&c);
    }

    int u,v;
    scanf("%d %d",&u,&v);
    int result = searchson(u,v);
    printf("%d",result);
    return 0;
}
