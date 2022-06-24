/*
整数数组nums按升序排列，数组中的值互不相同。
在传递给函数之前，nums在预先未知的某个下标k（0<=k< nums.length）上进行了旋转，
使数组变为[nums[k],nums[k+1],...,nums[n-1],nums[0],nums[1],...,nums[k-1]]。
例如，[0,1,2,4,5,6,7]在下标3处经旋转后可能变为[4,5,6,7,0,1,2]。
给你旋转后的数组nums和一个整数target，如果nums中存在这个目标值target，则返回它的下标，否则返回-1。

示例1：
输入：nums = [4,5,6,7,0,1,2], target = 0
输出：4

示例2：
输入：nums = [4,5,6,7,0,1,2], target = 3
输出：-1

示例3：
输入：nums = [1], target = 0
输出：-1

提示：
1 <= nums.length <= 5000
-10^4 <= nums[i] <= 10^4
nums中的每个值都独一无二
题目数据保证nums在预先未知的某个下标上进行了旋转
-10^4 <= target <= 10^4

进阶：你可以设计一个时间复杂度为O(logn)的解决方案吗？
*/

int binarySearch(int* nums, int left, int right, int target) {
  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (nums[mid] < target) {
      left = mid + 1;
    } else if (nums[mid] > target) {
      right = mid - 1;
    } else {
      return mid;
    }
  }

  return -1;
}
int search(int* nums, int numsSize, int target) {
  int i = 1;
  while (i < numsSize) {
    if (nums[i] < nums[i - 1]) {
      break;
    }
    ++i;
  }

  int ret = binarySearch(nums, 0, i - 1, target);
  if (ret == -1) {
    ret = binarySearch(nums, i, numsSize - 1, target);
  }
  return ret;
}

int search(int* nums, int numsSize, int target) {
  int left = 0;
  int right = numsSize - 1;
  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (nums[mid] == target) {
      return mid;
    }
    if (nums[left] <= nums[mid]) {  // 要有=号，不然[3,1]错误
      // [left,mid]是有序的
      if (nums[left] <= target && target < nums[mid]) {
        // target在[left,mid)中
        right = mid - 1;
      } else {
        left = mid + 1;
      }
    } else {
      // [mid,right]是有序的
      if (nums[mid] < target && target <= nums[right]) {
        // target在(mid,right]中
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }
  }
  return -1;
}

// [面试题1003搜索旋转数组]的解法也行，但是上面的两个解法不能解决[面试题1003搜索旋转数组]