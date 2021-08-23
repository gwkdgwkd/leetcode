/*
 * @lc app=leetcode.cn id=313 lang=c
 *
 * [313] 超级丑数
 */

// @lc code=start

// 动态规划
int nthSuperUglyNumber(int n, int* primes, int primesSize) {
  int dp[n + 1];
  dp[1] = 1;
  int m = primesSize;
  int pointers[m];
  for (int i = 0; i < m; i++) {
    pointers[i] = 1;
  }
  for (int i = 2; i <= n; i++) {
    int nums[m];
    int minNum = INT_MAX;
    for (int j = 0; j < m; j++) {
      nums[j] = dp[pointers[j]] * primes[j];
      minNum = fmin(minNum, nums[j]);
    }
    dp[i] = minNum;
    for (int j = 0; j < m; j++) {
      if (minNum == nums[j]) {
        pointers[j]++;
      }
    }
  }
  return dp[n];
}
// @lc code=end
