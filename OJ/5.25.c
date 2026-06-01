#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct olnode {
    int x, y, data;
    struct olnode *right, *down;
} OLnode, *OLink;

typedef struct {
    OLink *rhead, *chead;
    int mu, nu, tu;
} Crosslist;

// 创建空矩阵
Crosslist *MakeMatrix(int mu, int nu) {
    Crosslist *M  =  (Crosslist *)malloc(sizeof(Crosslist));
    if (!M) exit(1);
    M->rhead  =  (OLink *)calloc(mu, sizeof(OLink)); // calloc自动置0
    M->chead  =  (OLink *)calloc(nu, sizeof(OLink));
    M->mu  =  mu;
    M->nu  =  nu;
    M->tu  =  0;
    return M;
}

typedef struct{
    int matr;
    int value;
    int x;
    int y;
}data;

// 插入非零元素
void Insert(Crosslist *M, int px, int py, int d) {
    if (d  ==  0) return;
    OLnode *p  =  (OLnode *)malloc(sizeof(OLnode));
    p->x  =  px; p->y  =  py; p->data  =  d;
    p->right  =  p->down  =  NULL;

    // 行插入（有序）
    if (!M->rhead[px] || M->rhead[px]->y > py) {
        p->right  =  M->rhead[px];
        M->rhead[px]  =  p;
    } else {
        //利用q来找到插入的位置
        OLnode *q  =  M->rhead[px];
        while (q->right && q->right->y < py) q  =  q->right;
        p->right  =  q->right;
        q->right  =  p;
    }

    // 列插入（有序）
    if (!M->chead[py] || M->chead[py]->x > px) {
        p->down  =  M->chead[py];
        M->chead[py]  =  p;
    } else {
        OLnode *q  =  M->chead[py];
        while (q->down && q->down->x < px) q  =  q->down;
        p->down  =  q->down;
        q->down  =  p;
    }
    M->tu++;
}

// 删除元素
void Del(Crosslist *M, int px, int py) {
    OLnode *p, *q  =  NULL;
    // 行删除
    if (!M->rhead[px]) return;
    if (M->rhead[px]->y  ==  py) {
        q  =  M->rhead[px];
        M->rhead[px]  =  q->right;
    } else {
        for (p  =  M->rhead[px]; p->right && p->right->y < py; p  =  p->right);
        q  =  p->right;
        p->right  =  q->right;
    }
    // 列删除
    if (!M->chead[py]) return;
    if (M->chead[py]->x  ==  px) {
        q  =  M->chead[py];
        M->chead[py]  =  q->down;
    } else {
        for (p  =  M->chead[py]; p->down && p->down->x < px; p  =  p->down);
        q  =  p->down;
        p->down  =  q->down;
    }
    M->tu--;
}

// 矩阵加法：B加到A上
void AddMatr(Crosslist *A, Crosslist *B) {
    for (int i  =  0; i < B->mu; i++) {
        if (!B->rhead[i]) continue;

        for (OLnode *p  =  B->rhead[i]; p; p  =  p->right) {
            // 查找A中是否有相同位置
            OLnode *q  =  A->rhead[i];
            while (q && q->y < p->y) q  =  q->right; 
            if (q && q->y  ==  p->y) {
                q->data +=  p->data;
                if (q->data  ==  0) Del(A, i, q->y);
            } else {
                Insert(A, i, p->y, p->data);
            }
        }
    }
}

//打印结果
//利用这种输出方法来避免结尾不必要空格的出现
void printMatr(Crosslist *M) {
    int first  =  1;
    // 输出V数列
    for (int i  =  0; i < M->mu; i++) {
        for (OLnode *p  =  M->rhead[i]; p; p  =  p->right) {
            if (first) { printf("%d", p->data); first  =  0; }
            else printf(" %d", p->data);
        }
    }
    // 输出B矩阵
    int a[MAX][MAX]  =  {0};
    for (int i  =  0; i < M->mu; i++)
        for (OLnode *p  =  M->rhead[i]; p; p  =  p->right)
            a[i][p->y]  =  1;
    for (int i  =  0; i < M->mu; i++) {
        printf("\n%d", a[i][0]);
        for (int j  =  1; j < M->nu; j++)
            printf(" %d", a[i][j]);
    }
}

int main() {
    int m, n, tmp;
    scanf("%d %d", &m, &n);
    Crosslist *A  =  MakeMatrix(m, n);
    Crosslist *B  =  MakeMatrix(m, n);
    int va[MAX], vb[MAX], na  =  0, nb  =  0;

    // 读入A的V数组
    char c;
    while (scanf("%d", &va[na])  ==  1) {
        c  =  getchar();
        if (c  ==  '\n') break;
        na++;
    }
    na++; // 最后一个数

    // 读入A的B矩阵
    int ax[MAX], ay[MAX], ap  =  0;
    for (int i  =  0; i < m; i++)
        for (int j  =  0; j < n; j++) {
            scanf("%d", &tmp);
            if (tmp  ==  1) {
                ax[ap]  =  i;
                ay[ap]  =  j;
                ap++;
            }
        }

    for (int i  =  0; i < na; i++)
        Insert(A, ax[i], ay[i], va[i]);

    // 读入B的V数组
    nb  =  0;
    while (scanf("%d", &vb[nb])  ==  1) {
        c  =  getchar();
        if (c  ==  '\n') break;
        nb++;
    }
    nb++;

    // 读入B的B矩阵
    int bx[MAX], by[MAX], bp  =  0;
    for (int i  =  0; i < m; i++)
        for (int j  =  0; j < n; j++) {
            scanf("%d", &tmp);
            if (tmp  ==  1) {
                bx[bp]  =  i;
                by[bp]  =  j;
                bp++;
            }
        }
    for (int i  =  0; i < nb; i++)
        Insert(B, bx[i], by[i], vb[i]);

    AddMatr(A, B);
    printMatr(A);

    return 0;
}
