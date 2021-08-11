/*
 * @lc app=leetcode.cn id=53 lang=c
 *
 * [53] 最大子序和
 */

// @lc code=start

#define MAX(a, b) ((a) > (b) ? (a) : (b))
int maxSubArray(int* nums, int numsSize) {
  // dp[i]表示以nums[i]结尾的最长子序列之和
  int dp[numsSize];
  dp[0] = nums[0];
  for (int i = 1; i < numsSize; ++i) {
    // nums[i]大，表示dp[i-1]为负数，重新开始一个序列，为nums[i]
    // nums[i]+dp[i-1]大，表示dp[i-1]为正数，最大子序列要加上nums[i]
    dp[i] = MAX(nums[i], nums[i] + dp[i - 1]);
  }

  int ret = dp[0];
  for (int i = 1; i < numsSize; ++i) {
    ret = MAX(dp[i], ret);
  }

  return ret;
}

// 时间复杂度：O(N)
// 空间复杂度：O(N)

/*
// 官方题解
int maxSubArray(int* nums, int numsSize) {
  int pre = 0, maxAns = nums[0];
  for (int i = 0; i < numsSize; i++) {
    pre = fmax(pre + nums[i], nums[i]);
    maxAns = fmax(maxAns, pre);
  }
  return maxAns;
}

// 时间复杂度：O(N)
// 空间复杂度：O(1)
*/

// @lc code=end
