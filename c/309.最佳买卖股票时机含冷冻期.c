/*
 * @lc app=leetcode.cn id=309 lang=c
 *
 * [309] 最佳买卖股票时机含冷冻期
 */

// @lc code=start

// 动态规划
int maxProfit(int* prices, int pricesSize) {
  if (pricesSize <= 1) {
    return 0;
  }

  int dp[pricesSize][2];
  dp[0][0] = 0;
  dp[0][1] = -prices[0];

  for (int i = 1; i < pricesSize; ++i) {
    dp[i][0] = fmax(dp[i - 1][0], dp[i - 1][1] + prices[i]);
    dp[i][1] = fmax(dp[i - 1][1], dp[i > 1 ? i - 2 : 0][0] - prices[i]);
  }

  return dp[pricesSize - 1][0];
}

// @lc code=end
