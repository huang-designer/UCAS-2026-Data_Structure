#include <stdio.h>
#include <string.h>

#define MAX 105

// 上下左右四个方向
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

typedef struct {
    int x, y;
} Node;

Node pre[MAX][MAX];
int vis[MAX][MAX];
char maze[MAX][MAX];
int X, Y;

// 标准 BFS：从起点 (sx, sy) 搜到终点 (ex, ey)
int bfs(int sx, int sy, int ex, int ey) {
    // 每次搜寻前清空访问标记和前驱记录
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < X; i++) {
        for (int j = 0; j < Y; j++) {
            pre[i][j] = (Node){-1, -1};
        }
    }

    Node q[MAX * MAX];
    int head = 0, tail = 0;

    q[tail++] = (Node){sx, sy};
    vis[sx][sy] = 1;

    while (head < tail) {
        Node cur = q[head++];
        int x = cur.x;
        int y = cur.y;

        if (x == ex && y == ey) {
            return 1; // 成功找到目标
        }

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            // 判断边界、是否为墙、是否已访问
            if (nx >= 0 && nx < X && ny >= 0 && ny < Y && maze[nx][ny] != '1' && !vis[nx][ny]) {
                vis[nx][ny] = 1;
                pre[nx][ny] = (Node){x, y}; // 记录前驱
                q[tail++] = (Node){nx, ny};
            }
        }
    }
    return 0; // 无法到达
}

// 递归正向打印第一阶段路径 (包含起点和终点)
void printPath1(int x, int y) {
    if (pre[x][y].x != -1) {
        printPath1(pre[x][y].x, pre[x][y].y);
    }
    printf("%d %d\n", x + 1, y + 1);
}

// 递归正向打印第二阶段路径 (跳过起点，避免与第一阶段的终点重复)
void printPath2(int x, int y, int sx, int sy) {
    if (pre[x][y].x != -1) {
        printPath2(pre[x][y].x, pre[x][y].y, sx, sy);
    }
    if (!(x == sx && y == sy)) {
        printf("%d %d\n", x + 1, y + 1);
    }
}

int main() {
    int rx = 0, ry = 0; // R 的坐标
    int yx = 0, yy = 0; // Y 的坐标
    int cx = 0, cy = 0; // C 的坐标

    if (scanf("%d %d", &X, &Y) != 2) return 0;
    
    // 吃掉换行符，防止影响后面的字符读取
    getchar(); 

    // 读取迷宫地图并记录关键点位置
    for (int i = 0; i < X; i++) {
        for (int j = 0; j < Y; j++) {
            scanf(" %c", &maze[i][j]); // 用空格过滤掉空白字符
            if (maze[i][j] == 'R') {
                rx = i; ry = j;
            } else if (maze[i][j] == 'Y') {
                yx = i; yy = j;
            } else if (maze[i][j] == 'C') {
                cx = i; cy = j;
            }
        }
    }

    // 第一步：计算 R -> Y
    int ok1 = bfs(rx, ry, yx, yy);
    if (!ok1) return 0; // 如果拿不到钥匙，直接结束

    // 第二步：计算 Y -> C
    int ok2 = bfs(yx, yy, cx, cy);
    if (!ok2) return 0; // 如果拿到了钥匙但去不了出口，直接结束

    // -------- 开始按顺序输出完美路径 --------
    
    // 重新生成第一阶段的前驱树并打印
    bfs(rx, ry, yx, yy);
    printPath1(yx, yy);

    // 重新生成第二阶段的前驱树并打印（跳过重复的 Y 点）
    bfs(yx, yy, cx, cy);
    printPath2(cx, cy, yx, yy);

    return 0;
}
