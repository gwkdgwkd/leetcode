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

class Solution {
 private:
  class UF {
   public:
    int Count() { return count; }
    UF(int n) {
      count = n;
      size.assign(n, 1);
      parent.resize(n);
      for (int i = 0; i < n; ++i) {
        parent[i] = i;
      }
    }
    void Union(int p, int q) {
      int rootP = Find(p);
      int rootQ = Find(q);

      if (rootP == rootQ) {
        return;
      }

      if (size[rootP] > size[rootQ]) {
        parent[rootQ] = rootP;
        size[rootP] += size[rootQ];
      } else {
        parent[rootP] = rootQ;
        size[rootQ] += size[rootP];
      }
      --count;
    }
    // bool Connected(int p, int q) { return Find(p) == Find(q); }

   private:
    int Find(int x) {
      while (parent[x] != x) {
        parent[x] = parent[parent[x]];
        x = parent[x];
      }
      return x;
    }

    vector<int> parent;
    vector<int> size;
    int count;
  };

 public:
  int numIslands(vector<vector<char>> &grid) {
    int m = grid.size();
    int n = grid[0].size();
    int dummy = m * n;  // 虚拟节点，所有的0与虚拟节点连接
    UF uf(dummy + 1);
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] == '0') {
          uf.Union(n * i + j, dummy);
          continue;
        }
        if (i > 0 && grid[i - 1][j] == '1') {
          uf.Union(n * i + j, n * (i - 1) + j);
        }
        if (j > 0 && grid[i][j - 1] == '1') {
          uf.Union(n * i + j, n * i + j - 1);
        }
      }
    }
    return uf.Count() - 1;  // 减去虚拟节点
  }
};