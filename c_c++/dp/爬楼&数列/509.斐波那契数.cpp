/*
斐波那契数（通常用F(n)表示）形成的序列称为斐波那契数列。
该数列由0和1开始，后面的每一项数字都是前面两项数字的和。
也就是：
F(0) = 0，F(1) = 1
F(n) = F(n - 1) + F(n - 2)，其中n > 1
给定n，请计算F(n)。

示例1：
输入：n = 2
输出：1
解释：F(2) = F(1) + F(0) = 1 + 0 = 1

示例2：
输入：n = 3
输出：2
解释：F(3) = F(2) + F(1) = 1 + 1 = 2

示例3：
输入：n = 4
输出：3
解释：F(4) = F(3) + F(2) = 2 + 1 = 3

提示：0 <= n <= 30
*/

// 暴力递归
int fib(int n) {
  if (1 == n || 2 == n) {
    return 1;
  }
  return fib(n - 1) + fib(n - 2);
}

// 递归算法的时间复杂度=子问题个数×解决一个子问题需要的时间
// 子问题个数，即递归树中节点的总数。
// 二叉树节点总数为指数级别，所以子问题个数为O(2^n)。
// 解决一个子问题的时间，本算法中没有循环，
// 只有f(n-1)+f(n-2)一个加法操作，时间为O(1)。
// 时间复杂度：O(2^n)，指数级别，爆炸。
// 算法低效的原因：存在大量重复计算，比如f(18)被计算了两次。

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

// 把一颗存在巨量冗余的递归树通过减枝，改造成了一幅不存在冗余的递归图，
// 极大减少了子问题，子问题个数，就是节点的总数，不存在冗余计算，
// 子问题和输入的n相同，O(n)，解决一个子问题的时间，同上，没有循环，时间为O(1)。
// 时间复杂度：O(n)，比起暴力算法，是降维打击。
// 这种解法和迭代的动态规划效率已经差不多了，
// 只不过这种方法加自顶向下，动态规划叫做自底向上。

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
// 动态规划问题最困难的就是写出状态转移方程。
// 优化方法无非是用备忘录或者DP table。

// 优化dp数组
int fib(int n) {
  if (n <= 0) {
    return 0;
  }
  if (1 == n || 2 == n) {
    return 1;
  }

  // 并不需要那么长的DP table来存储所有的状态，只要储存之前的两个状态就行了。
  // 进一步优化，把空间复杂度降为O(1)。
  int prev = 1, curr = 1;
  for (int i = 3; i <= n; ++i) {
    int sum = prev + curr;
    prev = curr;
    curr = sum;
  }
  return curr;
}

// 斐波那契数列严格来说不算动态规划，没有涉及动态规划的重要特性，
// 最优子结构，因为没有涉及求最值，以上过程演示了算法设计螺旋上升的过程。

int fib(int n) {
  if (n < 1) return n;
  int pre1 = 0;
  int pre2 = 1;
  int cur;

  for (int i = 2; i <= n; ++i) {
    cur = pre1 + pre2;
    pre1 = pre2;
    pre2 = cur;
  }

  return pre2;
}

class Solution {
 public:
  int fib(int n) {
    if (n <= 1) {
      return n;
    }

    int pre2 = 0;
    int pre1 = 1;
    int cur;
    for (int i = 2; i <= n; ++i) {
      cur = pre2 + pre1;
      pre2 = pre1;
      pre1 = cur;
    }

    return pre1;
  }
};

// 剑指Offer10-I斐波那契数列
int fib(int n) {
  if (n <= 1) {
    return n;
  }

  int f0 = 0;
  int f1 = 1;
  int f2;
  for (int i = 2; i <= n; ++i) {
    f2 = (f1 + f0) % 1000000007;
    f0 = f1;
    f1 = f2;
  }

  return f1;  // 在这取余会产生错误
}
