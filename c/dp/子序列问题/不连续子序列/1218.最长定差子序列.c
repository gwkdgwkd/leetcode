/*
 * @lc app=leetcode.cn id=1218 lang=c
 *
 * [1218] 最长定差子序列
 */

// @lc code=start

// 动态规划，超时，与300类似
int longestSubsequence(int* arr, int arrSize, int difference) {
  int dp[arrSize];
  for (int i = 0; i < arrSize; ++i) {
    dp[i] = 1;
  }

  int max = dp[0];
  for (int i = 1; i < arrSize; ++i) {
    for (int j = 0; j < i; ++j) {
      if (arr[i] - arr[j] == difference) {
        dp[i] = fmax(dp[i], dp[j] + 1);
      }
      max = fmax(max, dp[i]);
    }
  }

  return max;
}

// @lc code=end
