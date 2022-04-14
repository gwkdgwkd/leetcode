/*
给你一个未排序的整数数组nums，请你找出其中没有出现的最小的正整数。
请你实现时间复杂度为O(n)并且只使用常数级别额外空间的解决方案。

示例1：
输入：nums = [1,2,0]
输出：3

示例2：
输入：nums = [3,4,-1,1]
输出：2

示例3：
输入：nums = [7,8,9,11,12]
输出：1

提示：
1 <= nums.length <= 5 * 10^5
-2^31 <= nums[i] <= 2^31 - 1
*/

// 常数级别额外空间表示不能用哈希表，使用数组下标当做哈希的k
// 时间复杂度：O(N)
// 空间复杂度：O(1)
int firstMissingPositive(int* nums, int numsSize) {
  // 将数组中所有小于等于0的数修改为N+1，标记这个位置不是正确的数
  for (int i = 0; i < numsSize; ++i) {
    if (nums[i] <= 0) {
      nums[i] = numsSize + 1;
    }
  }

  for (int i = 0; i < numsSize; ++i) {
    int num = abs(nums[i]);
    if (num <= numsSize) {  // 数组中出现的数字
      nums[num - 1] =
          -abs(nums[num - 1]);  // 把出现过的数字对应位置的数字设成负数
    }
  }

  for (int i = 0; i < numsSize; ++i) {
    if (nums[i] > 0) {  // 第一个非负数，就是缺失的第一个正整数
      return i + 1;
    }
  }

  return numsSize + 1;  // 如果都出现了，那么少的就是数组长度加1
}

// 置换
// 时间复杂度：O(N)
// 空间复杂度：O(1)
int firstMissingPositive(int* nums, int numsSize) {
  for (int i = 0; i < numsSize; ++i) {
    while (nums[i] > 0 && nums[i] <= numsSize && nums[nums[i] - 1] != nums[i]) {
      int t = nums[nums[i] - 1];
      nums[nums[i] - 1] = nums[i];
      nums[i] = t;
    }
  }
  for (int i = 0; i < numsSize; ++i) {
    if (nums[i] != i + 1) {
      return i + 1;
    }
  }
  return numsSize + 1;
}