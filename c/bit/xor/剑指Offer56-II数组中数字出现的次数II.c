/*
在一个数组nums中除一个数字只出现一次之外，其他数字都出现了三次。
请找出那个只出现一次的数字。

示例1：
输入：nums = [3,4,3,3]
输出：4

示例2：
输入：nums = [9,1,7,9,7,9,7]
输出：1

限制：
1 <= nums.length <= 10000
1 <= nums[i] < 2^31
*/

int singleNumber(int* nums, int numsSize) {
  int ans = 0;

  for (int i = 0; i < 32; ++i) {
    int total = 0;
    for (int j = 0; j < numsSize; ++j) {
      total += (nums[j] >> i) & 1;
    }

    if (total % 3) {
      ans |= (1u << i);
    }
  }

  return ans;
}
