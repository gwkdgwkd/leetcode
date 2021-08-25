/*
 * @lc app=leetcode.cn id=322 lang=c
 *
 * [322] 零钱兑换
 */

// @lc code=start

/*
#include <limits.h>
 
// 暴力递归法
int coinChange(int* coins, int coinsSize, int amount) {
  if (amount < 0) {
    return -1;
  }
  if (amount == 0) {
    return 0;
  }

  int min = INT_MAX;
  for (int i = 0; i < coinsSize; ++i) {
    int tmp = coinChange(coins, coinsSize, amount - coins[i]);
    if (-1 == tmp) {
      continue;
    }
    if (min > tmp) {
      min = tmp;
    }
  }

  return min == INT_MAX ? -1 : min + 1;
}

//           0,n = 0
// dp(n) =   -1,n < 0
//           min{dp(n - coin) + 1 | coin属于coins},n > 0
// 子问题总数为递归树节点个数，是O(n^k)，是指数级别的。
// 每个子问题中含有一个for循环，复杂度为O(k)。
// 时间复杂度：O(k*n^k)，指数级别。
*/

/* 
#include <limits.h>
#include <stdlib.h>

// 带备忘录的递归
int coinChange(int *coins, int coinsSize, int amount) {
  if (amount < 0) {
    return -1;
  }
  if (amount == 0) {
    return 0;
  }

  int *backup = (int *)malloc((amount + 1) * sizeof(int));
  for (int i = 0; i < amount + 1; ++i) {
    backup[i] = -1;
  }

  return helper(coins, coinsSize, amount, backup);
}

int helper(int *coins, int coinsSize, int amount, int *backup) {
  if (backup[amount] != -1) {
    return backup[amount];
  }
  int min = INT_MAX;
  for (int i = 0; i < coinsSize; ++i) {
    int tmp = coinChange(coins, coinsSize, amount - coins[i]);
    if (-1 == tmp) {
      continue;
    }
    if (min > tmp) {
      min = tmp;
    }
  }

  backup[amount] = min == INT_MAX ? -1 : min + 1;
  return backup[amount];
}

// 子问题数目为O(n)，处理一个子问题的时间不变，仍是O(k)。
// 时间复杂度：O(kn)。 
*/

// 完全背包
int coinChange(int *coins, int coinsSize, int amount) {
  int dp[amount + 1];  // dp[i]:凑足总额为i所需钱币的最少个数为dp[i]
  dp[0] = 0;
  for (int i = 1; i <= amount; ++i) {
    dp[i] = INT_MAX;  // 求最少的个数，初始化为最大值
  }

  // 那么钱币有顺序和没有顺序都可以，都不影响钱币的最⼩个数。所以本题并不强调集合是组合还是排列。
  for (int i = 0; i < coinsSize; ++i) {
    for (int j = coins[i]; j <= amount; ++j) {
      if (dp[j - coins[i]] != INT_MAX) {
        // 凑⾜总额为j-coins[i]的最少个数为dp[j-coins[i]]，那么只需要加上⼀个钱币coins[i]即dp[j-coins[i]]+1就是dp[j]
        dp[j] = fmin(dp[j], dp[j - coins[i]] + 1);
      }
    }
  }

  // for (int i = 1; i <= amount; ++i) {
  //   for (int j = 0; j < coinsSize; ++j) {
  //     if (i >= coins[j] && dp[i - coins[j]] != INT_MAX) {
  //       dp[i] = fmin(dp[i], dp[i - coins[j]] + 1);
  //     }
  //   }
  // }

  return dp[amount] == INT_MAX ? -1 : dp[amount];
}

// 计算机解决问题其实没有任何奇技淫巧，它唯一的解决办法就是穷举，穷举所有可能性。
// 备忘录、DP table就是在追求“如何聪明地穷举”。用空间换时间的思路，是降低时间复杂度的不二法门。

// @lc code=end
