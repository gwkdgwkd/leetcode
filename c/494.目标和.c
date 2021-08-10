/*
 * @lc app=leetcode.cn id=494 lang=c
 *
 * [494] 目标和
 */

// @lc code=start

// 官方解法，动态规划，压缩dp
int findTargetSumWays(int* nums, int numsSize, int target) {
  int sum = 0;
  for (int i = 0; i < numsSize; ++i) {
    sum += nums[i];
  }
  // (sum - seg) - seg = target   =>   seg = (sum - target)/2
  int neg = sum - target;
  if (neg < 0 || neg % 2) {
    return 0;
  }
  neg /= 2;

  int dp[neg + 1];
  for (int i = 1; i <= neg; ++i) {
    dp[i] = 0;
  }
  dp[0] = 1;

  for (int i = 0; i < numsSize; ++i) {
    for (int j = neg; j >= nums[i]; --j) {
      dp[j] += dp[j - nums[i]];
    }
  }

  return dp[neg];
}

// 时间复杂度：O(n×(sum-target))。
// 空间复杂度：O(sum-target)。

// @lc code=end
