/*
数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。
你可以假设数组是非空的，并且给定的数组总是存在多数元素。

示例1:
输入: [1, 2, 3, 2, 2, 2, 5, 4, 2]
输出: 2

限制：1 <= 数组长度 <= 50000

注意：本题与169题相同
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