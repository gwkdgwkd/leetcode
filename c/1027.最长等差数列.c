/*
 * @lc app=leetcode.cn id=1027 lang=c
 *
 * [1027] 最长等差数列
 */

// @lc code=start

#define MAX_NUM 20001
int max(int a, int b) { return a > b ? a : b; }
int longestArithSeqLength(int* A, int ASize) {
  int res = 1;
  int dp[ASize][MAX_NUM];
  for (int i = 0; i < ASize; i++) {
    for (int j = 0; j < MAX_NUM; j++) {
      dp[i][j] = 1;
    }
  }

  for (int i = 0; i < ASize; i++) {
    for (int j = 0; j < i; j++) {
      int diff = A[i] - A[j];
      diff += 10000;
      dp[i][diff] = max(dp[i][diff], dp[j][diff] + 1);
      res = max(res, dp[i][diff]);
    }
  }
  return res;
}

// @lc code=end
