/*
给定一个数组prices，它的第i个元素prices[i]表示一支给定股票第i天的价格。
你只能选择某一天买入这只股票，并选择在未来的某一个不同的日子卖出该股票。
设计一个算法来计算你所能获取的最大利润。
返回你可以从这笔交易中获取的最大利润。如果你不能获取任何利润，返回0。

示例1：
输入：[7,1,5,3,6,4]
输出：5
解释：在第2天（股票价格=1）的时候买入，在第5天（股票价格=6）的时候卖出，最大利润=6-1=5。
     注意利润不能是7-1=6,因为卖出价格需要大于买入价格；同时，你不能在买入前卖出股票。

示例2：
输入：prices = [7,6,4,3,1]
输出：0
解释：在这种情况下, 没有交易完成, 所以最大利润为0。

提示：
1 <= prices.length <= 10^5
0 <= prices[i] <= 10^4
*/

// 剑指Offer63股票的最大利润

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

// 动态规划，方法通用，还有5个股票问题
int maxProfit(int* prices, int pricesSize) {
  int dp[pricesSize][2];
  dp[0][0] = 0;           // 第一天没买股票，收益为0
  dp[0][1] = -prices[0];  // 第一天买了股票，收益为负的当天价格
  for (int i = 1; i < pricesSize; i++) {
    // 第i天，没有股票的收益：前一天没有股票的收益和前一天有股票今天卖掉的收益最大值
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

// 动态规划公式
int maxProfit(int* prices, int pricesSize) {
  if (pricesSize <= 0) {
    return 0;
  }

  int k = 1;
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

class Solution {
 public:
  int maxProfit(vector<int>& prices) {
    int n = prices.size();
    vector<vector<int>> dp(n, vector<int>(2));
    dp[0][0] = 0;
    dp[0][1] = -prices[0];

    for (int i = 1; i < n; ++i) {
      dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
      dp[i][1] = max(dp[i - 1][1], -prices[i]);
    }

    return dp[n - 1][0];
  }
};
