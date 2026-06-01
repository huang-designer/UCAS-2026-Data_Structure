#include <stdio.h>
#include <string.h>

int main() {
    char s[1000], t[1000];
    char r[1000];
    int pos[1000];
    int r_len = 0;

    scanf("%s %s", s, t);

    for (int i = 0; s[i] != '\0'; i++) {
        char c = s[i];
        int in_t = 0;
        int in_r = 0;

        for (int j = 0; t[j] != '\0'; j++) {
            if (c == t[j]) {
                in_t = 1;
                break;
            }
        }
        if (in_t) continue;

        for (int j = 0; j < r_len; j++) {
            if (c == r[j]) {
                in_r = 1;
                break;
            }
        }
        if (in_r) continue;
        r[r_len] = c;
        pos[r_len] = i;
        r_len++;
    }

    if (r_len == 0) {
        printf("-1\n");
    } else {
        for (int i = 0; i < r_len; i++) {
            printf("%c", r[i]);
        }
        printf(" ");
        for (int i = 0; i < r_len; i++) {
            printf("%d", pos[i]);
        }
        printf("\n");
    }

    return 0;
}
