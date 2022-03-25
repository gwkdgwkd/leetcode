/*
给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。
如果目标值不存在于数组中，返回它将会被按顺序插入的位置。
请必须使用时间复杂度为O(logn)的算法。

示例1:
输入: nums = [1,3,5,6], target = 5
输出: 2

示例2:
输入: nums = [1,3,5,6], target = 2
输出: 1

示例3:
输入: nums = [1,3,5,6], target = 7
输出: 4

提示:
1 <= nums.length <= 104
-104 <= nums[i] <= 104
nums为无重复元素的升序排列数组
-104 <= target <= 104
*/

int searchInsert(int* nums, int numsSize, int target) {
  int left = 0;
  int right = numsSize - 1;
  int mid;

  while (left <= right) {
    mid = left + (right - left) / 2;
    if (nums[mid] == target) {
      return mid;
    } else if (nums[mid] < target) {
      left = mid + 1;
    } else if (nums[mid] > target) {
      right = mid - 1;
    }
  }

  return left;  // while退出时，left>right，所以返回right不行
}

int searchInsert(int* nums, int numsSize, int target) {
  int left = 0;
  int right = numsSize;
  int mid;

  while (left < right) {
    mid = left + (right - left) / 2;
    if (nums[mid] == target) {
      return mid;
    } else if (nums[mid] < target) {
      left = mid + 1;
    } else if (nums[mid] > target) {
      right = mid;
    }
  }

  return left;  // right也行
}