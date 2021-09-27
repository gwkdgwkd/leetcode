/*
 * @lc app=leetcode.cn id=27 lang=c
 *
 * [27] 移除元素
 */

// @lc code=start

// 暴力法
int removeElement(int* nums, int numsSize, int val) {
  int count = numsSize;
  for (int i = 0; i < count; ++i) {
    if (nums[i] == val) {
      for (int j = i + 1; j < count; ++j) {
        nums[j - 1] = nums[j];
      }
      count--;
      --i;
    }
  }
  return count;
}

// 双指针
int removeElement(int* nums, int numsSize, int val) {
  int slow = 0;
  for (int fast = 0; fast < numsSize; ++fast) {
    if (val != nums[fast]) {
      nums[slow++] = nums[fast];
    }
  }

  return slow;
}
// @lc code=end
