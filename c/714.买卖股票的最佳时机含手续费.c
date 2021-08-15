/*
 * @lc app=leetcode.cn id=714 lang=c
 *
 * [714] 买卖股票的最佳时机含手续费
 */

// @lc code=start

// 动态规划
int maxProfit(int* prices, int pricesSize, int fee) {
  if (pricesSize < 2) {
    return 0;
  }

  int dp[pricesSize][2];
  dp[0][0] = 0;
  dp[0][1] = -prices[0];
  for (int i = 1; i < pricesSize; ++i) {
    dp[i][0] = fmax(dp[i - 1][0], dp[i - 1][1] + prices[i] - fee);
    dp[i][1] = fmax(dp[i - 1][1], dp[i - 1][0] - prices[i]);
  }

  return dp[pricesSize - 1][0];
}

/*
// 官方题解
int maxProfit(int* prices, int pricesSize, int fee) {
  int sell = 0, buy = -prices[0];
  for (int i = 1; i < pricesSize; ++i) {
    sell = fmax(sell, buy + prices[i] - fee);
    buy = fmax(buy, sell - prices[i]);
  }
  return sell;
}
*/

// @lc code=end
