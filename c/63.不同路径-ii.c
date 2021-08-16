/*
 * @lc app=leetcode.cn id=63 lang=c
 *
 * [63] 不同路径 II
 */

// @lc code=start

/*
// 动态规划
int uniquePathsWithObstacles(int** obstacleGrid, int obstacleGridSize,
                             int* obstacleGridColSize) {
  if (obstacleGrid[0][0]) {
    return 0;
  }
  int m = obstacleGridSize;
  int n = *obstacleGridColSize;
  int dp[m][n];
  memset(dp, 0, sizeof(dp));
  for (int i = 0; i < m; ++i) {
    if (obstacleGrid[i][0] == 1) {
      break;
    }
    dp[i][0] = 1;
  }
  for (int i = 1; i < n; ++i) {
    if (obstacleGrid[0][i] == 1) {
      break;
    }
    dp[0][i] = 1;
  }

  for (int i = 1; i < m; ++i) {
    for (int j = 1; j < n; ++j) {
      if (obstacleGrid[i][j] == 1) {
        dp[i][j] = 0;
      } else {
        dp[i][j] = dp[i][j - 1] + dp[i - 1][j];
      }
    }
  }

  return dp[m - 1][n - 1];
}
*/

// 官方题解
int uniquePathsWithObstacles(int** obstacleGrid, int obstacleGridSize,
                             int* obstacleGridColSize) {
  int n = obstacleGridSize, m = obstacleGridColSize[0];
  int f[m];
  memset(f, 0, sizeof(f));
  f[0] = (obstacleGrid[0][0] == 0);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (obstacleGrid[i][j] == 1) {
        f[j] = 0;
        continue;
      }
      if (j - 1 >= 0 && obstacleGrid[i][j - 1] == 0) {
        f[j] += f[j - 1];
      }
    }
  }

  return f[m - 1];
}
// @lc code=end
