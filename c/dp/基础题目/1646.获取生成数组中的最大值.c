/*
 * @lc app=leetcode.cn id=1646 lang=c
 *
 * [1646] 获取生成数组中的最大值
 */

// @lc code=start

// 动态规划
int getMaximumGenerated(int n) {
  if (n < 2) {
    return n;
  }
  int dp[n + 1];
  dp[0] = 0;
  dp[1] = 1;
  int ret = 0;
  for (int i = 2; i <= n; ++i) {
    int t = i / 2;
    if (i % 2) {
      dp[i] = dp[t] + dp[t + 1];
    } else {
      dp[i] = dp[t];
    }
    ret = fmax(ret, dp[i]);
  }

  return ret;
}

// @lc code=end
