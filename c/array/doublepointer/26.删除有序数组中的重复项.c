/*
 * @lc app=leetcode.cn id=26 lang=c
 *
 * [26] 删除有序数组中的重复项
 */

// @lc code=start

// 双指针
int removeDuplicates(int* nums, int numsSize) {
  if (numsSize == 0) return 0;
  int slow = 1;
  for (int fast = 1; fast < numsSize; ++fast) {
    if (nums[fast] != nums[fast - 1]) {
      nums[slow++] = nums[fast];
    }
  }

  return slow;
}

// 双指针
int removeDuplicates(int* nums, int numsSize) {
  if (numsSize == 0) return 0;
  int slow = 0;
  int fast = 0;
  while (fast < numsSize) {
    if (nums[fast] != nums[slow]) {
      nums[++slow] = nums[fast];
    }
    fast++;
  }

  return slow + 1;
}

// @lc code=end
