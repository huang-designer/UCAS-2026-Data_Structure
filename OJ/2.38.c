#include<stdio.h>
#include<stdlib.h>

typedef struct DLnode{
    int data;
    struct DLnode* next;
    struct DLnode* prior;
    int freq;
    int print;
    int first_visit_order; // 新增：首次被访问的序号，未访问为-1
}DLnode;

typedef struct{
    DLnode* first;
}DLlist;

DLnode* makenode(int value){
    DLnode* p = (DLnode*)malloc(sizeof(DLnode));
    p->data = value;
    p->next = NULL;
    p->prior = NULL;
    p->print = 0;
    p->freq = 0;
    p->first_visit_order = -1;
    return p;
}

DLlist* Init(){
    DLlist* L = (DLlist*)malloc(sizeof(DLlist));
    DLnode* temp = makenode(0);
    L->first = temp;
    return L;
}

void Addnode(DLlist* L, int value){
    DLnode* p = L->first;
    DLnode* q = makenode(value);
    while(p->next){
        p = p->next;
    }
    p->next = q;
    q->prior = p;
}

// 访问序号计数器，在 main 中声明并传递
void Locate(DLlist* L, int n, int order){
    DLnode* p = L->first->next;
    while(p){
        if(p->data == n){
            p->freq++;
            // 只在第一次被访问时赋值
            if(p->first_visit_order == -1){
                p->first_visit_order = order;
            }
            // 重新排序
            if(p->prior) p->prior->next = p->next;
            if(p->next) p->next->prior = p->prior;
            DLnode* q = L->first->next;
            DLnode* prev = L->first;
            // 先按freq排序，freq相同则比较first_visit_order
            while(q &&
                  (q->freq > p->freq ||
                    (q->freq == p->freq && 
                     (q->first_visit_order != -1 && p->first_visit_order != -1 && q->first_visit_order < p->first_visit_order))
                  )
                ){
                prev = q;
                q = q->next;
            }
            p->next = q;
            p->prior = prev;
            prev->next = p;
            if(q) q->prior = p;
            break;
        }
        p = p->next;
    }
}

void printList(DLlist* L, int n) {
    DLnode* p = L->first->next;
    for (int i = 0; i < n && p; i++, p = p->next) {
        if (i) printf(" ");
        printf("%d", p->data);
    }
}

// void Locate(DLlist* L, int n){
//     DLnode* p=L->first->next;
//     //p指向第一个有数据的结点
//     while(p){
//         if(p->data==n){
//             p->freq++;
//             break;
//         }
//         p = p->next;
//     }
// }

// //用逐个扫描的办法来打印, 用了一步懒排序

// void printList(DLlist* L,int n){
//     int maxf = 0;
//     int pos = 1;

//     for(int i = 0; i < n; i++){
//         //用于存储频率最高的结点
//         DLnode* p = L->first->next;
//         DLnode* maxnode = NULL;
//         while(p){
//             //表示有一个频率更高的数,并且没被打印过
//             if(p->print==0 && (maxnode==NULL ||  maxnode->freq < p->freq)){
//                 maxnode = p;
//             }
//             p=p->next;
//         }
//         if(i==0){
//             printf("%d",maxnode->data);
//         }
//         else{
//             printf(" %d",maxnode->data);
//         }
//         maxnode->print = 1;
//     }
//     //printf("\n");
// }

int main(){
    int n;
    int value;
    scanf("%d",&n);
    DLlist* L = Init();
    for(int i = 0; i < n;i++){
        scanf("%d",&value);
        Addnode(L,value);
    }
    int v;
    char c;
    int visit_order = 0; // 记录访问的顺序, 勇敢与输出oj里想要的顺序
    while(1){
        if(scanf("%d%c",&v,&c)!=2) break;
        Locate(L, v, visit_order++);
        if(c=='\n' || c==EOF){
            break;
        }
    }
    printList(L,n);
    return 0;
}
