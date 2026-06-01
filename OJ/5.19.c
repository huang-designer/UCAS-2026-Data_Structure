#include <stdio.h>
#define M 100
#define N 100

int main() {
    int a[M][N];
    int row, col;
    scanf("%d %d", &row, &col);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    int find = 0;
    int first = 1;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            int isRowMin = 1;
            for (int k = 0; k < col; k++) {
                if (a[i][j] > a[i][k]) {
                    isRowMin = 0;
                    break;
                }
            }
            
            if (!isRowMin) continue;

            int isColMax = 1;
            for (int k = 0; k < row; k++) {
                if (a[i][j] < a[k][j]) {
                    isColMax = 0;
                    break;
                }
            }
            if (isColMax) {
                if (first) {
                    printf("%d", a[i][j]);
                    first = 0;
                } else {
                    printf(" %d", a[i][j]);
                }
                find = 1;
            }
        }
    }

    if (!find) {
        printf("-1");
    }
    printf("\n");

    return 0;
}
