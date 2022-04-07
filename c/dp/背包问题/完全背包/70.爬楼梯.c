/*
假设你正在爬楼梯。需要n阶你才能到达楼顶。
每次你可以爬1或2个台阶。你有多少种不同的方法可以爬到楼顶呢？
 
示例1：
输入：n = 2
输出：2
解释：有两种方法可以爬到楼顶。
1.1阶+1阶
2.2阶

示例2：
输入：n = 3
输出：3
解释：有三种方法可以爬到楼顶。
1.1阶+1阶+1阶
2.1阶+2阶
3.2阶+1阶

提示：1 <= n <= 45
*/

// 动态规划，和斐波那契一样
int climbStairs(int n) {
  if (n < 2) {
    return n;
  }

  int dp[n];
  dp[0] = 1;
  dp[1] = 2;
  for (int i = 2; i < n; ++i) {
    dp[i] = dp[i - 1] + dp[i - 2];
  }

  return dp[n - 1];
}

int climbStairs(int n) {
  int a = 0, b = 1, c = 0;
  while (n--) {
    c = a + b;
    a = b;
    b = c;
  }
  return c;
}

// 完全背包，求装满的排列数
int climbStairs(int n) {
  int dp[n + 1];
  memset(dp, 0, sizeof(dp));
  dp[0] = 1;

  for (int i = 1; i <= n; ++i) {
    // j就表示背包中的物品重量
    // 如果把2换成m，那么就是每次最多可以爬m阶台阶
    for (int j = 1; j <= 2; ++j) {
      if (i >= j) {
        dp[i] += dp[i - j];
      }
    }
  }

  return dp[n];
}
