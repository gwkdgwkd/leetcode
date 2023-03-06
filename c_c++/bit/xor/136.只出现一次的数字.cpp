/*
给定一个非空整数数组，除了某个元素只出现一次以外，其余每个元素均出现两次。
找出那个只出现了一次的元素。

说明：算法应该具有线性时间复杂度，可以不使用额外空间来实现吗？

示例1:
输入: [2,2,1]
输出: 1

示例2:
输入: [4,1,2,1,2]
输出: 4
*/

// 一个数和它本身做异或运算结果为0，即a^a=0；
// 一个数和0做异或运算的结果为它本身，即a^0=a。
int singleNumber(int* nums, int numsSize) {
  int res = 0;
  for (int i = 0; i < numsSize; ++i) {
    res ^= nums[i];
  }

  return res;
}

class Solution {
 public:
  int singleNumber(vector<int>& nums) {
    int ans = 0;
    for (const int& num : nums) {
      ans ^= num;
    }
    return ans;
  }
};