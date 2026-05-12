#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct PolyTerm {
    int base;
    int exp;
} PolyTerm;

typedef struct PolyNode {
    PolyTerm data;
    struct PolyNode *next;
} PolyNode, *PolyLink;

typedef PolyLink LinkedPoly;

LinkedPoly createPoly() {
    LinkedPoly head = (PolyNode *)malloc(sizeof(PolyNode));
    head->next = head;
    return head;
}

//保证函数有序，合并同类项
void insertPoly(LinkedPoly poly, int base, int exp) {
    if (base == 0) return;
    PolyNode *p = poly, *q = poly->next;
    while (q != poly && q->data.exp > exp) {
        p = q;
        q = q->next;
    }
    if (q != poly && q->data.exp == exp) {
        q->data.base += base;
        if (q->data.base == 0) {
            p->next = q->next;
            free(q);
        }
    } else {
        PolyNode *node = (PolyNode *)malloc(sizeof(PolyNode));
        node->data.base = base;
        node->data.exp = exp;
        node->next = q;
        p->next = node;
    }
}

LinkedPoly derivativePoly(LinkedPoly poly) {
    LinkedPoly res = createPoly();
    PolyNode *p = poly->next;
    while (p != poly) {
        if (p->data.exp != 0) {
            insertPoly(res, p->data.base * p->data.exp, p->data.exp - 1);
        }
        p = p->next;
    }
    return res;
}

void trim(char *s) {
    char *p = s, *q = s;
    while (isspace(*p)) ++p;
    while (*p) *q++ = *p++;
    *q = 0;
    while (--q >= s && isspace(*q)) *q = 0;
}

void parsePoly(char *str, LinkedPoly poly) {
    trim(str);
    int i = 0, len = strlen(str);
    while (i < len) {
        int sign = 1, base = 0, exp = 0, hasbase = 0;
        while (i < len && isspace(str[i])) ++i;
        if (i < len && (str[i] == '+' || str[i] == '-')) {
            if (str[i] == '-') sign = -1;
            ++i;
        }
        while (i < len && isspace(str[i])) ++i;
        int start = i;
        while (i < len && isdigit(str[i])) ++i;
        if (i > start) {
            base = atoi(str + start);
            hasbase = 1;
        }
        if (i < len && str[i] == 'x') {
            if (!hasbase) base = 1;
            ++i;
            if (i < len && str[i] == '^') {
                ++i;
                int exp_start = i;
                while (i < len && isdigit(str[i])) ++i;
                exp = atoi(str + exp_start);
            } else {
                exp = 1;
            }
        } else {
            exp = 0;
        }
        insertPoly(poly, sign * base, exp);
        while (i < len && isspace(str[i])) ++i;
    }
}

void printPoly(LinkedPoly poly) {
    PolyNode *p = poly->next;
    int first = 1;
    while (p != poly) {
        int c = p->data.base, e = p->data.exp;
        if (!first) printf(" ");
        if (c < 0)
            printf("- ");
        else if (!first)
            printf("+ ");
        if (abs(c) != 1 || e == 0)
            printf("%d", abs(c));
        if (e > 0) {
            printf("x");
            if (e > 1) printf("^%d", e);
        }
        first = 0;
        p = p->next;
    }
    if (first) printf("0");
    printf("\n");
}

int main() {
    char s[500];
    fgets(s, sizeof(s), stdin);
    if (s[strlen(s)-1] == '\n') s[strlen(s)-1] = '\0';

    LinkedPoly poly = createPoly();
    parsePoly(s, poly);
    LinkedPoly der = derivativePoly(poly);
    printPoly(der);

    return 0;
}
