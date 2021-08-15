/*
 * @lc app=leetcode.cn id=188 lang=c
 *
 * [188] 买卖股票的最佳时机 IV
 */

// @lc code=start

// 动态规划公式
int maxProfit(int k, int* prices, int pricesSize) {
  if (pricesSize <= 1 || k <= 0) {
    return 0;
  }

  k = fmin(k, pricesSize / 2);

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

/*
// 官方题解
int maxProfit(int k, int* prices, int pricesSize) {
  int n = pricesSize;
  if (n == 0) {
    return 0;
  }

  k = fmin(k, n / 2);
  int buy[n][k + 1], sell[n][k + 1];
  memset(buy, 0, sizeof(buy));
  memset(sell, 0, sizeof(sell));

  buy[0][0] = -prices[0];
  sell[0][0] = 0;
  for (int i = 1; i <= k; ++i) {
    buy[0][i] = sell[0][i] = INT_MIN / 2;
  }

  for (int i = 1; i < n; ++i) {
    buy[i][0] = fmax(buy[i - 1][0], sell[i - 1][0] - prices[i]);
    for (int j = 1; j <= k; ++j) {
      buy[i][j] = fmax(buy[i - 1][j], sell[i - 1][j] - prices[i]);
      sell[i][j] = fmax(sell[i - 1][j], buy[i - 1][j - 1] + prices[i]);
    }
  }
  int ret = 0;
  for (int i = 0; i <= k; i++) {
    ret = fmax(ret, sell[n - 1][i]);
  }

  return ret;
}
*/

// @lc code=end
