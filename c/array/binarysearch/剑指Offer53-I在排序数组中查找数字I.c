/*
统计一个数字在排序数组中出现的次数。

示例1:
输入: nums = [5,7,7,8,8,10], target = 8
输出: 2

示例2:
输入: nums = [5,7,7,8,8,10], target = 6
输出: 0

提示：
0 <= nums.length <= 105
-109 <= nums[i] <= 109
nums是一个非递减数组
-109 <= target <= 109

注意：本题与34题相同（仅返回值不同）
*/

int left_bound(int* nums, int numsSize, int target) {
  int left = 0;
  int right = numsSize - 1;
  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (nums[mid] < target) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }

  if (left >= numsSize || nums[left] != target) return -1;
  return left;
}

int right_bound(int* nums, int numsSize, int target) {
  int left = 0;
  int right = numsSize - 1;
  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (nums[mid] > target) {
      right = mid - 1;
    } else {
      left = mid + 1;
    }
  }

  if (right < 0 || nums[right] != target) return -1;
  return right;
}

int search(int* nums, int numsSize, int target) {
  int left = left_bound(nums, numsSize, target);
  int right = right_bound(nums, numsSize, target);
  if (left >= 0 && right >= 0) {
    return right - left + 1;
  } else {
    return 0;
  }
}