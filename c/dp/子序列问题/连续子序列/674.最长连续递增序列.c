/*
 * @lc app=leetcode.cn id=674 lang=c
 *
 * [674] 最长连续递增序列
 */

// @lc code=start

int findLengthOfLCIS(int* nums, int numsSize) {
  // 1. 确定dp数组以及下标的含义
  // dp[i]：以下标i为结尾的数组的连续递增的⼦序列⻓度为dp[i]。
  int dp[numsSize];
  for (int i = 0; i < numsSize; ++i) {
    dp[i] = 1;
  }

  int max = dp[0];
  for (int i = 1; i < numsSize; ++i) {
    // 2. 确定递推公式
    // 如果nums[i+1]>nums[i]，那么以i+1为结尾的数组的连续递增的⼦序列⻓度⼀定等于以i为结尾的数组的连续递增的⼦序列⻓度+1。
    if (nums[i] > nums[i - 1]) {
      dp[i] = dp[i - 1] + 1;
    }
    max = fmax(max, dp[i]);
  }

  return max;
}

// @lc code=end
