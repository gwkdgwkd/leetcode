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