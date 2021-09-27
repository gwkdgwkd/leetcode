/*
 * @lc app=leetcode.cn id=977 lang=c
 *
 * [977] 有序数组的平方
 */

// @lc code=start

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

// 双指针
int* sortedSquares(int* nums, int numsSize, int* returnSize) {
  int* ans = malloc(sizeof(int) * numsSize);
  *returnSize = numsSize;
  for (int i = 0, j = numsSize - 1, pos = numsSize - 1; i <= j;) {
    if (nums[i] * nums[i] > nums[j] * nums[j]) {
      ans[pos] = nums[i] * nums[i];
      ++i;
    } else {
      ans[pos] = nums[j] * nums[j];
      --j;
    }
    --pos;
  }
  return ans;
}
// @lc code=end
