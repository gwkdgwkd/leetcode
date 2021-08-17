/*
 * @lc app=leetcode.cn id=673 lang=c
 *
 * [673] 最长递增子序列的个数
 */

// @lc code=start

// 动态规划
int findNumberOfLIS(int* nums, int numsSize) {
  if (numsSize == 1) {
    return numsSize;
  }

  int dp[numsSize];
  int count[numsSize];
  for (int i = 0; i < numsSize; ++i) {
    dp[i] = 1;
    count[i] = 1;
  }
  int max = 0;
  for (int i = 1; i < numsSize; ++i) {
    for (int j = 0; j < i; ++j) {
      if (nums[i] > nums[j]) {
        if (dp[j] + 1 > dp[i]) {
          count[i] = count[j];
        } else if (dp[j] + 1 == dp[i]) {
          count[i] += count[j];
        }
        dp[i] = fmax(dp[i], dp[j] + 1);
      }
      max = fmax(max, dp[i]);
    }
  }

  int ret = 0;
  for (int i = 0; i < numsSize; ++i) {
    if (max == dp[i]) {
      ret += count[i];
    }
  }

  return ret;
}

// @lc code=end
