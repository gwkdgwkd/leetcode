/*
 * @lc app=leetcode.cn id=1043 lang=c
 *
 * [1043] 分隔数组以得到最大和
 */

// @lc code=start

// 动态规划
int maxSumAfterPartitioning(int* arr, int arrSize, int k) {
  int dp[arrSize + 1];
  memset(dp, 0, sizeof(dp));
  for (int i = 1; i <= arrSize; i++) {
    int maxtemp = arr[i - 1];
    for (int j = 1; j <= k; j++) {
      if (i >= j) {
        maxtemp = fmax(arr[i - j], maxtemp);
        dp[i] = fmax(dp[i], dp[i - j] + maxtemp * j);
      }
      printf("%d ", dp[i]);
    }
    printf("\n");
  }

  return dp[arrSize];
}

// @lc code=end
