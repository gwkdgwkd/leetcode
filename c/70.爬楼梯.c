/*
 * @lc app=leetcode.cn id=70 lang=c
 *
 * [70] 爬楼梯
 */

// @lc code=start

/* 
// 动态规划
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
*/

int climbStairs(int n) {
  int a = 0, b = 1, c = 0;
  while (n--) {
    c = a + b;
    a = b;
    b = c;
  }
  return c;
}

// @lc code=end
