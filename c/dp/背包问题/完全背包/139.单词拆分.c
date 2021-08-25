/*
 * @lc app=leetcode.cn id=139 lang=c
 *
 * [139] 单词拆分
 */

// @lc code=start

// 动态规划，完全背包
bool wordBreak(char* s, char** wordDict, int size) {
  int n = strlen(s);
  int dp[n + 1];
  memset(dp, 0, sizeof(dp));
  dp[0] = 1;

  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j < size; ++j) {
      int len = strlen(wordDict[j]);
      if (i >= len && strncmp(wordDict[j], &s[i - len], len) == 0) {
        dp[i] |= dp[i - len];
      }
    }
  }

  return dp[n];
}
// @lc code=end
