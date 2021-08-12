/*
 * @lc app=leetcode.cn id=64 lang=c
 *
 * [64] 最小路径和
 */

// @lc code=start

// 动态规划
int minPathSum(int** grid, int gridSize, int* gridColSize) {
  int dp[gridSize][*gridColSize];
  dp[0][0] = grid[0][0];
  for (int i = 1; i < gridSize; ++i) {
    dp[i][0] = dp[i - 1][0] + grid[i][0];
  }
  for (int i = 1; i < *gridColSize; ++i) {
    dp[0][i] = dp[0][i - 1] + grid[0][i];
  }

  for (int i = 1; i < gridSize; ++i) {
    for (int j = 1; j < *gridColSize; ++j) {
      dp[i][j] = fmin(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
    }
  }

  return dp[gridSize - 1][*gridColSize - 1];
}

// @lc code=end
