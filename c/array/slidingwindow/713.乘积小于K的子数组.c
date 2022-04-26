/*
给定一个正整数数组nums和整数k。
请找出该数组内乘积小于k的连续的子数组的个数。

示例1:
输入: nums = [10,5,2,6], k = 100
输出: 8
解释: 8个乘积小于100的子数组分别为: 
[10], [5], [2], [6], [10,5], [5,2], [2,6], [5,2,6]。
需要注意的是[10,5,2]并不是乘积小于100的子数组。

示例2:
输入: nums = [1,2,3], k = 0
输出: 0

提示: 
1 <= nums.length <= 3 * 10^4
1 <= nums[i] <= 1000
0 <= k <= 10^6
*/

int numSubarrayProductLessThanK(int* nums, int numsSize, int k) {
  if (1 >= k) return 0;

  int count = 0;
  int left = 0;
  int right = 0;
  int tmp = 1;
  while (right < numsSize) {
    tmp *= nums[right++];
    while (tmp >= k) {
      tmp /= nums[left++];
    }
    count += right - left;
  }

  return count;
}