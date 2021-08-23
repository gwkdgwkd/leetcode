/*
 * @lc app=leetcode.cn id=583 lang=c
 *
 * [583] 两个字符串的删除操作
 */

// @lc code=start

/*
// 参考最长公共子串
int minDistance(char* word1, char* word2) {
  int len1 = strlen(word1);
  int len2 = strlen(word2);
  if (len1 * len2 == 0) {
    return 0;
  }

  int dp[len1 + 1][len2 + 1];
  memset(dp, 0, sizeof(dp));

  for (int i = 1; i <= len1; ++i) {
    for (int j = 1; j <= len2; ++j) {
      if (word1[i - 1] == word2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        dp[i][j] = fmax(dp[i - 1][j], dp[i][j - 1]);
      }
    }
  }

  // 删除最后的结果就是两个字符串的最长公共子串(1143)，删除的次数为：
  return len1 - dp[len1][len2] + len2 - dp[len1][len2];
}
*/

// 直接动态规划
int minDistance(char* word1, char* word2) {
  int len1 = strlen(word1);
  int len2 = strlen(word2);
  if (len1 * len2 == 0) {
    return len1 + len2;
  }

  int dp[len1 + 1][len2 + 1];
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
        dp[i][j] = fmin(dp[i - 1][j], dp[i][j - 1]) + 1;
      }
    }
  }

  return dp[len1][len2];
}

// @lc code=end
