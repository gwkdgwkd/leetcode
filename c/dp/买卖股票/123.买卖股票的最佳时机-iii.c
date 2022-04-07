/*
给定一个数组，它的第i个元素是一支给定的股票在第i天的价格。
设计一个算法来计算你所能获取的最大利润。你最多可以完成两笔交易。
注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

示例1:
输入：prices = [3,3,5,0,0,3,1,4]
输出：6
解释：在第4天（股票价格=0）的时候买入，在第6天（股票价格=3）的时候卖出，
     这笔交易所能获得利润=3-0=3。
     随后，在第7天（股票价格=1）的时候买入，在第8天（股票价格=4）的时候卖出，
     这笔交易所能获得利润=4-1=3。

示例2：
输入：prices = [1,2,3,4,5]
输出：4
解释：在第1天（股票价格=1）的时候买入，在第5天（股票价格=5）的时候卖出,
     这笔交易所能获得利润=5-1=4。
     注意你不能在第1天和第2天接连购买股票，之后再将它们卖出。
     因为这样属于同时参与了多笔交易，你必须在再次购买前出售掉之前的股票。

示例 3：

输入：prices = [7,6,4,3,1]
输出：0
解释：在这个情况下, 没有交易完成, 所以最大利润为 0。

示例4：
输入：prices = [1]
输出：0

提示：
1 <= prices.length <= 105
0 <= prices[i] <= 105
*/

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
  // 1.确定dp数组以及下标的含义，⼀天⼀共就有五个状态，
  //   0.没有操作
  //   1.第⼀次买⼊
  //   2.第⼀次卖出
  //   3.第⼆次买⼊
  //   4.第⼆次卖出
  // dp[i][j]中i表示第i天，j为[0-4]五个状态，dp[i][j]表示第i天状态j所剩最⼤现⾦。
  // dp[i][1]，表示的是第i天，买⼊股票的状态，并不是说⼀定要第i天买⼊股票，这是容易陷⼊的误区。
  int dp[pricesSize][5];
  // 3.dp数组如何初始化
  memset(dp, 0, sizeof(dp));
  dp[0][1] = -prices[0];
  dp[0][3] = -prices[0];

  // 4.确定遍历顺序，⼀定是从前向后遍历，因为dp[i]，依靠dp[i-1]的数值。
  for (int i = 1; i < pricesSize; ++i) {
    // 2.确定递推公式
    dp[i][0] = dp[i - 1][0];
    dp[i][1] = fmax(dp[i - 1][1], dp[i - 1][0] - prices[i]);
    dp[i][2] = fmax(dp[i - 1][2], dp[i - 1][1] + prices[i]);
    dp[i][3] = fmax(dp[i - 1][3], dp[i - 1][2] - prices[i]);
    dp[i][4] = fmax(dp[i - 1][4], dp[i - 1][3] + prices[i]);
  }

  // 5.举例推导dp数组

  return dp[pricesSize - 1][4];
}
