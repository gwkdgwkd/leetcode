/*
给定一个正整数数组nums和整数k，请找出该数组内乘积小于k的连续的子数组的个数。

示例1：
输入：nums = [10,5,2,6], k = 100
输出：8
解释：8个乘积小于100的子数组分别为：
[10], [5], [2], [6], [10,5], [5,2], [2,6], [5,2,6]。
需要注意的是[10,5,2]并不是乘积小于100的子数组。

示例2：
输入：nums = [1,2,3], k = 0
输出：0

提示：
1 <= nums.length <= 3 * 10^4
1 <= nums[i] <= 1000
0 <= k <= 10^6
*/

// 剑指OfferII009乘积小于K的子数组

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

class Solution {
 public:
  int numSubarrayProductLessThanK(vector<int>& nums, int k) {
    if (k <= 1) {
      return 0;
    }
    int left = 0;
    int right = 0;
    int tmp = 1;
    int res = 0;
    while (right < nums.size()) {
      tmp *= nums[right++];
      while (tmp >= k) {
        tmp /= nums[left++];
      }
      // 右移左端点，那么最右边这个新元素就可以使用了。
      // 实际上就是res加上含新元素子集的个数,那是多啥呢？
      // 新元素（right-1），新元素+前一个...新元素+到最左边元素，即right-left个
      res += right - left;  // right - 1 - left + 1
    }

    return res;
  }
};