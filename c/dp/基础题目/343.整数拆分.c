/*
给定一个正整数n，将其拆分为k个正整数的和（k >= 2），并使这些整数的乘积最大化。
返回你可以获得的最大乘积。

示例1:
输入: n = 2
输出: 1
解释: 2 = 1 + 1, 1 × 1 = 1。

示例2:
输入: n = 10
输出: 36
解释: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36。

提示:2 <= n <= 58
*/

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

int integerBreak(int n) {
  // dp[i]：分拆数字i，可以得到的最⼤乘积为dp[i]。
  int dp[n + 1];
  memset(dp, 0, sizeof(dp));
  dp[2] = 1;
  for (int i = 3; i <= n; i++) {
    for (int j = 1; j < i - 1; j++) {
      // 其实可以从1遍历j，然后有两种渠道得到dp[i].
      // ⼀个是j*(i-j)直接相乘。
      // ⼀个是j*dp[i-j]，相当于是拆分(i-j)。
      dp[i] = fmax(dp[i], fmax((i - j) * j, dp[i - j] * j));
    }
  }
  return dp[n];
}

// 贪心
int integerBreak(int n) {
  if (n == 2) return 1;
  if (n == 3) return 2;
  if (n == 4) return 4;
  int result = 1;
  while (n > 4) {
    result *= 3;
    n -= 3;
  }
  result *= n;
  return result;
}
