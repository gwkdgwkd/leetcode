/*
 * @lc app=leetcode.cn id=1025 lang=c
 *
 * [1025] 除数博弈
 */

// @lc code=start

// 动态规划
bool divisorGame(int n) {
  if (1 == n) {
    return false;
  }
  bool dp[n + 1];
  memset(dp, 0, sizeof(dp));
  dp[1] = false;
  dp[2] = true;

  for (int i = 3; i <= n; ++i) {
    for (int j = 1; j < i; ++j) {
      if (i % j == 0 && !dp[i - j]) {
        dp[i] = true;
        break;
      }
    }
  }
  return dp[n];
}

/*
// 数学
bool divisorGame(int n){
    return n%2 == 0;
}
*/

// @lc code=end
