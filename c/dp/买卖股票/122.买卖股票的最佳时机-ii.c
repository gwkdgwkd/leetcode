/*
 * @lc app=leetcode.cn id=122 lang=c
 *
 * [122] 买卖股票的最佳时机 II
 */

// @lc code=start

// 动态规划
int maxProfit(int* prices, int pricesSize) {
  int dp[pricesSize][2];
  dp[0][0] = 0;
  dp[0][1] = -prices[0];
  for (int i = 1; i < pricesSize; i++) {
    dp[i][0] = fmax(dp[i - 1][0], dp[i - 1][1] + prices[i]);
    // 只有下面的语句与121不同
    dp[i][1] = fmax(dp[i - 1][1], dp[i - 1][0] - prices[i]);
  }

  // for (int i = 0; i < 2; ++i) {
  //   for (int j = 0; j < pricesSize; ++j) {
  //     printf("%3d ", dp[j][i]);
  //   }
  //   printf("\n");
  // }

  // [7,1,5,3,6,4]
  //   0   0   4   4   7   7
  //  -7  -1  -1   1   1   3

  return dp[pricesSize - 1][0];
}

/* 
// 动态规划，每天的状态只与前一天有关，不用dp
int maxProfit(int* prices, int pricesSize) {
  int pre0 = 0;
  int pre1 = -prices[0];
  for (int i = 1; i < pricesSize; i++) {
    int cur0 = fmax(pre0, pre1 + prices[i]);
    int cur1 = fmax(pre1, pre0 - prices[i]);
    pre0 = cur0;
    pre1 = cur1;
  }

  return pre0;
}
*/

// @lc code=end
