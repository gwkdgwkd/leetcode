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

int maxProfit(int* prices, int pricesSize) {
  // 1. 确定dp数组以及下标的含义，⼀天⼀共就有五个状态，
  //    0. 没有操作
  //    1. 第⼀次买⼊
  //    2. 第⼀次卖出
  //    3. 第⼆次买⼊
  //    4. 第⼆次卖出
  // dp[i][j]中i表示第i天，j为[0-4]五个状态，dp[i][j]表示第i天状态j所剩最⼤现⾦。
  // dp[i][1]，表示的是第i天，买⼊股票的状态，并不是说⼀定要第i天买⼊股票，这是容易陷⼊的误区。
  int dp[pricesSize][5];
  // 3. dp数组如何初始化
  memset(dp, 0, sizeof(dp));
  dp[0][1] = -prices[0];
  dp[0][3] = -prices[0];

  // 4. 确定遍历顺序，⼀定是从前向后遍历，因为dp[i]，依靠dp[i-1]的数值。
  for (int i = 1; i < pricesSize; ++i) {
    // 2. 确定递推公式
    dp[i][0] = dp[i - 1][0];
    dp[i][1] = fmax(dp[i - 1][1], dp[i - 1][0] - prices[i]);
    dp[i][2] = fmax(dp[i - 1][2], dp[i - 1][1] + prices[i]);
    dp[i][3] = fmax(dp[i - 1][3], dp[i - 1][2] - prices[i]);
    dp[i][4] = fmax(dp[i - 1][4], dp[i - 1][3] + prices[i]);
  }

  // 5. 举例推导dp数组

  return dp[pricesSize - 1][4];
}
// @lc code=end
