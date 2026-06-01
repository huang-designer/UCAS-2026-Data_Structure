#include <stdio.h>
#include <string.h>

void getMaxRepeatSubstr(char s[100]){
  int n=strlen(s);
  int maxLen=0;
  int startPos=0;
  for (int i = 0; i < n; i++) {
    for (int len = 1; len <= n - i; len++) {
      int found = 0;
      for (int j = i + 1; j <= n - len; j++) {
        int match = 1;
        for (int k = 0; k < len; k++) {
          if (s[i + k] != s[j + k]) {
            match = 0;
            break;
          }
        }
        if (match) {
          found = 1;
          break;
        }
      }
      if (found && len > maxLen) {
        maxLen = len;
        startPos = i;
      }
    }
  }
  if (maxLen == 0) {
    printf("-1\n");
  } else {
    for (int i = 0; i < maxLen; i++) {
      printf("%c", s[startPos + i]);
    }
    printf(" %d\n", startPos);
  }
}

int main() {
    char s[1000];
    scanf("%s", s);
    getMaxRepeatSubstr(s);
    return 0;
}
