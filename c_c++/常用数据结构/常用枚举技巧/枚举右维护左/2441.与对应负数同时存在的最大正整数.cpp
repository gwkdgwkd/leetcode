/*
给一个不包含任何零的整数数组nums，找出自身与对应的负数都在数组中存在的最大正整数k。
返回正整数k，如果不存在这样的整数，返回-1。

示例1：
输入：nums = [-1,2,-3,3]
输出：3
解释：3是数组中唯一一个满足题目要求的k。

示例2：
输入：nums = [-1,10,6,7,-7,1]
输出：7
解释：数组中存在1和7对应的负数，7的值更大。

示例3：
输入：nums = [-10,8,6,7,-2,-3]
输出：-1
解释：不存在满足题目要求的k，返回-1。


提示：
1 <= nums.length <= 1000
-1000 <= nums[i] <= 1000
nums[i] != 0
*/

class Solution {
 public:
  int findMaxK(vector<int>& nums) {
    int ans = -1;
    unordered_set<int> s;
    for (auto num : nums) {
      if (s.count(-num)) {
        ans = max(ans, abs(num));
      }
      s.insert(num);
    }
    return ans;
  }
};
