/*
 * @lc app=leetcode.cn id=198 lang=c
 *
 * [198] 打家劫舍
 */

// @lc code=start

// 动态规划
int rob(int* nums, int numsSize) {
  if (numsSize == 0) {
    return numsSize;
  }
  if (numsSize == 1) {
    return nums[0];
  }

  int dp[numsSize];
  dp[0] = nums[0];
  dp[1] = fmax(nums[1], nums[0]);

  for (int i = 2; i < numsSize; ++i) {
    dp[i] = fmax(dp[i - 1], dp[i - 2] + nums[i]);
  }

  return dp[numsSize - 1];
}

/*
// 压缩dp
int rob(int* nums, int numsSize) {
  if (numsSize == 0) {
    return numsSize;
  }
  if (numsSize == 1) {
    return nums[0];
  }

  int pre1 = nums[0];
  int pre2 = fmax(nums[1], nums[0]);

  for (int i = 2; i < numsSize; ++i) {
    int curr = fmax(pre2, pre1 + nums[i]);
    pre1 = pre2;
    pre2 = curr;
  }

  return pre2;
}
*/

// @lc code=end
