/*
 * @lc app=leetcode.cn id=213 lang=c
 *
 * [213] 打家劫舍 II
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
  if (numsSize == 2) {
    return fmax(nums[0], nums[1]);
  }

  int pre01 = nums[0];
  int pre02 = fmax(nums[0], nums[1]);
  int pre11 = nums[1];
  int pre12 = fmax(nums[1], nums[2]);

  for (int i = 2; i < numsSize; ++i) {
    // 首尾不能同时偷，尾不偷：0 - n-2
    if (i < numsSize - 1) {
      int curr1 = fmax(pre02, pre01 + nums[i]);
      pre01 = pre02;
      pre02 = curr1;
    }
    // 首尾不能同时偷，首不偷：1 - n-1
    if (i > 2) {
      int curr2 = fmax(pre12, pre11 + nums[i]);
      pre11 = pre12;
      pre12 = curr2;
    }
  }

  return fmax(pre02, pre12);
}

// @lc code=end
