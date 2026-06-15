#include <stdio.h>

int main() {
    int c, next; // 用 int 类型接收 getchar() 才能正确判断 EOF

    while ((c = getchar()) != EOF) {
        if (c == '/') {
            next = getchar();
            if (next == '*') {
                // 进入注释状态，开始寻找 */
                int in_comment = 1;
                while (in_comment) {
                    c = getchar();
                    if (c == EOF) {
                        break; // 防止文件意外结束导致死循环
                    }
                    if (c == '*') {
                        next = getchar();
                        if (next == '/') {
                            in_comment = 0; // 成功匹配到 */，退出注释
                        } else {
                            // 如果 * 后面不是 /，把读到的新字符放回或继续判断
                            // 这里可以通过让 c 变成 next，在下一轮循环中继续判断它是不是另一个 '*'
                            if (next == EOF) break;
                            // 如果 next 是 '*', 下一轮循环开头 c == '*' 依旧成立
                            // 所以这里把 next 赋给 c 即可
                            c = next; 
                            if (c == '*') {
                                // 技巧：如果连续出现 **, 倒退回去重新检查
                                // 通过控制循环逻辑，这里可以简单通过判断处理
                                // 为了逻辑更清晰，可以用下面的标准状态机写法
                            }
                        }
                    }
                }
            } else {
                // 不是注释，把 '/' 和刚刚偷看的字符都原样输出
                putchar(c);
                if (next != EOF) {
                    putchar(next);
                }
            }
        } else {
            // 普通字符，直接输出
            putchar(c);
        }
    }
    return 0;
}
