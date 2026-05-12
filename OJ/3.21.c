#include <stdio.h>
#define MAXSIZE 100

// 栈结构体
typedef struct {
    char data[MAXSIZE];
    int top;
} stack;

// 初始化栈
void InitStack(stack *s) {
    s->top = -1;
}

// 判断栈空
int IsEmpty(stack *s) {
    return s->top == -1;
}

// 入栈
int push(stack *s, char x) {
    if (s->top == MAXSIZE - 1) return 0;
    s->data[++s->top] = x;
    return 1;
}

// 出栈
int pop(stack *s, char *x) {
    if (IsEmpty(s)) return 0;
    *x = s->data[s->top--];
    return 1;
}

// 取栈顶元素
char getTop(stack *s) {
    if (!IsEmpty(s)) return s->data[s->top];
    return '\0';
}

// 判断是否为运算符
int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// 返回运算符优先级
int priority(char c) {
    if (c == '*' || c == '/') return 2;
    if (c == '+' || c == '-') return 1;
    return 0; // (
}

int main() {
    stack s;
    InitStack(&s);
    char ch, temp;

    // 逐字符读取表达式，直到换行
    while ((ch = getchar()) != '\n') {
        // 1. 字母直接输出
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
            printf("%c", ch);
        }
        // 2. 左括号直接入栈
        else if (ch == '(') {
            push(&s, ch);
        }
        // 3. 右括号：出栈直到 (
        else if (ch == ')') {
            while (getTop(&s) != '(') {
                pop(&s, &temp);
                printf("%c", temp);
            }
            pop(&s, &temp); // 弹出 ( 不输出
        }
        // 4. 运算符
        else if (isOperator(ch)) {
            while (!IsEmpty(&s) && priority(getTop(&s)) >= priority(ch)) {
                pop(&s, &temp);
                printf("%c", temp);
            }
            push(&s, ch);
        }
    }

    // 5. 剩余运算符全部出栈
    while (!IsEmpty(&s)) {
        pop(&s, &temp);
        printf("%c", temp);
    }

    return 0;
}
