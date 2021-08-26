/*
 * @lc app=leetcode.cn id=198 lang=c
 *
 * [198] 打家劫舍
 */

// @lc code=start

// 动态规划
int rob1(int* nums, int numsSize) {
  if (numsSize == 0) {
    return numsSize;
  }
  if (numsSize == 1) {
    return nums[0];
  }

  int dp[numsSize];  // dp[i]：i（包括i）以内的房屋，最多可以偷窃的⾦额为dp[i]。
  memset(dp, 0, sizeof(dp));
  dp[0] = nums[0];
  dp[1] = fmax(nums[0], nums[1]);

  for (int i = 2; i < numsSize; ++i) {
    // 如果偷第i房间，那么dp[i]=dp[i-2]+nums[i]，第i-1房⼀定是不考虑的，找出下标i-2（包括i-2）以内的房屋，最多可以偷窃的⾦额为dp[i-2]加上第i房间偷到的钱。
    // 如果不偷第i房间，那么dp[i]=dp[i-1]，即考虑i-1房。
    dp[i] = fmax(dp[i - 1], dp[i - 2] + nums[i]);
  }

  return dp[numsSize - 1];
}

// 压缩dp
int rob2(int* nums, int numsSize) {
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

// @lc code=end
