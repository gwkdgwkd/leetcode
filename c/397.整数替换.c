/*
 * @lc app=leetcode.cn id=397 lang=c
 *
 * [397] 整数替换
 */

// @lc code=start

// 动态规划，超时
int integerReplacement(int n) {
  int dp[n + 1];
  memset(dp, 0, sizeof(dp));
  dp[0] = dp[1] = 0;
  for (int i = 2; i <= n; ++i) {
    if (i % 2) {
      // dp[i] = fmin(dp[(i + 1)/2], dp[(i - 1)/2]) + 2;
      dp[i] = fmin(dp[(i + 1) >> 1], dp[(i - 1) >> 1]) + 2;
    } else {
      // dp[i] = dp[i/2] + 1;
      dp[i] = dp[i >> 1] + 1;
    }
  }

  return dp[n];
}

// @lc code=end
