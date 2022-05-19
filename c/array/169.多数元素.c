/*
给定一个大小为n的数组，找到其中的多数元素。
多数元素是指在数组中出现次数大于n/2的元素。
你可以假设数组是非空的，并且给定的数组总是存在多数元素。

示例1：
输入：[3,2,3]
输出：3

示例2：
输入：[2,2,1,1,1,2,2]
输出：2

进阶：尝试设计时间复杂度为O(n)、空间复杂度为O(1)的算法解决此问题。
*/

// 剑指Offer39数组中出现次数超过一半的数字

int majorityElement(int* nums, int numsSize) {
  if (numsSize < 3) return nums[0];

  int max = nums[0];
  int count = 1;
  for (int i = 1, c = 1; i != numsSize; i++) {
    if (count == 0) {
      max = nums[i];
    }
    nums[i] == max ? count++ : count--;
  }
  return max;
}

int cmp(int* a, int* b) { return *a - *b; }
int majorityElement(int* nums, int numsSize) {
  qsort(nums, numsSize, sizeof(int), cmp);
  return nums[numsSize / 2];
}

// 面试题1710主要元素
// 数组中占比超过一半的元素称之为主要元素。
// 给你一个整数数组，找出其中的主要元素。若没有，返回-1。

// 摩尔投票
int majorityElement(int* nums, int numsSize) {
  int index = 0, number = nums[0], i;
  for (i = 0; i < numsSize; i++) {
    if (nums[i] == number)
      index++;
    else
      index--;
    if (index == 0) number = nums[i + 1];
  }
  index = 0;
  for (i = 0; i < numsSize; i++) {
    if (nums[i] == number) index++;
  }
  return index > numsSize / 2 ? number : -1;
}