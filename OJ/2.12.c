#include <stdio.h>
#include <string.h>

#define MAX_SIZE 101  // 每个顺序表最多 100 个元素

// 分割字符串，按逗号分隔，存入数组，返回元素个数
int split(char *str, char arr[][MAX_SIZE]) {
    int count = 0;
    char *token = strtok(str, ",");
    while (token != NULL && count < MAX_SIZE) {
        strcpy(arr[count++], token);
        token = strtok(NULL, ",");
    }
    return count;
}

int main() {
    char A_str[1000], B_str[1000];
    char A[MAX_SIZE][MAX_SIZE], B[MAX_SIZE][MAX_SIZE];
    int lenA, lenB;
    int i = 0;

    // 输入两行
    fgets(A_str, sizeof(A_str), stdin);
    fgets(B_str, sizeof(B_str), stdin);

    // 去掉换行符（fgets 会读取换行）
    A_str[strcspn(A_str, "\n")] = '\0';
    B_str[strcspn(B_str, "\n")] = '\0';

    // 分割成顺序表
    lenA = split(A_str, A);
    lenB = split(B_str, B);

    // 找最大共同前缀
    while (i < lenA && i < lenB && strcmp(A[i], B[i]) == 0) {
        i++;
    }

    // 按题目规则判断
    int result;
    if (i == lenA && i == lenB) {
        result = 0;        // A = B
    } else if (i == lenA || (i < lenA && i < lenB && strcmp(A[i], B[i]) < 0)) {
        result = 1;        // A < B
    } else {
        result = 2;        // A > B
    }

    printf("%d\n", result);
    return 0;
}
