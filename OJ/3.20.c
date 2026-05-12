#include <stdio.h>

int m,n;
int arr[100][100];
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

void color(int x, int y) {
    if (x < 0 || x >= m || y < 0 || y >= n || arr[x][y] != 1) {
        return;
    }
    arr[x][y] = 2;
    for (int d = 0; d < 4; d++) {
        int nx = x + dx[d];
        int ny = y + dy[d];
        color(nx, ny);
    }
}

int main(){
  int p,q,s;
  scanf("%d %d %d %d %d",&m,&n,&p,&q,&s);
  for(int i=0;i<m;i++){
    for(int j=0;j<n;j++){
      scanf("%d",&arr[i][j]);
    }
  }
  color(p,q);
  for(int i=0;i<m;i++){
    for(int j=0;j<n;j++){
      printf("%d",arr[i][j]);
    }
    printf("\n");
  }  
  return 0;
}
