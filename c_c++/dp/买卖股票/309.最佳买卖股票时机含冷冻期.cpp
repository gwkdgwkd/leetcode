/*
给定一个整数数组prices，其中第prices[i]表示第i天的股票价格，设计算法计算最大利润。
在满足以下约束条件下，可以尽可能地完成更多的交易（多次买卖一支股票）：
卖出股票后，无法在第二天买入股票(即冷冻期为1天)。
注意：不能同时参与多笔交易（必须在再次购买前出售掉之前的股票）。

示例1：
输入：prices = [1,2,3,0,2]
输出：3
解释：对应的交易状态为：[买入，卖出，冷冻期，买入，卖出]

示例2：
输入：prices = [1]
输出：0

提示：
1 <= prices.length <= 5000
0 <= prices[i] <= 1000
*/

int maxProfit(int* prices, int pricesSize) {
  // 1.确定dp数组以及下标的含义：
  //   dp[i][j]，第i天状态为j，所剩的最多现⾦为dp[i][j]。
  //   因为出现冷冻期之后，状态其实是⽐较复杂度，
  //   例如今天买⼊股票、今天卖出股票、今天是冷冻期，都是不能操作股票的。
  //   具体可以区分出如下四个状态：
  //   状态⼀：买⼊股票状态，今天买⼊股票，或者是之前就买⼊了股票然后没有操作；
  //   状态⼆：两天前就卖出了股票，度过了冷冻期，⼀直没操作，今天保持卖出股票状态；
  //   状态三：今天卖出了股票；
  //   状态四：今天为冷冻期状态，但冷冻期状态不可持续，只有⼀天。
  //   j的状态为：
  //    0：状态⼀
  //    1：状态⼆
  //    2：状态三
  //    3：状态四
  //   很多题解为什么讲的⽐较模糊，是因为把这四个状态合并成三个状态了，
  //   其实就是把状态⼆和状态四合并在⼀起了。
  //   从代码上来看确实可以合并，但从逻辑上分析合并之后就很难理解了。
  //   注意，例如状态⼀，是买⼊股票状态并不是说今天已经就买⼊股票，
  //   ⽽是说保存买⼊股票的状态即：
  //   可能是前⼏天买⼊的，之后⼀直没操作，所以保持买⼊股票的状态。
  int dp[pricesSize][4];
  // 3.dp数组如何初始化
  //   如果是持有股票状态（状态⼀）那么：
  //   dp[0][0]=-prices[0]，买⼊股票所省现⾦为负数。
  //   保持卖出股票状态（状态⼆），第0天没有卖出dp[0][1]初始化为0就⾏，
  //   今天卖出了股票（状态三），同样dp[0][2]初始化为0，
  //   因为最少收益就是0，绝不会是负数。
  //   同理dp[0][3]也初始为0。
  memset(dp, 0, sizeof(dp));
  dp[0][0] = -prices[0];

  // 4.确定遍历顺序：
  //   从递归公式上可以看出，dp[i]依赖于dp[i-1]，所以是从前向后遍历。
  for (int i = 1; i < pricesSize; i++) {
    // 2.确定递推公式
    //   达到买⼊股票状态（状态⼀）即：dp[i][0]，有两个具体操作：
    //   操作⼀：前⼀天就是持有股票状态（状态⼀），dp[i][0] = dp[i-1][0]
    //   操作⼆：今天买⼊了，有两种情况
    //   前⼀天是冷冻期（状态四），dp[i-1][3]-prices[i]
    //   前⼀天是保持卖出股票状态（状态⼆），dp[i-1][1]-prices[i]
    //   所以操作⼆取最⼤值，即：max(dp[i-1][3], dp[i-1][1])-prices[i]
    dp[i][0] = fmax(dp[i - 1][0], fmax(dp[i - 1][3], dp[i - 1][1]) - prices[i]);
    //   达到保持卖出股票状态（状态⼆）即：dp[i][1]，有两个具体操作：
    //   操作⼀：前⼀天就是状态⼆
    //   操作⼆：前⼀天是冷冻期（状态四）
    dp[i][1] = fmax(dp[i - 1][1], dp[i - 1][3]);
    //   达到今天就卖出股票状态（状态三），即：dp[i][2] ，只有⼀个操作：
    //   操作⼀：昨天⼀定是买⼊股票状态（状态⼀），今天卖出
    dp[i][2] = dp[i - 1][0] + prices[i];
    //   达到冷冻期状态（状态四），即：dp[i][3]，只有⼀个操作：
    //   操作⼀：昨天卖出了股票（状态三）
    dp[i][3] = dp[i - 1][2];
  }

  return fmax(dp[pricesSize - 1][3],
              fmax(dp[pricesSize - 1][1], dp[pricesSize - 1][2]));
}

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

class Solution {
 public:
  int maxProfit(vector<int>& prices) {
    int n = prices.size();
    vector<vector<int>> dp(n, vector<int>(2));

    dp[0][0] = 0;
    dp[0][1] = -prices[0];

    for (int i = 1; i < n; ++i) {
      dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
      if (i > 2) {
        dp[i][1] = max(dp[i - 1][1], dp[i - 2][0] - prices[i]);
      } else {
        dp[i][1] = max(dp[i - 1][1], -prices[i]);
      }
    }

    return dp[n - 1][0];
  }
};
