/*
 * @lc app=leetcode.cn id=1137 lang=c
 *
 * [1137] 第 N 个泰波那契数
 */

// @lc code=start

// 动态规划
int tribonacci(int n) {
  if (n < 2) {
    return n;
  }

  int t0 = 0;
  int t1 = 1;
  int t2 = 1;
  for (int i = 3; i <= n; ++i) {
    int t = t0 + t1 + t2;
    t0 = t1;
    t1 = t2;
    t2 = t;
  }

  return t2;
}

// @lc code=end
