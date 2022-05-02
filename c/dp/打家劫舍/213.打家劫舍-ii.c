/*
你是一个专业的小偷，计划偷窃沿街的房屋，每间房内都藏有一定的现金。
这个地方所有的房屋都围成一圈，这意味着第一个房屋和最后一个房屋是紧挨着的。
同时，相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。
给定一个代表每个房屋存放金额的非负整数数组，计算你在不触动警报装置的情况下，今晚能够偷窃到的最高金额。

示例1：
输入：nums = [2,3,2]
输出：3
解释：你不能先偷窃1号房屋（金额 = 2），然后偷窃3号房屋（金额 = 2）,
因为他们是相邻的。

示例2：
输入：nums = [1,2,3,1]
输出：4
解释：你可以先偷窃1号房屋（金额 = 1），然后偷窃3号房屋（金额 = 3）。
偷窃到的最高金额 = 1 + 3 = 4。

示例3：
输入：nums = [1,2,3]
输出：3

提示：
1 <= nums.length <= 100
0 <= nums[i] <= 1000
*/

// 剑指OfferII090环形房屋偷盗

// 这道题⽬和198.打家劫舍是差不多的，唯⼀区别就是成环了。
// 对于⼀个数组，成环的话主要有如下三种情况：
// 1.情况⼀：考虑不包含⾸尾元素
// 2.情况⼆：考虑包含⾸元素，不包含尾元素
// 3.情况三：考虑包含尾元素，不包含⾸元素
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

  int dp1[numsSize];  // 首偷尾不偷，0 ～ n-2
  dp1[0] = nums[0];
  dp1[1] = fmax(nums[0], nums[1]);
  int dp2[numsSize];  // 首不偷尾偷，1 ～ n-1
  dp2[1] = nums[1];
  dp2[2] = fmax(nums[1], nums[2]);

  for (int i = 2; i < numsSize; ++i) {
    if (i < numsSize - 1) {
      dp1[i] = fmax(dp1[i - 2] + nums[i], dp1[i - 1]);
    }
    if (i > 2) {
      dp2[i] = fmax(dp2[i - 2] + nums[i], dp2[i - 1]);
    }
  }

  return fmax(dp1[numsSize - 2], dp2[numsSize - 1]);
}

// 压缩dp
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
