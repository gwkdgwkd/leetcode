/*
给定一个按照升序排列的整数数组nums，和一个目标值target。找出给定目标值在数组中的开始位置和结束位置。
如果数组中不存在目标值target，返回[-1, -1]。

进阶：你可以设计并实现时间复杂度为O(logn)的算法解决此问题吗？

示例1：
输入：nums = [5,7,7,8,8,10], target = 8
输出：[3,4]

示例2：
输入：nums = [5,7,7,8,8,10], target = 6
输出：[-1,-1]

示例3：
输入：nums = [], target = 0
输出：[-1,-1]

提示：
0 <= nums.length <= 105
-109 <= nums[i] <= 109
nums是一个非递减数组
-109 <= target <= 109
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
    // 使用704中的也可以
    result[0] = findFirst(nums, numsSize, target);
    result[1] = result[0] == -1 ? -1 : findLast(nums, numsSize, target);
  }

  return result;
}
