/*
 * @lc app=leetcode.cn id=813 lang=c
 *
 * [813] 最大平均值和的分组
 */

// @lc code=start

// 动态规划
double largestSumOfAverages(int* nums, int numsSize, int k) {
  int sum[numsSize + 1];
  memset(sum, 0, sizeof(sum));
  for (int i = 1; i <= numsSize; ++i) {
    sum[i] = sum[i - 1] + nums[i - 1];
  }
  double dp[numsSize + 1][k + 1];
  memset(dp, 0, sizeof(dp));

  for (int i = 1; i <= numsSize; ++i) {
    dp[i][1] = 1.0 * sum[i] / i;
    for (int j = 2; j <= k && j <= i; ++j) {
      for (int m = 1; m < i; ++m) {
        dp[i][j] =
            fmax(dp[i][j], dp[m][j - 1] + (sum[i] - sum[m]) * 1.0 / (i - m));
      }
    }
  }
  return dp[numsSize][k];
}

// @lc code=end
