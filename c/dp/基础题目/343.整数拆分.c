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
  if (n < 2) {
    return 0;
  }

  // dp[i]表示将正整数i拆分成至少两个正整数的和之后，这些正整数的最大乘积
  // 0不是正整数，1是最小的正整数，0和1都不能拆分，因此dp[0]=dp[1]=0
  int dp[n + 1];
  memset(dp, 0, sizeof(dp));

  for (int i = 2; i <= n; ++i) {
    for (int j = 1; j < i; ++j) {
      // 有两种渠道得到dp[i]，把i分成j和i-j：
      //  dp[i - j] * j : i - j继续拆分
      //  (i - j) * j : i - j不继续拆分
      dp[i] = fmax(dp[i], fmax(dp[i - j] * j, (i - j) * j));
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
