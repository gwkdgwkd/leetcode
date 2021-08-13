/*
 * @lc app=leetcode.cn id=121 lang=c
 *
 * [121] 买卖股票的最佳时机
 */

// @lc code=start

/* 
// 暴力法，超时
int maxProfit(int* prices, int pricesSize) {
  int max = 0;
  for (int i = 0; i < pricesSize - 1; ++i) {
    for (int j = i + 1; j < pricesSize; ++j) {
      int tmp = prices[j] - prices[i];
      max = fmax(tmp, max);
    }
  }

  return max;
}
*/

/* 
// 一次遍历，比动态规划快
int maxProfit(int* prices, int pricesSize) {
  if (pricesSize == 0) {
    return 0;
  }

  int minprice = prices[0];
  int maxprofit = 0;

  for (int i = 0; i < pricesSize; ++i) {
    if (prices[i] < minprice) {
      minprice = prices[i];
    } else if (prices[i] - minprice > maxprofit) {
      maxprofit = prices[i] - minprice;
    }
  }
  return maxprofit;
}
*/

// 动态规划，方法通用，还有5个股票问题
int maxProfit(int* prices, int pricesSize) {
  int dp[pricesSize][2];
  dp[0][0] = 0;           // 第一天没买股票，收益为0
  dp[0][1] = -prices[0];  // 第一天买了股票，收益为负的当天价格
  for (int i = 1; i < pricesSize; i++) {
    // 第i天，没有股票的收益：前一天没有股票的收益和前一天卖掉股票的收益最大值
    dp[i][0] = fmax(dp[i - 1][0], dp[i - 1][1] + prices[i]);
    // 第i天，有股票的收益：前一天有股票的收益和当天买入股票收益的最大值
    dp[i][1] = fmax(dp[i - 1][1], -prices[i]);
  }

  // for (int i = 0; i < 2; ++i) {
  //   for (int j = 0; j < pricesSize; ++j) {
  //     printf("%3d ", dp[j][i]);
  //   }
  //   printf("\n");
  // }

  // [7,1,5,3,6,4]
  //   0   0   4   4   5   5
  //  -7  -1  -1  -1  -1  -1

  return dp[pricesSize - 1][0];
}

// @lc code=end
