/*
给你一个整数数组nums，除某个元素仅出现一次外，其余每个元素都恰出现三次。
请你找出并返回那个只出现了一次的元素。

示例1：
输入：nums = [2,2,3,2]
输出：3

示例2：
输入：nums = [0,1,0,1,0,1,100]
输出：100

提示：
1 <= nums.length <= 3 * 10^4
-2^31 <= nums[i] <= 2^31 - 1
nums中，除某个元素仅出现一次外，其余每个元素都恰出现三次

进阶：你的算法应该具有线性时间复杂度。你可以不使用额外空间来实现吗？

注意：本题与137题相同
*/

int singleNumber(int* nums, int numsSize) {
  int res = 0;
  for (int i = 0; i < 32; ++i) {
    int total = 0;
    for (int j = 0; j < numsSize; ++j) {
      total += (nums[j] >> i) & 1;
    }

    if (total % 3) {
      res |= (1u << i);
    }
  }

  return res;
}