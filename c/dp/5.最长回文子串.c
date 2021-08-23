/*
 * @lc app=leetcode.cn id=5 lang=c
 *
 * [5] 最长回文子串
 */

// @lc code=start

char* longestPalindrome(char* s) {
  int n = strlen(s);
  if (n == 1) {
    return s;
  }

  bool dp[n][n];
  memset(dp, 0, sizeof(dp));
  for (int i = 0; i < n; ++i) {
    dp[i][i] = true;
  }

  int maxlen = 1;
  int start = 0;
  for (int i = n - 2; i >= 0; --i) {
    for (int j = i + 1; j < n; ++j) {
      if (s[i] == s[j]) {  // s[i] != s[j],dp[i][j] = false
        if (j - i <= 2) {
          dp[i][j] = true;
        } else {
          dp[i][j] = dp[i + 1][j - 1];
        }
      }
      if (dp[i][j] && (j - i + 1 > maxlen)) {
        maxlen = j - i + 1;
        start = i;
      }
    }
  }
  s[start + maxlen] = 0;

  return s + start;
}

// @lc code=end
