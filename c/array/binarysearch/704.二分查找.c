/*
 * @lc app=leetcode.cn id=704 lang=c
 *
 * [704] 二分查找
 */

// @lc code=start

// 第一种写法
int search(int* nums, int numsSize, int target) {
  int left = 0;
  int right = numsSize - 1;  // 定义target在左闭右闭的区间里，[left,right]

  while (left <= right) {  // 当left==right，区间[left,right]依然有效，所以用<=
    int mid = left + (right - left) / 2;  // 防止溢出，等同于(left+right)/2
    if (nums[mid] == target) {
      return mid;  // 数组中找到目标值，直接返回下标
    } else if (nums[mid] < target) {
      left = mid + 1;  // target在右区间，所以[middle+1,right]
    } else if (nums[mid] > target) {
      right = mid - 1;  // target在左区间，所以[left,middle-1]
    }
  }

  return -1;  // 未找到目标值
}

// 第二种写法
int search(int* nums, int numsSize, int target) {
  int left = 0;
  int right = numsSize;  // 定义target在左闭右开的区间里，即：[left,right)

  while (left < right) {  // 当left==right时，[left,right)是无效空间，所以使用<
    int mid = left + ((right - left) >> 1);
    if (nums[mid] == target) {  // 数组中找到目标值，直接返回下标
      return mid;
    } else if (nums[mid] < target) {  // target在右区间，在[middle+1,right)中
      left = mid + 1;
    } else if (nums[mid] > target) {  // target在左区间，在[left,middle)中
      right = mid;
    }
  }

  return -1;  // 未找到目标值
}
// @lc code=end
