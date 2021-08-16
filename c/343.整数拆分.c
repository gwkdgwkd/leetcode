/*
 * @lc app=leetcode.cn id=343 lang=c
 *
 * [343] 整数拆分
 */

// @lc code=start

// 动态规划
int integerBreak(int n) {
  if (n < 1) {
    return 0;
  }
  if (n == 2) {
    return 1;
  }
  int dp[n + 1];
  memset(dp, 0, sizeof(dp));
  for (int i = 2; i <= n; ++i) {
    int max = 0;
    for (int j = 1; j < i; ++j) {
      // dp[i - j] * j : i - j继续拆分
      // (i - j) * j : i - j不继续拆分
      max = fmax(max, fmax(dp[i - j] * j, (i - j) * j));
      dp[i] = max;
    }
  }

  return dp[n];
}
// @lc code=end
