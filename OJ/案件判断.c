#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

// parent 数组大小开到 2 * MAXN，因为需要存储每个案件的对立面
int parent[2 * MAXN];

// 初始化并查集
void init(int n) {
    for (int i = 1; i <= 2 * n; ++i) {
        parent[i] = i;
    }
}

// 查找祖先节点（带路径压缩）
int find_set(int x) {
    if (parent[x] == x) {
        return x;
    }
    return parent[x] = find_set(parent[x]); // 路径压缩
}

// 合并两个集合
void union_sets(int x, int y) {
    int root_x = find_set(x);
    int root_y = find_set(y);
    if (root_x != root_y) {
        parent[root_x] = root_y;
    }
}

void solve() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return;

    init(n);

    for (int i = 0; i < m; ++i) {
        char type;
        int a, b;
        // 注意 %c 前面加一个空格，用来跳过换行符和空格
        scanf(" %c %d %d", &type, &a, &b);

        if (type == 'D') {
            // a 和 b 的对立面 (b + n) 属于同一团伙
            // b 和 a 的对立面 (a + n) 属于同一团伙
            union_sets(a, b + n);
            union_sets(b, a + n);
        } else if (type == 'A') {
            // 特殊情况：如果是同一个编号的案件自己问自己
            if (a == b) {
                printf("是同一个团伙所为\n");
                continue;
            }

            int root_a = find_set(a);
            int root_b = find_set(b);
            int root_b_enemy = find_set(b + n);

            if (root_a == root_b) {
                printf("是同一个团伙所为\n");
            } else if (root_a == root_b_enemy) {
                printf("不是同一个团伙所为\n");
            } else {
                printf("不确定\n");
            }
        }
    }
}

int main() {
    int t;
    if (scanf("%d", &t) == 1) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
