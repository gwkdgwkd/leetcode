/*
 * @lc app=leetcode.cn id=718 lang=c
 *
 * [718] 最长重复子数组
 */

// @lc code=start

// 动态规划
int findLength(int* A, int ASize, int* B, int BSize) {
  // dp[i][j]表示A[i-1  ---  n-1]和B[j-1  ---  n-1]的最长公共前缀
  int dp[ASize + 1][BSize + 1];
  memset(dp, 0, sizeof(dp));
  int ans = 0;
  // 从下到上，从右到左遍历
  for (int i = ASize - 1; i >= 0; i--) {
    for (int j = BSize - 1; j >= 0; j--) {
      dp[i][j] = A[i] == B[j] ? dp[i + 1][j + 1] + 1 : 0;
      ans = fmax(ans, dp[i][j]);
    }
  }

  // for (int i = 0; i <= ASize; ++i) {
  //   for (int j = 0; j <= BSize; ++j) {
  //     printf("%3d ", dp[i][j]);
  //   }
  //   printf("\n");
  // }
  // [1,2,3,2,1],[3,2,1,4,7]
  //   0   0   1   0   0   0
  //   0   1   0   0   0   0
  //   3   0   0   0   0   0
  //   0   2   0   0   0   0
  //   0   0   1   0   0   0
  //   0   0   0   0   0   0

  return ans;
}
// @lc code=end
