/*
 * @lc app=leetcode.cn id=518 lang=c
 *
 * [518] 零钱兑换 II
 */

// @lc code=start

#include <stdio.h>

/*
int change(int amount, int* coins, int coinsSize) {
  // dp[i][j]表示：若只使用前i个物品，当背包容量为j时，有dp[i][j]种方法可以装满背包
  int dp[coinsSize + 1][amount + 1];
  for (int i = 1; i < amount + 1; ++i) {
    // 不使用任何面值，就无法凑出任何金额
    dp[0][i] = 0;
  }
  for (int i = 0; i < coinsSize + 1; ++i) {
    // 如果要凑出的目标金额为0，那只有一种方法，什么面值都不选
    dp[i][0] = 1;
  }

  for (int i = 1; i <= coinsSize; ++i) {
    for (int j = 1; j <= amount; ++j) {
      if (j < coins[i - 1]) {
        // 如果目标值j比当前面值小，那么当前面值不能放入，所以选择不包括当前值的所有方法
        dp[i][j] = dp[i - 1][j];
      } else {
        // 如果目标值j比当前面值大，那么等于不放当前面值的个数+除去当前面值后使用当前面值的个数
        dp[i][j] = dp[i - 1][j] + dp[i][j - coins[i - 1]];
      }
    }
  }

  return dp[coinsSize][amount];
}
*/

// 压缩dp
int change(int amount, int* coins, int coinsSize) {
  int dp[amount + 1];
  for (int i = 1; i < amount + 1; ++i) {
    dp[i] = 0;
  }
  dp[0] = 1;

  for (int i = 0; i < coinsSize; ++i) {
    for (int j = 1; j <= amount; ++j) {
      if (j >= coins[i]) {
        dp[j] = dp[j] + dp[j - coins[i]];
      }
    }
  }

  return dp[amount];
}

// 时间复杂度：O(amount*n)
// 空间复杂度：O(amount)

int main() {
  int coins[3] = {1, 2, 5};
  int count = change(5, coins, sizeof(coins) / sizeof(int));
  printf("%d\n", count);
  return 0;
}

// @lc code=end
