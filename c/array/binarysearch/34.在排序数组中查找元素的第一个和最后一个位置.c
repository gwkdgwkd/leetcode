/*
 * @lc app=leetcode.cn id=34 lang=c
 *
 * [34] 在排序数组中查找元素的第一个和最后一个位置
 */

// @lc code=start

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int findFirst(int* nums, int numsSize, int target) {
  int left = 0;
  int right = numsSize - 1;

  while (left < right) {  // 跳出循环时，left一定等于right
    int mid = left + (right - left) / 2;
    if (nums[mid] == target) {
      right = mid;
    } else if (nums[mid] < target) {
      left = mid + 1;
    } else if (nums[mid] > target) {
      right = mid - 1;
    }
  }
  if (nums[left] == target) {
    return left;
  }

  return -1;
}
int findLast(int* nums, int numsSize, int target) {
  int left = 0;
  int right = numsSize - 1;

  while (left < right) {
    // 需要向上取整，不然会死循环
    int mid = left + (right - left + 1) / 2;
    if (nums[mid] == target) {
      left = mid;
    } else if (nums[mid] < target) {
      left = mid + 1;
    } else if (nums[mid] > target) {
      right = mid - 1;
    }
  }

  // 执行到这里一定是能找到target的，直接返回left
  return left;
}
int* searchRange(int* nums, int numsSize, int target, int* returnSize) {
  int* result = (int*)malloc(sizeof(int) * 2);
  *returnSize = 2;
  if (numsSize == 0) {
    result[0] = result[1] = -1;
  } else {
    result[0] = findFirst(nums, numsSize, target);
    result[1] = result[0] == -1 ? -1 : findLast(nums, numsSize, target);
  }

  return result;
}
// @lc code=end
