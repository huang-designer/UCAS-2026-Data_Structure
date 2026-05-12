#include <stdio.h>

#define MAXINT 4294967295U

int main() {
    int n, arrsize;
    scanf("%d %d", &n, &arrsize);

    if (n > arrsize) {
        printf("-1\n");
        return 0;
    }

    unsigned long long result = 1;
    int is_error = 0;

    for (int i = 0; i < n; i++) {
        // 先判断当前值是否溢出！
        if (result > MAXINT) {
            is_error = 1;
            break;
        }
        // 再计算下一个
        if (i > 0) {
            result = result * i * 2; 
        }
    }

    if (is_error) {
        printf("-1\n");
    } else {
        unsigned long long val = 1;
        for (int i = 0; i < n; i++) {
            printf("%llu", val);
            if (i < n-1) printf(" ");
            
            if (i < n-1) {
                val = val * (i+1) * 2;
            }
        }
        printf("\n");
    }

    return 0;
}
