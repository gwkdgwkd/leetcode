/*
 * @lc app=leetcode.cn id=62 lang=c
 *
 * [62] 不同路径
 */

// @lc code=start

/*
// 组合计算
// 从左上角到右下角的过程中，我们需要移动m+n−2次，其中有m−1次向下移动，n−1次向右移动。因此路径的总数，就等于从m+n−2次移动中选择m−1次向下移动的方案数，即组合数。
int uniquePaths(int m, int n) {
  long long ans = 1;
  for (int x = n, y = 1; y < m; ++x, ++y) {
    ans = ans * x / y;
  }
  return ans;
}
*/

// 动态规划
int uniquePaths(int m, int n) {
  int dp[m][n];
  for (int i = 0; i < m; ++i) {
    dp[i][0] = 1;
  }
  for (int i = 1; i < n; ++i) {
    dp[0][i] = 1;
  }

  for (int i = 1; i < m; ++i) {
    for (int j = 1; j < n; ++j) {
      dp[i][j] = dp[i][j - 1] + dp[i - 1][j];
    }
  }

  return dp[m - 1][n - 1];
}

// @lc code=end
