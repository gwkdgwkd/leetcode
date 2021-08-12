/*
 * @lc app=leetcode.cn id=516 lang=c
 *
 * [516] 最长回文子序列
 */

// @lc code=start

int longestPalindromeSubseq(char* s) {
  int n = strlen(s);
  if (0 == n || 1 == n) {
    return n;
  }

  // dp[i][j]表示子串s[i..j]的最长回文子序列长度
  int dp[n][n];
  memset(dp, 0, sizeof(dp));
  for (int i = 0; i < n; ++i) {
    dp[i][i] = 1;
  }

  // 从下到上，从左到右遍历
  for (int i = n - 1; i >= 0; --i) {
    // 只考虑右上的倒三角，左下的三角（i>j）的序列不存在
    for (int j = i + 1; j < n; ++j) {
      if (s[i] == s[j]) {
        // 等于左下的长度加2
        dp[i][j] = dp[i + 1][j - 1] + 2;
      } else {
        dp[i][j] = fmax(dp[i + 1][j], dp[i][j - 1]);
      }
    }
  }

  // 表示s的最长回文子序列
  return dp[0][n - 1];
}

// @lc code=end
