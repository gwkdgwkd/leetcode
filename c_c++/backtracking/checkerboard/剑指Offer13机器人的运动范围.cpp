/*
地上有一个m行n列的方格，从坐标[0,0]到坐标[m-1,n-1]。
一个机器人从坐标[0,0]的格子开始移动，
它每次可以向左、右、上、下移动一格（不能移动到方格外），
也不能进入行坐标和列坐标的数位之和大于k的格子。
例如，当k为18时，机器人能够进入方格[35,37]，因为3+5+3+7=18。
但它不能进入方格[35,38]，因为3+5+3+8=19。
请问该机器人能够到达多少个格子？

示例1：
输入：m = 2, n = 3, k = 1
输出：3

示例2：
输入：m = 3, n = 1, k = 0
输出：1

提示：
1 <= n,m <= 100
0 <= k <= 20
*/

// DFS
bool check(int i, int j, int k) {
  int sum = 0;
  while (i) {
    sum += i % 10;
    i /= 10;
  }
  while (j) {
    sum += j % 10;
    j /= 10;
  }

  return sum <= k;
}
int res;
int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
void dfs(int i, int j, int m, int n, int k, int** visited) {
  if (i >= m || j >= n || visited[i][j] == 1) {
    return;
  }

  if (!check(i, j, k)) {
    return;
  }
  ++res;
  visited[i][j] = 1;
  for (int l = 0; l < 4; ++l) {
    int newi = i + dir[l][0];
    int newj = j + dir[l][1];
    if (newi >= 0 && newi < m && newj >= 0 && newj < n) {
      dfs(newi, newj, m, n, k, visited);
    }
  }
}
int movingCount(int m, int n, int k) {
  res = 0;
  int** visited = malloc(sizeof(int*) * m);
  for (int i = 0; i < m; i++) {
    visited[i] = malloc(sizeof(int) * n);
    memset(visited[i], 0, sizeof(int) * n);
  }

  dfs(0, 0, m, n, k, visited);
  return res;
}

// BFS

// 动态规划
int get(int x) {
  int res = 0;
  for (; x; x /= 10) {
    res += x % 10;
  }
  return res;
}
int movingCount(int m, int n, int k) {
  if (!k) return 1;
  int vis[m][n];
  memset(vis, 0, sizeof(vis));
  int ans = 1;
  vis[0][0] = 1;
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if ((i == 0 && j == 0) || get(i) + get(j) > k) continue;
      // 边界判断
      if (i - 1 >= 0) vis[i][j] |= vis[i - 1][j];
      if (j - 1 >= 0) vis[i][j] |= vis[i][j - 1];
      ans += vis[i][j];
    }
  }
  return ans;
}

class Solution {
  vector<vector<bool>> used;
  int rows;
  int cols;
  int sum;
  int count;
  bool check(int x, int y) {
    int tmp = 0;
    while (x) {
      tmp += x % 10;
      x /= 10;
    }
    while (y) {
      tmp += y % 10;
      y /= 10;
    }

    return tmp <= sum;
  }
  void dfs(int x, int y) {
    if (used[x][y]) {
      return;
    }

    if (!check(x, y)) {
      return;
    }
    ++count;

    int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    used[x][y] = true;
    for (int i = 0; i < 4; ++i) {
      int newx = x + dir[i][0];
      int newy = y + dir[i][1];
      if (0 <= newx && newx < rows && 0 <= newy && newy < cols) {
        dfs(newx, newy);
      }
    }
  }

 public:
  int movingCount(int m, int n, int k) {
    used.assign(m, vector<bool>(n, false));
    rows = m;
    cols = n;
    sum = k;
    count = 0;

    dfs(0, 0);
    return count;
  }
};
