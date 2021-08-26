/*
 * @lc app=leetcode.cn id=647 lang=c
 *
 * [647] 回文子串
 */

// @lc code=start

// 动态规划
int countSubstrings(char* s) {
  int n = strlen(s);
  int dp[n][n];
  int ret = 0;
  memset(dp, 0, sizeof(dp));
  for (int i = 0; i < n; ++i) {
    dp[i][i] = 1;
    ++ret;
  }

  for (int i = n - 1; i >= 0; --i) {
    for (int j = i + 1; j < n; ++j) {
      if (j == i + 1) {
        dp[i][j] = s[i] == s[j] ? 1 : 0;
      } else {
        dp[i][j] = s[i] == s[j] ? dp[i + 1][j - 1] : 0;
      }
      if (dp[i][j]) {
        ++ret;
      }
    }
  }

  return ret;
}

// @lc code=end
