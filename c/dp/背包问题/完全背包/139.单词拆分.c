/*
 * @lc app=leetcode.cn id=139 lang=c
 *
 * [139] 单词拆分
 */

// @lc code=start

// 动态规划
bool wordBreak(char* s, char** wordDict, int size) {
  int n = strlen(s);
  int dp[n + 1];
  memset(dp, 0, sizeof(dp));

  dp[0] = 1;
  for (int j = 1; j <= n; ++j) {
    for (int i = 0; i < size; ++i) {
      int len = strlen(wordDict[i]);
      if (j >= len && strncmp(wordDict[i], &s[j - len], len) == 0) {
        dp[j] |= dp[j - len];
      }
    }
  }

  return dp[n];
}
// @lc code=end
