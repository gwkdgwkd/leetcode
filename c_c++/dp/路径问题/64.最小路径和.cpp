/*
给定一个包含非负整数的mxn网格grid，
请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。
说明：每次只能向下或者向右移动一步。

示例1：
输入：grid = [[1,3,1],[1,5,1],[4,2,1]]
输出：7
解释：因为路径1→3→1→1→1的总和最小。

示例2：
输入：grid = [[1,2,3],[4,5,6]]
输出：12

提示：
m == grid.length
n == grid[i].length
1 <= m, n <= 200
0 <= grid[i][j] <= 100
*/

// 剑指OfferII099最小路径之和

// 动态规划
int minPathSum(int** grid, int gridSize, int* gridColSize) {
  int m = gridSize;
  int n = *gridColSize;
  int dp[m][n];
  dp[0][0] = grid[0][0];
  for (int i = 1; i < m; ++i) {
    dp[i][0] = dp[i - 1][0] + grid[i][0];
  }
  for (int j = 1; j < n; ++j) {
    dp[0][j] = dp[0][j - 1] + grid[0][j];
  }

  for (int i = 1; i < m; ++i) {
    for (int j = 1; j < n; ++j) {
      dp[i][j] = fmin(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
    }
  }

  return dp[m - 1][n - 1];
}

class Solution {
 public:
  int minPathSum(vector<vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();
    vector<vector<int>> dp(m, vector<int>(n, 0));
    dp[0][0] = grid[0][0];
    for (int i = 1; i < m; ++i) {
      dp[i][0] = dp[i - 1][0] + grid[i][0];
    }
    for (int j = 1; j < n; ++j) {
      dp[0][j] = dp[0][j - 1] + grid[0][j];
    }

    for (int i = 1; i < m; ++i) {
      for (int j = 1; j < n; ++j) {
        dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
      }
    }

    return dp[m - 1][n - 1];
  }
};

// 剑指Offer47礼物的最大价值
// 在一个m*n的棋盘的每一格都放有一个礼物，
// 每个礼物都有一定的价值（价值大于0）。
// 你可以从棋盘的左上角开始拿格子里的礼物，
// 并每次向右或者向下移动一格、直到到达棋盘的右下角。
// 给定一个棋盘及其上面的礼物的价值，
// 请计算你最多能拿到多少价值的礼物？
class Solution {
 public:
  int maxValue(vector<vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();
    vector<vector<int>> dp(m, vector<int>(n, 0));
    dp[0][0] = grid[0][0];
    for (int i = 1; i < m; ++i) {
      dp[i][0] = dp[i - 1][0] + grid[i][0];
    }
    for (int j = 1; j < n; ++j) {
      dp[0][j] = dp[0][j - 1] + grid[0][j];
    }

    for (int i = 1; i < m; ++i) {
      for (int j = 1; j < n; ++j) {
        // 与最小路径和恰恰相反，只要把下面的min换成max就可以了
        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
      }
    }

    return dp[m - 1][n - 1];
  }
};
