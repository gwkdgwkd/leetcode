/*
给你一个m x n的矩阵board，由若干字符'X'和'O'，
找到所有被'X'围绕的区域，并将这些区域里所有的'O'用'X'填充。

示例1：
输入：board = [["X","X","X","X"],
              ["X","O","O","X"],
              ["X","X","O","X"],
              ["X","O","X","X"]]
输出：[["X","X","X","X"],
      ["X","X","X","X"],
      ["X","X","X","X"],
      ["X","O","X","X"]]
解释：被围绕的区间不会存在于边界上，换句话说，任何边界上的'O'都不会被填充为'X'。
任何不在边界上，或不与边界上的'O'相连的'O'最终都会被填充为'X'。
如果两个元素在水平或垂直方向相邻，则称它们是“相连”的。

示例2：
输入：board = [["X"]]
输出：[["X"]]

提示：
m == board.length
n == board[i].length
1 <= m, n <= 200
board[i][j]为'X'或'O'
*/

// 深度优先遍历
void dfs(char** board, int x, int y, int row, int col) {
  // 从边界的'O'出发遍历与之直接或间接相邻的'O'
  if (x < 0 || x >= row || y < 0 || y >= col || board[x][y] != 'O') {
    return;
  }

  board[x][y] = 'Z';  // 暂时将与边界上的'O'直接或间接相邻的'O'标记为'Z'
  dfs(board, x + 1, y, row, col);  // 向下遍历
  dfs(board, x - 1, y, row, col);  // 向上遍历
  dfs(board, x, y + 1, row, col);  // 向右遍历
  dfs(board, x, y - 1, row, col);  // 向左遍历
}
void solve(char** board, int boardSize, int* boardColSize) {
  if (board == NULL || boardSize == 0 || (*boardColSize) == 0) {
    return;
  }

  int row = boardSize;
  int col = (*boardColSize);

  int i;
  for (i = 0; i < col; i++) {  // 寻找与第一行的'O'直接或间接相邻的'O'
    if (board[0][i] == 'O') {
      dfs(board, 0, i, row, col);
    }
  }

  for (i = 0; i < col; i++) {  // 寻找与最后一行的'O'直接或间接相邻的'O'
    if (board[row - 1][i] == 'O') {
      dfs(board, row - 1, i, row, col);
    }
  }

  for (i = 1; i < row; i++) {  // 寻找与第一列的'O'直接或间接相邻的'O'
    if (board[i][0] == 'O') {
      dfs(board, i, 0, row, col);
    }
  }

  for (i = 1; i < row; i++) {  // 寻找与最后一列的'O'直接或间接相邻的'O'
    if (board[i][col - 1] == 'O') {
      dfs(board, i, col - 1, row, col);
    }
  }

  int j;
  for (i = 0; i < row; i++) {  // 将被'X'围绕的'O'转换为'X'
    for (j = 0; j < col; j++) {
      if (board[i][j] == 'O') {
        board[i][j] = 'X';
      }
    }
  }

  for (i = 0; i < row; i++) {
    // 之前将不被'X'围绕的'O'转换为'Z'，现在恢复为'O'
    for (j = 0; j < col; j++) {
      if (board[i][j] == 'Z') {
        board[i][j] = 'O';
      }
    }
  }
}

// Union-Find算法
// 很多使用DFS深度优先算法解决的问题，也可以用Union-Find算法解决。
int count;    // 连通分量个数
int* parent;  // 存储一棵树
int* size;    // 记录树的重量
void UF(int n) {
  count = n;
  parent = (int*)malloc(sizeof(int) * n);
  size = (int*)malloc(sizeof(int) * n);
  for (int i = 0; i < n; i++) {
    parent[i] = i;
    size[i] = 1;
  }
}
int Find(int x) {
  while (parent[x] != x) {
    // 进行路径压缩
    parent[x] = parent[parent[x]];
    x = parent[x];
  }
  return x;
}
void Union(int p, int q) {
  int rootP = Find(p);
  int rootQ = Find(q);
  if (rootP == rootQ) return;

  // 小树接到大树下面，较平衡
  if (size[rootP] > size[rootQ]) {
    parent[rootQ] = rootP;
    size[rootP] += size[rootQ];
  } else {
    parent[rootP] = rootQ;
    size[rootQ] += size[rootP];
  }
  count--;
}
bool Connected(int p, int q) {
  int rootP = Find(p);
  int rootQ = Find(q);
  return rootP == rootQ;
}
// 使用Union-Find算法
void solve(char** board, int boardSize, int* boardColSize) {
  // 不需要被替换的O看成一个拥有独门绝技的门派，它们有一个共同祖师爷叫dummy，
  // 这些O和dummy互相连通，而那些需要被替换的O与dummy不连通。
  if (boardSize == 0) return;

  int m = boardSize;
  int n = boardColSize[0];
  // 给dummy留一个额外位置
  UF(m * n + 1);
  int dummy = m * n;
  // 将首列和末列的O与dummy连通
  for (int i = 0; i < m; i++) {
    if (board[i][0] == 'O') Union(i * n, dummy);
    if (board[i][n - 1] == 'O') Union(i * n + n - 1, dummy);
  }
  // 将首行和末行的O与dummy连通
  for (int j = 0; j < n; j++) {
    if (board[0][j] == 'O') Union(j, dummy);
    if (board[m - 1][j] == 'O') Union(n * (m - 1) + j, dummy);
  }
  // 方向数组d是上下左右搜索的常用手法
  int d[4][2] = {{1, 0}, {0, 1}, {0, -1}, {-1, 0}};
  for (int i = 1; i < m - 1; i++)
    for (int j = 1; j < n - 1; j++)
      if (board[i][j] == 'O')
        // 将此O与上下左右的O连通
        for (int k = 0; k < 4; k++) {
          int x = i + d[k][0];
          int y = j + d[k][1];
          if (board[x][y] == 'O') Union(x * n + y, i * n + j);
        }
  // 所有不和dummy连通的O(没有和边上的O相连的)，都要被替换
  for (int i = 1; i < m - 1; i++) {
    for (int j = 1; j < n - 1; j++) {
      if (!Connected(dummy, i * n + j)) board[i][j] = 'X';
    }
  }
}

class UF {
 public:
  UF(int n) : count(n) {
    parent.reserve(n);
    size.reserve(n);
    for (int i = 0; i < n; ++i) {
      parent[i] = i;
      size[i] = 1;
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
  bool Connected(int p, int q) { return Find(p) == Find(q); }

 private:
  int count;
  vector<int> parent;
  vector<int> size;

  int Find(int x) {
    while (parent[x] != x) {
      parent[x] = parent[parent[x]];
      x = parent[x];
    }
    return x;
  }
};

class Solution {
 public:
  void solve(vector<vector<char>>& board) {
    int m = board.size();
    int n = board[0].size();
    UF uf(m * n + 1);
    int dummy = m * n;

    for (int i = 0; i < m; ++i) {
      if (board[i][0] == 'O') {
        uf.Union(dummy, i * n);
      }
      if (board[i][n - 1] == 'O') {
        uf.Union(dummy, i * n + n - 1);
      }
    }
    for (int j = 0; j < n; ++j) {
      if (board[0][j] == 'O') {
        uf.Union(dummy, j);
      }
      if (board[m - 1][j] == 'O') {
        uf.Union(dummy, n * (m - 1) + j);
      }
    }

    int d[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    for (int i = 1; i < m - 1; ++i) {
      for (int j = 1; j < n - 1; ++j) {
        if (board[i][j] == 'O') {
          for (int k = 0; k < 4; ++k) {
            int x = i + d[k][0];
            int y = j + d[k][1];
            if (board[x][y] == 'O') {
              uf.Union(i * n + j, x * n + y);
            }
          }
        }
      }
    }

    for (int i = 1; i < m - 1; ++i) {
      for (int j = 1; j < n - 1; ++j) {
        if (!uf.Connected(i * n + j, dummy)) {
          board[i][j] = 'X';
        }
      }
    }
  }
};