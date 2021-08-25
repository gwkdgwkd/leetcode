/*
 * @lc app=leetcode.cn id=518 lang=c
 *
 * [518] 零钱兑换 II
 */

// @lc code=start

#include <stdio.h>
#include <string.h>

// 组合不强调元素之间的顺序，排列强调元素之间的顺序。
// 在求装满背包有⼏种⽅案的时候，认清遍历顺序是⾮常关键的：
//  如果求组合数就是外层for循环遍历物品，内层for遍历背包。
//  如果求排列数就是外层for遍历背包，内层for循环遍历物品。

// 动态规划、完全背包、装满背包有几种方法
int change1(int amount, int* coins, int coinsSize) {
  int dp[coinsSize + 1][amount + 1];
  memset(dp, 0, sizeof(dp));
  for (int i = 0; i <= coinsSize; ++i) {
    dp[i][0] = 1;  // 如果要凑出的目标金额为0，那只有一种方法，什么面值都不选
  }
  // for (int i = 1; i <= amount; ++i) {
  //   dp[0][i] = 0;  // 不使用任何面值，就无法凑出任何金额
  // }

  for (int i = 1; i <= coinsSize; ++i) {
    for (int j = 0; j <= amount; ++j) {
      if (j < coins[i - 1]) {
        // 如果目标值j比当前面值小，那么当前面值不能放入，所以选择不包括当前值的所有方法
        dp[i][j] = dp[i - 1][j];
      } else {
        // 如果目标值j比当前面值大，那么等于不放当前面值的个数+除去当前面值后使用当前面值的个数
        dp[i][j] = dp[i - 1][j] + dp[i][j - coins[i - 1]];
      }
    }
  }

  // for (int i = 0; i <= coinsSize; ++i) {
  //   for (int j = 0; j <= amount; ++j) {
  //     printf("%3d ", dp[i][j]);
  //   }
  //   printf("\n");
  // }
  // 5 [1,2,5]
  // 1   0   0   0   0   0
  // 1   1   1   1   1   1
  // 1   1   2   2   3   3
  // 1   1   2   2   3   4

  return dp[coinsSize][amount];
}

int change2(int amount, int* coins, int coinsSize) {
  // 时间复杂度：O(amount*n)
  // 空间复杂度：O(amount)

  int dp[amount + 1];
  memset(dp, 0, sizeof(dp));
  dp[0] = 1;

  // 这种遍历顺序中dp[j]⾥计算的是组合数！
  for (int i = 0; i < coinsSize; ++i) {
    for (int j = coins[i]; j <= amount; ++j) {
      dp[j] += dp[j - coins[i]];
    }
    // for (int j = 0; j <= amount; ++j) {
    //   printf("%d ", dp[j]);
    // }
    // printf("\n");
  }

  // 1 1 1 1 1 1
  // 1 1 2 2 3 3
  // 1 1 2 2 3 4

  return dp[amount];
}

int change3(int amount, int* coins, int coinsSize) {
  // 时间复杂度：O(amount*n)
  // 空间复杂度：O(amount)

  int dp[amount + 1];
  memset(dp, 0, sizeof(dp));
  dp[0] = 1;

  // 如果把两个for交换顺序，此时dp[j]⾥算出来的就是排列数！
  for (int j = 0; j <= amount; ++j) {
    for (int i = 0; i < coinsSize; ++i) {
      // printf("%d %d: ", j, coins[i]);
      if (j >= coins[i]) {
        // printf("%d(dp[%d])+%d(dp[%d])=", dp[j], j, dp[j - coins[i]], j - coins[i]);
        dp[j] += dp[j - coins[i]];
      }
      // printf("%d\n", dp[j]);
    }
  }

  // 0 1: 1
  // 0 2: 1
  // 0 5: 1
  // 1 1: 0(dp[1])+1(dp[0])=1
  // 1 2: 1
  // 1 5: 1
  // 2 1: 0(dp[2])+1(dp[1])=1
  // 2 2: 1(dp[2])+1(dp[0])=2
  // 2 5: 2
  // 3 1: 0(dp[3])+2(dp[2])=2
  // 3 2: 2(dp[3])+1(dp[1])=3
  // 3 5: 3
  // 4 1: 0(dp[4])+3(dp[3])=3
  // 4 2: 3(dp[4])+2(dp[2])=5
  // 4 5: 5
  // 5 1: 0(dp[5])+5(dp[4])=5
  // 5 2: 5(dp[5])+3(dp[3])=8
  // 5 5: 8(dp[5])+1(dp[0])=9

  return dp[amount];
}

int main() {
  int coins[3] = {1, 2, 5};
  printf("%d\n", change1(5, coins, sizeof(coins) / sizeof(int)));  // 4
  printf("%d\n", change2(5, coins, sizeof(coins) / sizeof(int)));  // 4
  printf("%d\n", change3(5, coins, sizeof(coins) / sizeof(int)));  // 9

  return 0;
}

// @lc code=end
