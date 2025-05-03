/*
给一个下标从0 开始、长度为n的整数数组nums，
和两个整数lower和upper，返回公平数对的数目。
如果(i, j)数对满足以下情况，则认为它是一个公平数对：
0 <= i < j < n，且lower <= nums[i] + nums[j] <= upper

示例1：
输入：nums = [0,1,7,4,4,5], lower = 3, upper = 6
输出：6
解释：共计6个公平数对：(0,3)、(0,4)、(0,5)、(1,3)、(1,4)和(1,5)。

示例2：
输入：nums = [1,7,9,2,5], lower = 11, upper = 11
输出：1
解释：只有单个公平数对：(2,3)。


提示：
1 <= nums.length <= 10^5
nums.length == n
-10^9 <= nums[i] <= 10^9
-10^9 <= lower <= upper <= 10^9
*/

class Solution {
 public:
  long long countFairPairs(vector<int>& nums, int lower, int upper) {
    sort(nums.begin(), nums.end());
    auto count = [&nums](int upper) {
      long long ans = 0;
      int left = 0;
      int right = nums.size() - 1;
      while (left < right) {
        if (nums[left] + nums[right] <= upper) {
          ans += right - left;
          ++left;
        } else {
          --right;
        }
      }
      return ans;
    };

    return count(upper) - count(lower - 1);
  }
};