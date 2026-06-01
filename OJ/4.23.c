#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCKSIZE 4

typedef struct Block {
    char ch[BLOCKSIZE];
    struct Block *next;
} Block;

typedef struct {
    Block *head;
    int len;
} BLString;

// 赋值：把字符串s存入块链串
void StrAssign(BLString *S, char s[]) {
    S->len = strlen(s);
    S->head = NULL;
    Block *p = NULL;
    
    for (int i = 0; i < S->len; i++) {
        if (i % BLOCKSIZE == 0) {
            Block *newb = (Block *)malloc(sizeof(Block));
            newb->next = NULL;
            if (!S->head) 
              S->head = newb;
            else 
              p->next = newb;
            p = newb;
        }
        p->ch[i % BLOCKSIZE] = s[i];
    }
}

char GetChar(BLString S, int pos) {
    Block *p = S.head;
    int i = 1;
    while (i < pos) {
        if (i % BLOCKSIZE == 0) p = p->next;
        i++;
    }
    return p->ch[(pos - 1) % BLOCKSIZE];
}

int IsSymmetry(BLString S) {
    int i = 1, j = S.len;
    while (i < j) {
        if (GetChar(S, i) != GetChar(S, j))
            return 0;
        i++;
        j--;
    }
    return 1;
}

int main() {
    int n;
    char s[1000];
    scanf("%d", &n);
    scanf("%s", s);
    
    BLString S;
    StrAssign(&S, s);
    
    printf("%d\n", IsSymmetry(S));
    return 0;
}
