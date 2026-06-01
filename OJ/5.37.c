#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
#define ATOM 0
#define LIST 1

typedef struct glnode{
    int tag;
    union{
        char atom;
        struct { struct glnode *hp, *tp; } ptr;
    };
} *GList, GLnode;

GList MakeGList(char *s);
void printGList(GList L, int mode);
GList DelAtom(GList L, char data);
void split(char *s, char *head, char *tail);


int main() {
    char s[MAX];
    int length = 0;
    char c;

    //读入字符串形式的广义表s
    while((c = getchar()) != EOF && c != '\n' && c != ' ')
        s[length++] = c;
    s[length] = '\0';

    //根据字符串来创建广义表
    GList L = MakeGList(s);

    c = getchar(); // 读取要删除的原子字符
    L = DelAtom(L, c);

    if(L == NULL)
        printf("-1\n");
    else
        printGList(L, 1);
    return 0;
}

// 辅助函数：分割头尾, 一边用递归的方式来创建表
// 输入s如"(a,(b,c),d)", 输出head="a", tail="((b,c),d)"
void split(char *s, char *head, char *tail) {
    int len = strlen(s);
    if(len < 3) {head[0]=0; tail[0]=0; return; }
    int k = 0, pos = 0;

    // 跳过最外层括号, 找到头结点
    for(int i = 0; i < len; i++) {
        if(s[i] == '(') k++;
        if(s[i] == ')') k--;
        if(s[i] == ',' && k == 1) {pos = i; break; }//表示将头节点读完了
    }

    //pos标记的位置是头head结束的位置
    if(pos) {
        strncpy(head, s+1, pos-1); head[pos-1]=0;
        //将之后的读入到tail中
        strcpy(tail,s+pos);
        *tail = '(';
        //printf("%c\n",tail);
    } //表示最终没有tail,只有头节点
    else {
        strncpy(head, s+1, len-2); head[len-2]=0;
        tail[0]=0;
    }
}

//创建广义表
GList MakeGList(char *s) {
    if(s == NULL || *s == 0) return NULL;
    if(strcmp(s, "()") == 0) return NULL;

    GList L = (GList)malloc(sizeof(GLnode));
    if(strlen(s) == 1) {
        L->tag = ATOM;
        L->atom = *s;
        return L;
    }

    char head[MAX] = {0}, tail[MAX] = {0};
    split(s, head, tail);
    L->tag = LIST;
    L->ptr.hp = MakeGList(head);
    L->ptr.tp = MakeGList(tail);
    return L;
}

//利用pivot来标记括号,防止尾部出现多余的括号
void printGList(GList L, int pivot) {
    if(!L) return;
    if(L->tag == ATOM)
        printf("%c", L->atom);
    else {
        if(pivot) printf("(");
        printGList(L->ptr.hp, 1);
        if(L->ptr.tp) {
            if(L->ptr.hp)
                printf(",");
            printGList(L->ptr.tp, 0);
        }
        if(pivot) printf(")");
    }
}

GList DelAtom(GList L, char data) {
    if(!L) return NULL;
    if(L->tag == ATOM) {
        if(L->atom == data) {
            free(L); // 释放节点
            return NULL;
        } else {
            return L;
        }
    }
    L->ptr.hp = DelAtom(L->ptr.hp, data);
    L->ptr.tp = DelAtom(L->ptr.tp, data);
    if(L->ptr.hp == NULL && L->ptr.tp == NULL) {
        free(L);
        return NULL;
    }
    return L;
}
