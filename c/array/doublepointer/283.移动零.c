/*
 * @lc app=leetcode.cn id=283 lang=c
 *
 * [283] 移动零
 */

// @lc code=start

// 双指针
void moveZeroes(int* nums, int numsSize) {
  int slow = 0;
  for (int fast = 0; fast < numsSize; ++fast) {
    if (nums[fast] != 0) {
      nums[slow++] = nums[fast];
    }
  }

  for (int i = slow; i < numsSize; ++i) {
    nums[i] = 0;
  }
}
// @lc code=end
