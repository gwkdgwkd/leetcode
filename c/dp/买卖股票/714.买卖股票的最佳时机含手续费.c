/*
给定一个整数数组prices，其中prices[i]表示第i天的股票价格；整数fee代表了交易股票的手续费用。
你可以无限次地完成交易，但是你每笔交易都需要付手续费。
如果你已经购买了一个股票，在卖出它之前你就不能再继续购买股票了。
返回获得利润的最大值。
注意：这里的一笔交易指买入持有并卖出股票的整个过程，每笔交易你只需要为支付一次手续费。

示例1：
输入：prices = [1, 3, 2, 8, 4, 9], fee = 2
输出：8
解释：能够达到的最大利润:
在此处买入 prices[0] = 1
在此处卖出 prices[3] = 8
在此处买入 prices[4] = 4
在此处卖出 prices[5] = 9
总利润: ((8 - 1) - 2) + ((9 - 4) - 2) = 8

示例2：
输入：prices = [1,3,7,5,10,3], fee = 3
输出：6

提示：
1 <= prices.length <= 5 * 104
1 <= prices[i] < 5 * 104
0 <= fee < 5 * 104
*/

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

// 官方题解
int maxProfit(int* prices, int pricesSize, int fee) {
  int sell = 0, buy = -prices[0];
  for (int i = 1; i < pricesSize; ++i) {
    sell = fmax(sell, buy + prices[i] - fee);
    buy = fmax(buy, sell - prices[i]);
  }
  return sell;
}

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
      // 情况一：收获利润的这一天并不是收获利润区间里的最后一天（不是真正的卖出，相当于持有股票），
      // 所以后面要继续收获利润。
      result += prices[i] - minPrice - fee;
      minPrice = prices[i] - fee;  // 情况一，这一步很关键
    }
  }
  return result;
}
