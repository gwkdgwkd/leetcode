/*
硬币。给定数量不限的硬币，币值为25分、10分、5分和1分，编写代码计算n分有几种表示法。
结果可能会很大，你需要将结果模上1000000007

示例1:
输入: n = 5
输出：2
解释:有两种方式可以凑成总金额:
5=5
5=1+1+1+1+1

示例2:
输入: n = 10
输出：4
解释:有四种方式可以凑成总金额:
10=10
10=5+5
10=5+1+1+1+1+1
10=1+1+1+1+1+1+1+1+1+1

说明：你可以假设：0 <= n (总金额) <= 1000000
*/

int waysToChange(int n) {
  int coinSize = 4;
  int coins[4] = {1, 5, 10, 25};
  int dp[coinSize + 1][n + 1];
  memset(dp, 0, sizeof(dp));
  for (int i = 0; i <= coinSize; ++i) {
    dp[i][0] = 1;
  }

  for (int i = 1; i <= coinSize; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (j < coins[i - 1]) {
        dp[i][j] = dp[i - 1][j];
      } else {
        dp[i][j] = (dp[i - 1][j] + dp[i][j - coins[i - 1]]) % 1000000007;
      }
    }
  }

  return dp[coinSize][n];
}

int waysToChange(int n) {
  int coins[4] = {1, 5, 10, 25};
  int *dp = (int *)calloc(n + 1, sizeof(int));
  dp[0] = 1;

  for (int i = 0; i < 4; i++) {
    for (int j = coins[i]; j <= n; j++) {
      dp[j] = (dp[j] + dp[j - coins[i]]) % 1000000007;
    }
  }

  return dp[n];
}

class Solution {
 public:
  int waysToChange(int n) {
    vector<int> coins{1, 5, 10, 25};
    vector<int> dp(n + 1, 0);
    dp[0] = 1;

    for (int i = 0; i < coins.size(); ++i) {
      for (int j = coins[i]; j <= n; ++j) {
        dp[j] = (dp[j] + dp[j - coins[i]]) % 1000000007;
      }
    }

    return dp[n];
  }
};