/*
假设把某股票的价格按照时间先后顺序存储在数组中，请问买卖该股票一次可能获得的最大利润是多少？

示例1:
输入: [7,1,5,3,6,4]
输出: 5
解释: 在第2天（股票价格 = 1）的时候买入，
     在第5天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5。
     注意利润不能是 7-1 = 6, 因为卖出价格需要大于买入价格。

示例2:
输入: [7,6,4,3,1]
输出: 0
解释: 在这种情况下, 没有交易完成, 所以最大利润为0。

限制：0 <= 数组长度 <= 10^5

注意：本题与121题相同
*/

int maxProfit(int* prices, int pricesSize) {
  if (pricesSize == 0) {
    return 0;
  }
  int dp[pricesSize][2];
  dp[0][0] = 0;
  dp[0][1] = -prices[0];
  for (int i = 1; i < pricesSize; ++i) {
    dp[i][0] = fmax(dp[i - 1][0], dp[i - 1][1] + prices[i]);
    dp[i][1] = fmax(dp[i - 1][1], -prices[i]);
  }

  return dp[pricesSize - 1][0];
}