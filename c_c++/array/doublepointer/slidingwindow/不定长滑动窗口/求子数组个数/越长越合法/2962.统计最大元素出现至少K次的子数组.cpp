/*
给一个整数数组nums和一个正整数k。
请统计有多少满足nums中的最大元素至少出现k次的子数组，
并返回满足这一条件的子数组的数目。
子数组是数组中的一个连续元素序列。

示例1：
输入：nums = [1,3,2,3,3], k = 2
输出：6
解释：包含元素3至少2次的子数组为：
     [1,3,2,3]、[1,3,2,3,3]、[3,2,3]、[3,2,3,3]、[2,3,3]和[3,3]。

示例2：
输入：nums = [1,4,2,1], k = 3
输出：0
解释：没有子数组包含元素4至少3次。


提示：
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^6
1 <= k <= 10^5
*/

class Solution {
 public:
  long long countSubarrays(vector<int>& nums, int k) {
    int m = *max_element(nums.begin(), nums.end());
    int n = nums.size();

    int cnt = 0;
    int right = 0;
    int left = 0;
    long long ans = 0;
    while (right < n) {
      if (nums[right++] == m) {
        ++cnt;
      }
      while (cnt == k) {
        if (nums[left++] == m) {
          --cnt;
        }
      }
      ans += left;
    }

    return ans;
  }
};