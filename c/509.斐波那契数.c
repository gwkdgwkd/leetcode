/*
 * @lc app=leetcode.cn id=509 lang=c
 *
 * [509] 斐波那契数
 */

// @lc code=start

/*
// 暴力递归
int fib(int n) {
  if (1 == n || 2 == n) {
    return 1;
  }
  return fib(n - 1) + fib(n - 2);
}

// 递归算法的时间复杂度=子问题个数×解决一个子问题需要的时间
// 子问题个数，即递归树中节点的总数。二叉树节点总数为指数级别，所以子问题个数为O(2^n)。
// 解决一个子问题的时间，本算法中没有循环，只有f(n-1)+f(n-2)一个加法操作，时间为O(1)。
// 时间复杂度：O(2^n)，指数级别，爆炸。
// 算法低效的原因：存在大量重复计算，比如f(18)被计算了两次。
*/

/* 
#include <stdlib.h>

// 带备忘录的递归解法
int helper(int *backup, int n) {
  if (1 == n || 2 == n) {
    return 1;
  }
  if (backup[n] != 0) {
    return backup[n];
  }
  backup[n] = helper(backup, n - 1) + helper(backup, n - 2);
  return backup[n];
}
int fib(int n) {
  if (n <= 0) {
    return 0;
  }
  int *backup = (int *)malloc((n + 1) * sizeof(int));
  for (int i = 1; i <= n; ++i) {
    backup[i] = 0;
  }

  return helper(backup, n);
}

// 把一颗存在巨量冗余的递归树通过减枝，改造成了一幅不存在冗余的递归图，极大减少了子问题。
// 子问题个数，就是节点的总数，不存在冗余计算，子问题和输入的n相同，O(n)。
// 解决一个子问题的时间，同上，没有循环，时间为O(1)。
// 时间复杂度：O(n)，比起暴力算法，是降维打击。
// 这种解法和迭代的动态规划效率已经差不多了，只不过这种方法加自顶向下，动态规划叫做自底向上。
*/

/* 
#include <stdlib.h>

// dp数组的迭代解法
int fib(int n) {
  if (n <= 0) {
    return 0;
  }
  if (1 == n || 2 == n) {
    return 1;
  }

  int *dp = (int *)malloc((n + 1) * sizeof(int));
  dp[1] = dp[2] = 1;  // 0空着不用
  for (int i = 3; i <= n; ++i) {
    dp[i] = dp[i - 1] + dp[i - 2];
  }
  return dp[n];
}

// 状态转移方程：
// f(n) = { 1,n = 1,2
//        { f(n - 1) + f(n - 2),n > 2
// 状态转移方程是解决问题的核心，代表着暴力解法。
// 动态规划问题最困难的就是写出状态转移方程。优化方法无非是用备忘录或者DP table。
*/

/* 
// 优化dp数组
int fib(int n) {
  if (n <= 0) {
    return 0;
  }
  if (1 == n || 2 == n) {
    return 1;
  }

  // 并不需要那么长的DP table来存储所有的状态，只要想办法储存之前的两个状态就行了。
  // 进一步优化，把空间复杂度降为O(1)。
  int prev = 1, curr = 1;
  for (int i = 3; i <= n; ++i) {
    int sum = prev + curr;
    prev = curr;
    curr = sum;
  }
  return curr;
}

// 斐波那契数列严格来说不算动态规划（没有涉及动态规划的重要特性，最优子结构），因为没有涉及求最值，以上过程演示了算法设计螺旋上升的过程。
*/

// 官方解法
int fib(int n) {
  if (n < 2) {
    return n;
  }
  int p = 0, q = 0, r = 1;
  for (int i = 2; i <= n; ++i) {
    p = q;
    q = r;
    r = p + q;
  }
  return r;
}

// @lc code=end
