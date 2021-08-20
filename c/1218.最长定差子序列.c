/*
 * @lc app=leetcode.cn id=1218 lang=c
 *
 * [1218] 最长定差子序列
 */

// @lc code=start

// 动态规划，超时
int longestSubsequence(int* arr, int arrSize, int difference) {
  int dp[arrSize];
  memset(dp, 0, sizeof(dp));
  dp[0] = 1;
  for (int i = 0; i < arrSize; ++i) {
    dp[i] = 1;
  }

  for (int i = 1; i < arrSize; ++i) {
    for (int j = 0; j < i; ++j) {
      if (arr[i] - arr[j] == difference) {
        dp[i] = fmax(dp[i], dp[j] + 1);
      }
      // printf("dp[%d][%d] %d\n", j, i ,dp[i]);
    }
  }

  int max = 0;
  for (int i = 0; i < arrSize; ++i) {
    max = fmax(max, dp[i]);
    // printf("%d ", dp[i]);
  }
  // printf("\n");

  return max;
}

// @lc code=end
