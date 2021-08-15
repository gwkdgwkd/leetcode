/*
 * @lc app=leetcode.cn id=123 lang=c
 *
 * [123] 买卖股票的最佳时机 III
 */

// @lc code=start

/*
// 官方题解
int maxProfit(int* prices, int pricesSize) {
  int buy1 = -prices[0], sell1 = 0;
  int buy2 = -prices[0], sell2 = 0;
  for (int i = 1; i < pricesSize; ++i) {
    buy1 = fmax(buy1, -prices[i]);
    sell1 = fmax(sell1, buy1 + prices[i]);
    buy2 = fmax(buy2, sell1 - prices[i]);
    sell2 = fmax(sell2, buy2 + prices[i]);
  }
  return sell2;
}
*/

/*
// 动态规划
int maxProfit(int* prices, int pricesSize) {
  // dp[i][k][0-1]表示第i天第k次没有股票或有股票时的最大收益
  int dp[pricesSize][2][2];
  dp[0][0][0] = 0;
  dp[0][0][1] = -prices[0];
  dp[0][1][0] = 0;
  dp[0][1][1] = -prices[0];
  for (int i = 1; i < pricesSize; i++) {
    dp[i][1][0] = fmax(dp[i - 1][1][0], dp[i - 1][1][1] + prices[i]);
    dp[i][1][1] = fmax(dp[i - 1][1][1], dp[i - 1][0][0] - prices[i]);
    dp[i][0][0] = fmax(dp[i - 1][0][0], dp[i - 1][0][1] + prices[i]);
    dp[i][0][1] = fmax(dp[i - 1][0][1], -prices[i]);
  }

  return dp[pricesSize - 1][1][0];
}
*/

// 动态规划，股票问题公式
int maxProfit(int* prices, int pricesSize) {
  if (pricesSize <= 0) {
    return 0;
  }

  int k = 2;
  int dp[pricesSize][k][2];
  for (int i = 0; i < k; ++i) {
    dp[0][i][0] = 0;
    dp[0][i][1] = -prices[0];
  }
  for (int i = 1; i < pricesSize; ++i) {
    for (int j = 0; j < k; ++j) {
      dp[i][j][0] = fmax(dp[i - 1][j][0], dp[i - 1][j][1] + prices[i]);
      if (0 == j) {
        dp[i][j][1] = fmax(dp[i - 1][j][1], -prices[i]);
      } else {
        dp[i][j][1] = fmax(dp[i - 1][j][1], dp[i - 1][j - 1][0] - prices[i]);
      }
    }
  }

  return dp[pricesSize - 1][k - 1][0];
}

// @lc code=end
