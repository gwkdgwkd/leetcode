/*
数组中占比超过一半的元素称之为主要元素。
给你一个整数数组，找出其中的主要元素。若没有，返回-1。
请设计时间复杂度为O(N) 、空间复杂度为O(1)的解决方案。

示例1：
输入：[1,2,5,9,5,9,5,5,5]
输出：5

示例2：
输入：[3,2]
输出：-1

示例3：
输入：[2,2,1,1,1,2,2]
输出：2
*/

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