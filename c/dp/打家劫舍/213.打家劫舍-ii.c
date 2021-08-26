/*
 * @lc app=leetcode.cn id=213 lang=c
 *
 * [213] 打家劫舍 II
 */

// @lc code=start

// 这道题⽬和198.打家劫舍是差不多的，唯⼀区别就是成环了。对于⼀个数组，成环的话主要有如下三种情况：
//  情况⼀：考虑不包含⾸尾元素
//  情况⼆：考虑包含⾸元素，不包含尾元素
//  情况三：考虑包含尾元素，不包含⾸元素
// ⽽情况⼆和情况三都包含了情况⼀了，所以只考虑情况⼆和情况三就可以了。

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
    if (i < numsSize - 1) {  // 首尾不能同时偷，尾不偷：0 - n-2
      int curr1 = fmax(pre02, pre01 + nums[i]);
      pre01 = pre02;
      pre02 = curr1;
    }
    if (i > 2) {  // 首尾不能同时偷，首不偷：1 - n-1
      int curr2 = fmax(pre12, pre11 + nums[i]);
      pre11 = pre12;
      pre12 = curr2;
    }
  }

  return fmax(pre02, pre12);
}

// @lc code=end
