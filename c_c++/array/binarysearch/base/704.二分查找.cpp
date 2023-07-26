#include <stdio.h>

#include <vector>

/*
给定一个n个元素有序的（升序）整型数组nums和一个目标值target，
写一个函数搜索nums中的target，如果目标值存在返回下标，否则返回-1。

示例1：
输入：nums = [-1,0,3,5,9,12], target = 9
输出：4
解释：9出现在nums中并且下标为4

示例2：
输入：nums = [-1,0,3,5,9,12], target = 2
输出：-1
解释：2不存在nums中因此返回-1

提示：
你可以假设nums中的所有元素是不重复的。
n将在[1, 10000]之间。
nums的每个元素都将在[-9999, 9999]之间。
*/

// 第一种写法：
int search1(int* nums, int numsSize, int target) {
  int left = 0;
  int right = numsSize - 1;  // 定义target在左闭右闭的区间里，[left,right]

  // 当left==right，区间[left,right]依然有效，所以用<=，如果用<，
  // 对于只有一个元素并且与target相等的数组，那么left<right为false，返回-1，错误
  while (left <= right) {
    // int mid = left + ((right - left) >> 1);
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

using namespace std;
class Solution {
 public:
  int search(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;

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
};

// 第二种写法：
int search2(int* nums, int numsSize, int target) {
  int left = 0;
  int right = numsSize;  // 定义target在左闭右开的区间里，[left,right)

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

class Solution {
 public:
  int search(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size();

    while (left < right) {
      int mid = left + (right - left) / 2;
      if (nums[mid] < target) {
        left = mid + 1;
      } else if (nums[mid] > target) {
        right = mid;
      } else {
        return mid;
      }
    }

    return -1;
  }
};

int main() {
  int nums1[] = {1, 2, 2, 2, 2, 2, 3};
  printf("s1: %d\n", search1(nums1, sizeof(nums1) / sizeof(int), 2));  // 3
  printf("s2: %d\n", search2(nums1, sizeof(nums1) / sizeof(int), 2));  // 3

  int nums[] = {1, 2, 2, 2, 2, 2, 2, 3};
  printf("s1: %d\n", search1(nums, sizeof(nums) / sizeof(int), 2));  // 3
  printf("s2: %d\n", search2(nums, sizeof(nums) / sizeof(int), 2));  // 4

  return 0;
}