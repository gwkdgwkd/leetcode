/*
 * @lc app=leetcode.cn id=72 lang=c
 *
 * [72] 编辑距离
 */

// @lc code=start

#define MIN(a, b) ((a) < (b) ? (a) : (b))
int minDistance(char *word1, char *word2) {
  int len1 = (int)strlen(word1);
  int len2 = (int)strlen(word2);

  if (len1 * len2 == 0) {
    return len1 + len2;
  }

  int dp[len1 + 1][len2 + 2];
  for (int i = 0; i <= len1; ++i) {
    dp[i][0] = i;
  }
  for (int i = 0; i <= len2; ++i) {
    dp[0][i] = i;
  }
  for (int i = 1; i <= len1; ++i) {
    for (int j = 1; j <= len2; ++j) {
      if (word1[i - 1] == word2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1];
      } else {
        dp[i][j] =
            MIN(MIN(dp[i - 1][j] + 1, dp[i][j - 1] + 1), dp[i - 1][j - 1] + 1);
      }
    }
  }

  return dp[len1][len2];
}

// @lc code=end
