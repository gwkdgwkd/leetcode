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

#include <stdlib.h>

// dp数组的迭代解法
int coinChange(int *coins, int coinsSize, int amount) {
  if (amount < 0) {
    return -1;
  }
  if (amount == 0) {
    return 0;
  }

  int *dp = (int *)malloc((amount + 1) * sizeof(int));
  for (int i = 0; i < amount + 1; ++i) {
    dp[i] = amount + 1;  // 最多只能用amount个一元的硬币，amount+1相当于正无穷
  }

  dp[0] = 0;
  for (int i = 1; i < amount + 1; ++i) {
    for (int j = 0; j < coinsSize; ++j) {
      if (i - coins[j] < 0) {
        continue;
      }
      if (dp[i] > dp[i - coins[j]] + 1) {
        dp[i] = dp[i - coins[j]] + 1;
      }
    }
  }

  return (dp[amount] == amount + 1) ? -1 : dp[amount];
}

// 计算机解决问题其实没有任何奇技淫巧，它唯一的解决办法就是穷举，穷举所有可能性。
// 备忘录、DP table就是在追求“如何聪明地穷举”。用空间换时间的思路，是降低时间复杂度的不二法门。

// @lc code=end
