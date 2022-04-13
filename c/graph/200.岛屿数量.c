/*
给你一个由'1'（陆地）和'0'（水）组成的的二维网格，请你计算网格中岛屿的数量。
岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。
此外，你可以假设该网格的四条边均被水包围。

示例1：
输入：grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
输出：1

示例2：
输入：grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
输出：3

提示：
m == grid.length
n == grid[i].length
1 <= m, n <= 300
grid[i][j]的值为'0'或'1'
*/

// DFS
void dfs(char **grid, int row, int col, int i, int j) {
  if (grid[i][j] == '1')
    grid[i][j] = '0';
  else
    return;
  if (i != 0) dfs(grid, row, col, i - 1, j);
  if (i != row - 1) dfs(grid, row, col, i + 1, j);
  if (j != 0) dfs(grid, row, col, i, j - 1);
  if (j != col - 1) dfs(grid, row, col, i, j + 1);
}
int numIslands(char **grid, int gridSize, int *gridColSize) {
  int i, j, count = 0;
  for (i = 0; i < gridSize; i++) {
    for (j = 0; j < gridColSize[i]; j++) {
      if (grid[i][j] == '1') {
        dfs(grid, gridSize, gridColSize[i], i, j);
        count++;
      }
    }
  }
  return count;
}

// BFS

// Union-Find算法
int count;
int *parent;
int *size;
void UF(int n) {
  // count = n; // 初始化和别的题不一样
  parent = (int *)malloc(sizeof(int) * n);
  size = (int *)malloc(sizeof(int) * n);
  for (int i = 0; i < n; i++) {
    parent[i] = i;
    size[i] = 1;
  }
}
int Find(int x) {
  while (parent[x] != x) {
    parent[x] = parent[parent[x]];
    x = parent[x];
  }
  return x;
}
void Union(int p, int q) {
  int rootP = Find(p);
  int rootQ = Find(q);
  if (rootP == rootQ) return;

  if (size[rootP] > size[rootQ]) {
    parent[rootQ] = rootP;
    size[rootP] += size[rootQ];
  } else {
    parent[rootP] = rootQ;
    size[rootQ] += size[rootP];
  }
  count--;
}
// 这个题用不上
// bool Connected(int p, int q) {
//   int rootP = Find(p);
//   int rootQ = Find(q);
//   return rootP == rootQ;
// }
int numIslands(char **grid, int gridSize, int *gridColSize) {
  UF(gridSize * gridColSize[0]);
  count = 0;

  for (int i = 0; i < gridSize; ++i) {
    for (int j = 0; j < *gridColSize; ++j) {
      if (grid[i][j] == '0') {
        continue;
      } else {
        ++count;  // 值为1的算一个树
      }
      if (j > 0 && grid[i][j - 1] == '1') {
        Union(gridColSize[0] * i + j, gridColSize[0] * i + j - 1);
      }
      if (i > 0 && grid[i - 1][j] == '1') {
        Union(gridColSize[0] * i + j, gridColSize[0] * (i - 1) + j);
      }
    }
  }

  return count;
}

// 并集查
struct Pos {
  int x;
  int y;
};
int count = 0;
struct Pos **init(char **grid, int gridSize, int *gridColSize) {
  count = 0;
  struct Pos **uf = (struct Pos **)malloc(sizeof(struct Pos *) * gridSize);
  for (int row = 0; row < gridSize; row++) {
    uf[row] = (struct Pos *)malloc(sizeof(struct Pos) * *gridColSize);
    for (int col = 0; col < *gridColSize; col++) {
      uf[row][col].x = row;
      uf[row][col].y = col;
      if (grid[row][col] == '1') count++;
    }
  }
  return uf;
}
struct Pos find(struct Pos **uf, struct Pos pos) {
  struct Pos *p = &uf[pos.x][pos.y];
  if (p->x != pos.x || p->y != pos.y) {
    *p = find(uf, uf[p->x][p->y]);
  }
  return *p;
}
void merge(struct Pos **uf, struct Pos a, struct Pos b) {
  struct Pos aa = find(uf, a);
  struct Pos bb = find(uf, b);

  if (aa.x == bb.x && aa.y == bb.y) return;

  uf[b.x][b.y] = aa;
  count--;
}
int numIslands(char **grid, int gridSize, int *gridColSize) {
  struct Pos **uf = init(grid, gridSize, gridColSize);

  for (int row = 0; row < gridSize; row++) {
    for (int col = 0; col < *gridColSize; col++) {
      if (grid[row][col] == '0') continue;
      if (col > 0 && (grid[row][col - 1] == '1')) {
        merge(uf, uf[row][col - 1], uf[row][col]);
      }
      if (row > 0 && (grid[row - 1][col] == '1')) {
        merge(uf, uf[row - 1][col], uf[row][col]);
      }
    }
  }
  return count;
}