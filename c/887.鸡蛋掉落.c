/*
 * @lc app=leetcode.cn id=887 lang=c
 *
 * [887] 鸡蛋掉落
 */

// @lc code=start

/* 
#include <limits.h>

#define min(a, b) ((a) < (b) ? (a) : (b))
int g_memo[101][10001];
// 线性搜索
int dp(int k, int n) {  // 在最坏的情况下，至少需要扔鸡蛋的次数
  if (g_memo[k][n] != 0) {
    return g_memo[k][n];
  }
  if (1 == k) {  // 只有一个鸡蛋，至少需要扔n次
    return n;
  }
  if (0 == n) {  // 已经扔到最后一楼，不需要扔了
    return 0;
  }

  int ret = INT_MAX;
  for (int i = 1; i <= n; ++i) {
    int broken = dp(k - 1, i - 1);
    int notbroken = dp(k, n - i);
    if (broken > notbroken) {
      ret = min(ret, broken + 1);
    } else {
      ret = min(ret, notbroken + 1);
    }
  }
  g_memo[k][n] = ret;
  return ret;
}
int superEggDrop(int k, int n) { return dp(k, n); }

// 动态规划算法的时间复杂度就是子问题个数×函数本身的复杂度
// dp有一个for循环，复杂度是O(n)。
// 子问题个数是不同状态的总数，是两个状态的乘积，也就是O(KN)。
// 时间复杂度：O(K*N^2)。
// 空间复杂度：O(KN)。
// dp(K,N) = min(0<=i<=N){max{dp(K-1,i-1),dp(K,N-i)} + 1}
// 确定当前的鸡蛋个数和面对的楼层数，就知道最小扔鸡蛋次数，最终要的答案就是dp(K,N)的结果。
// 这种思路下，肯定要穷举所有可能的扔法，用下面的二分搜索优化也只是做了减枝，减小了搜索空间，但本质思路没有变，还是穷举。
*/

/* 
#include <limits.h>

#define min(a, b) ((a) < (b) ? (a) : (b))
int g_memo[101][10001];
// 用二分搜索代替线性搜索
int dp(int k, int n) {  // 在最坏的情况下，至少需要扔鸡蛋的次数
  if (g_memo[k][n] != 0) {
    return g_memo[k][n];
  }
  if (1 == k) {  // 只有一个鸡蛋，至少需要扔n次
    return n;
  }
  if (0 == n) {  // 已经扔到最后一楼，不需要扔了
    return 0;
  }

  int ret = INT_MAX;
  int low = 1, high = n;
  while (low <= high) {
    int mid = (high + low) / 2;
    int broken = dp(k - 1, mid - 1);
    int notbroken = dp(k, n - mid);
    if (broken > notbroken) {
      high = mid - 1;
      ret = min(ret, broken + 1);
    } else {
      low = mid + 1;
      ret = min(ret, notbroken + 1);
    }
  }
  g_memo[k][n] = ret;
  return ret;
}
int superEggDrop(int k, int n) { return dp(k, n); }

// dp使用了二分搜索，复杂度是O(logN)。
// 子问题个数是不同状态的总数，是两个状态的乘积，也就是O(KN)。
// 时间复杂度：O(K*N*logN)，效率要高效一些。
// 空间复杂度：O(KN)。
*/

// 找状态规划的状态就是见仁见智，比较玄学的事情，不同的状态定义可以衍生出不同的解法，解法和复杂度都可能有巨大差异。
// 修改dp数组的定义，确定当前的鸡蛋个数和最多允许的扔蛋次数，就知道能够确定F的最高楼层数。
int superEggDrop(int k, int n) {
  // dp数组的含义：dp[k][m] = n表示有k个鸡蛋，扔m次，最坏情况下最多可以扔n层楼
  int **dp = (int **)malloc(sizeof(int *) * (k + 1));
  for (int i = 0; i < k + 1; ++i) {
    // bad case:
    // dp[0][...] = 0表示有0个鸡蛋，无论可以扔几次，最多能扔0层楼
    // dp[...][0] = 0表示可以扔0次，无论有多少个鸡蛋，最多能扔0层楼
    dp[i] = (int *)calloc(n + 1, sizeof(int));
  }

  int m = 0;  // 鸡蛋扔m次
  // for(int m = 1;dp[k][m] < n; ++m)
  while (dp[k][m] < n) {  // dp[k][m] == n表示找到最多次数m
    m++;
    for (int i = 1; i <= k; ++i) {
      // dp[i][m - 1]表示鸡蛋没碎还可以扔的楼层数
      // dp[i - 1][m - 1]表示鸡蛋碎了还可以扔的楼层数
      // 1表示当前已经扔了1层
      dp[i][m] = dp[i][m - 1] + dp[i - 1][m - 1] + 1;
    }
  }

  return m;
}

// 时间复杂度：O(KN)
// dp转移只和左边和左上的两个状态有关，所以很容易优化成一维dp数组
// 还可以借助二分搜索法快速逼近dp[K][m]==N这个终止条件，时间复杂度进一步下降为O(KlogN)。

// @lc code=end
