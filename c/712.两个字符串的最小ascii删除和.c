/*
 * @lc app=leetcode.cn id=712 lang=c
 *
 * [712] 两个字符串的最小ASCII删除和
 */

// @lc code=start

int minimumDeleteSum(char *s1, char *s2) {
  int len1 = strlen(s1);
  int len2 = strlen(s2);
  int ret = 0;
  if (len1 == 0) {
    for (int i = 0; i < len2; ++i) {
      ret += s2[i];
    }
    return ret;
  }
  if (len2 == 0) {
    for (int i = 0; i < len1; ++i) {
      ret += s1[i];
    }
    return ret;
  }

  int dp[len1 + 1][len2 + 1];
  dp[0][0] = 0;
  for (int i = 1; i <= len1; ++i) {
    dp[i][0] = dp[i - 1][0] + s1[i - 1];
  }

  for (int i = 1; i <= len2; ++i) {
    dp[0][i] = dp[0][i - 1] + s2[i - 1];
  }

  for (int i = 1; i <= len1; ++i) {
    for (int j = 1; j <= len2; ++j) {
      if (s1[i - 1] == s2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1];
      } else {
        dp[i][j] = fmin(dp[i - 1][j] + s1[i - 1], dp[i][j - 1] + s2[j - 1]);
      }
    }
  }

  // for (int i = 0; i <= len1; ++i) {
  //   for (int j = 0; j <= len2; ++j) {
  //     printf("%d ", dp[i][j]);
  //   }
  //   printf("\n");
  // }

  return dp[len1][len2];
}
// @lc code=end
