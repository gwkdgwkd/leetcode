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

// 贪心算法
// 时间复杂度：O(n)
// 空间复杂度：O(1)
int maxProfit(int* prices, int pricesSize, int fee) {
  int result = 0;
  int minPrice = prices[0];  // 记录最低价格
  for (int i = 1; i < pricesSize; i++) {
    // 情况二：前一天是收获利润区间里的最后一天（相当于真正的卖出了），今天要重新记录最小价格了。
    if (prices[i] < minPrice) minPrice = prices[i];

    // 情况三：不作操作，保持原有状态（买入，卖出，不买不卖，因为此时买则不便宜，卖则亏本）
    if (prices[i] >= minPrice && prices[i] <= minPrice + fee) {
      continue;
    }

    // 计算利润，可能有多次计算利润，最后一次计算利润才是真正意义的卖出
    if (prices[i] > minPrice + fee) {
      // 情况一：收获利润的这一天并不是收获利润区间里的最后一天（不是真正的卖出，相当于持有股票），所以后面要继续收获利润。
      result += prices[i] - minPrice - fee;
      minPrice = prices[i] - fee;  // 情况一，这一步很关键
    }
  }
  return result;
}

// @lc code=end
