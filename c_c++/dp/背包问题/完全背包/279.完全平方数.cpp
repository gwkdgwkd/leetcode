/*
给一个整数n，返回和为n的完全平方数的最少数量，完全平方数是一个整数，
其值等于另一个整数的平方，换句话说，其值等于一个整数自乘的积。
例如1、4、9和16都是完全平方数，而3和11不是。

示例1：
输入：n = 12
输出：3
解释：12 = 4 + 4 + 4

示例2：
输入：n = 13
输出：2
解释：13 = 4 + 9

提示：1 <= n <= 10^4
*/

// 动态规划，可以看成背包问题
int numSquares(int n) {
  int dp[n + 1];
  memset(dp, 0, sizeof(dp));

  dp[0] = 0;
  for (int i = 1; i <= n; ++i) {
    int min = INT_MAX;
    for (int j = 1; j * j <= i; ++j) {
      min = fmin(min, dp[i - j * j]);
    }
    dp[i] = min + 1;
  }

  return dp[n];
}

// 完全背包
int numSquares(int n) {
  int dp[n + 1];
  dp[0] = 0;
  for (int i = 1; i <= n; ++i) {
    dp[i] = INT_MAX;
  }

  for (int i = 0; i <= n; ++i) {
    for (int j = 1; j * j <= i; ++j) {
      dp[i] = fmin(dp[i], dp[i - j * j] + 1);
    }
  }

  return dp[n];
}

class Solution {
 public:
  int numSquares(int n) {
    vector<int> dp(n + 1, INT_MAX);
    dp[0] = 0;

    for (int i = 0; i <= n; ++i) {
      for (int j = 1; j * j <= i; ++j) {
        dp[i] = min(dp[i], dp[i - j * j] + 1);
      }
    }

    return dp[n];
  }
};