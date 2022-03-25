/*
给定一个n个元素有序的（升序）整型数组nums和一个目标值target，
写一个函数搜索nums中的target，如果目标值存在返回下标，否则返回-1。


示例 1:
输入: nums = [-1,0,3,5,9,12], target = 9
输出: 4
解释: 9 出现在 nums 中并且下标为 4

示例 2:
输入: nums = [-1,0,3,5,9,12], target = 2
输出: -1
解释: 2 不存在 nums 中因此返回 -1

 

提示：
你可以假设nums中的所有元素是不重复的。
n将在[1, 10000]之间。
nums的每个元素都将在[-9999, 9999]之间。
*/

#include <stdio.h>

// 第一种写法：
int search1(int* nums, int numsSize, int target) {
  int left = 0;
  int right = numsSize - 1;  // 定义target在左闭右闭的区间里，[left,right]

  // 当left==right，区间[left,right]依然有效，所以用<=
  // 如果用<，对于只有一个元素并且与target相等的数组，那么left<right为false，返回-1，错误
  while (left <= right) {
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

// 第二种写法：
int search2(int* nums, int numsSize, int target) {
  int left = 0;
  int right = numsSize;  // 定义target在左闭右开的区间里，即：[left,right)

  // 当left==right时，[left,right)是无效空间，所以使用<
  while (left < right) {
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

// 寻找左侧边界的二分搜索：
int left_bound1(int* nums, int numsSize, int target) {
  if (numsSize == 0) return -1;

  int left = 0;
  int right = numsSize;

  // 当left==right时，[left,right)是无效空间，所以使用<
  while (left < right) {
    int mid = left + (right - left) / 2;
    if (nums[mid] == target) {
      // 找到target时不要立即返回，而是缩小「搜索区间」的上界right，
      // 在区间[left, mid)中继续搜索，即不断向左收缩，达到锁定左侧边界的目的。
      right = mid;
    } else if (nums[mid] < target) {  // target在右区间，在[middle+1,right)中
      left = mid + 1;
    } else if (nums[mid] > target) {  // target在左区间，在[left,middle)中
      right = mid;
    }
  }

  // target比所有数都大
  if (left == numsSize) return -1;
  // 类似之前算法的处理方式
  return nums[left] == target ? left : -1;
  // 返回right也行，因为while终止的条件是left==right。
  // return nums[right] == target ? right : -1;
}

// 和第一种二分搜索算法统一了，都是两端都闭的「搜索区间」，而且最后返回的也是left变量的值：
int left_bound2(int* nums, int numsSize, int target) {
  int left = 0;
  int right = numsSize - 1;  // 定义target在左闭右闭的区间里，[left,right]

  while (left <= right) {  // 当left==right，区间[left,right]依然有效，所以用<=
    int mid = left + (right - left) / 2;  // 防止溢出，等同于(left+right)/2
    if (nums[mid] == target) {
      right = mid - 1;
    } else if (nums[mid] < target) {
      left = mid + 1;  // target在右区间，所以[middle+1,right]
    } else if (nums[mid] > target) {
      right = mid - 1;  // target在左区间，所以[left,middle-1]
    }
  }
  // 检查出界情况
  if (left >= numsSize || nums[left] != target) return -1;
  return left;
}

int left_bound3(int* nums, int numsSize, int target) {
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

int right_bound1(int* nums, int numsSize, int target) {
  if (numsSize == 0) return -1;

  int left = 0;
  int right = numsSize;

  while (left < right) {
    int mid = left + (right - left) / 2;
    if (nums[mid] == target) {
      // 当nums[mid] == target时，不要立即返回，而是增大「搜索区间」的下界left，
      // 使得区间不断向右收缩，达到锁定右侧边界的目的。
      left = mid + 1;
    } else if (nums[mid] < target) {
      left = mid + 1;
    } else if (nums[mid] > target) {
      right = mid;
    }
  }

  if (left == 0) return -1;
  return nums[left - 1] == target ? (left - 1) : -1;
  // return nums[right - 1] == target ? (right - 1) : -1;  // 也行
}

int right_bound2(int* nums, int numsSize, int target) {
  int left = 0;
  int right = numsSize - 1;  // 定义target在左闭右闭的区间里，[left,right]

  while (left <= right) {  // 当left==right，区间[left,right]依然有效，所以用<=
    int mid = left + (right - left) / 2;  // 防止溢出，等同于(left+right)/2
    if (nums[mid] == target) {
      left = mid + 1;
    } else if (nums[mid] < target) {
      left = mid + 1;  // target在右区间，所以[middle+1,right]
    } else if (nums[mid] > target) {
      right = mid - 1;  // target在左区间，所以[left,middle-1]
    }
  }
  // 检查出界情况
  if (right < 0 || nums[right] != target) return -1;
  return right;
}

int right_bound3(int* nums, int numsSize, int target) {
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

int main() {
  // 这个算法存在局限性:比如说给你有序数组nums = [1,2,2,2,3]，target为2，此算法返回的索引是2。
  // 但是如果我想得到target的左侧边界，即索引1，或者我想得到target的右侧边界，即索引3，这样的话此算法是无法处理的。
  // 找到一个target，然后向左或向右线性搜索不行吗？可以，但是不好，因为这样难以保证二分查找对数级的复杂度了。
  int nums1[] = {1, 2, 2, 2, 2, 2, 3};
  printf("s1: %d\n", search1(nums1, sizeof(nums1) / sizeof(int), 2));       // 3
  printf("s2: %d\n", search2(nums1, sizeof(nums1) / sizeof(int), 2));       // 3
  printf("l1: %d\n", left_bound1(nums1, sizeof(nums1) / sizeof(int), 2));   // 1
  printf("l2: %d\n", left_bound2(nums1, sizeof(nums1) / sizeof(int), 2));   // 1
  printf("l3: %d\n", left_bound3(nums1, sizeof(nums1) / sizeof(int), 2));   // 1
  printf("r1: %d\n", right_bound1(nums1, sizeof(nums1) / sizeof(int), 2));  // 5
  printf("r2: %d\n", right_bound2(nums1, sizeof(nums1) / sizeof(int), 2));  // 5
  printf("r3: %d\n", right_bound3(nums1, sizeof(nums1) / sizeof(int), 2));  // 5
  int nums[] = {1, 2, 2, 2, 2, 2, 2, 3};
  printf("s1: %d\n", search1(nums, sizeof(nums) / sizeof(int), 2));         // 3
  printf("s2: %d\n", search2(nums, sizeof(nums) / sizeof(int), 2));         // 4
  printf("l1: %d\n", left_bound1(nums, sizeof(nums) / sizeof(int), 2));     // 1
  printf("l2: %d\n", left_bound2(nums, sizeof(nums) / sizeof(int), 2));     // 1
  printf("l3: %d\n", left_bound3(nums, sizeof(nums) / sizeof(int), 2));     // 1
  printf("r1: %d\n", right_bound1(nums1, sizeof(nums1) / sizeof(int), 2));  // 5
  printf("r2: %d\n", right_bound2(nums1, sizeof(nums1) / sizeof(int), 2));  // 5
  printf("r3: %d\n", right_bound3(nums1, sizeof(nums1) / sizeof(int), 2));  // 5

  return 0;
}