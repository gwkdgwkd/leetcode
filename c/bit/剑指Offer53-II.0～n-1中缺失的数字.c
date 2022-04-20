/*
一个长度为n-1的递增排序数组中的所有数字都是唯一的，并且每个数字都在范围0～n-1之内。
在范围0～n-1内的n个数字中有且只有一个数字不在该数组中，请找出这个数字。

示例1:
输入: [0,1,3]
输出: 2

示例2:
输入: [0,1,2,3,4,5,6,7,9]
输出: 8

限制：1 <= 数组长度 <= 10000
*/

// 数组无序，就不能用这种方法
int missingNumber(int* nums, int numsSize) {
  for (int i = 0; i < numsSize; ++i) {
    if (nums[i] != i) {
      return i;
    }
  }

  return numsSize;
}

int missingNumber(int* nums, int numsSize) {
  int sum = 0;
  for (int i = 0; i < numsSize; ++i) {
    sum ^= i ^ nums[i];
  }
  sum ^= numsSize;

  return sum;
}