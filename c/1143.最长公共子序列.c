/*
 * @lc app=leetcode.cn id=1143 lang=c
 *
 * [1143] 最长公共子序列
 */

// @lc code=start

int longestCommonSubsequence(char* text1, char* text2) {
  int len1 = strlen(text1);
  int len2 = strlen(text2);
  if (len1 * len2 == 0) {
    return 0;
  }

  int dp[len1 + 1][len2 + 1];
  memset(dp, 0, sizeof(dp));

  for (int i = 1; i <= len1; ++i) {
    for (int j = 1; j <= len2; ++j) {
      if (text1[i - 1] == text2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        dp[i][j] = fmax(dp[i - 1][j], dp[i][j - 1]);
      }
    }
  }

  return dp[len1][len2];
}

// @lc code=end
