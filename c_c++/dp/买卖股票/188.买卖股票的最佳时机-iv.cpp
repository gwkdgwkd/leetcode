/*
给定一个整数数组prices，它的第i个元素prices[i]是一支给定的股票在第i天的价格。
设计一个算法来计算你所能获取的最大利润。你最多可以完成k笔交易。
注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

示例1：
输入：k = 2, prices = [2,4,1]
输出：2
解释：在第1天(股票价格=2) 的时候买入，在第2天 (股票价格=4)的时候卖出，
     这笔交易所能获得利润=4-2=2。

示例2：
输入：k = 2, prices = [3,2,6,5,0,3]
输出：7
解释：在第2天(股票价格=2)的时候买入，在第3天(股票价格=6)的时候卖出，
     这笔交易所能获得利润=6-2=4。
     随后，在第5天(股票价格=0)的时候买入，
     在第6天(股票价格=3)的时候卖出，这笔交易所能获得利润=3-0=3。

提示：
0 <= k <= 100
0 <= prices.length <= 1000
0 <= prices[i] <= 1000
*/

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

int maxProfit(int k, int* prices, int pricesSize) {
  if (pricesSize == 0 || k == 0) {
    return 0;
  }

  // 使⽤⼆维数组dp[i][j]：第i天的状态为j，所剩下的最⼤现⾦是dp[i][j]。
  // j的状态表示为：
  // 0表示不操作
  // 1第⼀次买⼊
  // 2第⼀次卖出
  // 3第⼆次买⼊
  // 4第⼆次卖出
  // .....
  // 除了0以外，偶数就是卖出，奇数就是买⼊。
  // ⾄多有K笔交易，那么j的范围就定义为2*k+1就可以了。
  int dp[pricesSize][2 * k + 1];
  memset(dp, 0, sizeof(dp));
  // for (int i = 0; i < 2 * k + 1; ++i) {
  //   dp[0][i] = i % 2 ? -prices[0] : 0;
  // }
  for (int j = 1; j < 2 * k; j += 2) {
    dp[0][j] = -prices[0];
  }

  for (int i = 1; i < pricesSize; ++i) {
    // dp[i][0] = dp[i - 1][0];  // 这个一直是0，初始化为0就可以了
    for (int j = 1; j < 2 * k + 1; ++j) {
      dp[i][j] =
          fmax(dp[i - 1][j], dp[i - 1][j - 1] + (j % 2 ? -1 : 1) * prices[i]);
    }
  }

  return dp[pricesSize - 1][2 * k];
}

class Solution {
 public:
  int maxProfit(int k, vector<int>& prices) {
    if (k == 0 || prices.size() == 0) {
      return 0;
    }

    int n = prices.size();
    vector<vector<int>> dp(n, vector<int>(2 * k, 0));
    for (int i = 0; i < 2 * k; ++i) {
      if (i % 2 == 0) {
        dp[0][i] = -prices[0];
      }
    }

    for (int i = 1; i < n; ++i) {
      dp[i][0] = max(dp[i - 1][0], -prices[i]);
      for (int j = 1; j < 2 * k; ++j) {
        if (j % 2 == 0) {
          dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1] - prices[i]);
        } else {
          dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1] + prices[i]);
        }
      }
    }

    return dp[n - 1][2 * k - 1];
  }
};
