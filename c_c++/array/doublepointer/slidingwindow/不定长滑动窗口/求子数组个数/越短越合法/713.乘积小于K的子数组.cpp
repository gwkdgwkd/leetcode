/*
给一个整数数组nums和一个整数k，
请你返回子数组内所有元素的乘积严格小于k的连续子数组的数目。

示例1：
输入：nums = [10,5,2,6], k = 100
输出：8
解释：8个乘积小于100的子数组分别为：
     [10]、[5]、[2]、[6]、[10,5]、[5,2]、[2,6]、[5,2,6]。
     需要注意的是[10,5,2]并不是乘积小于100的子数组。

示例2：
输入：nums = [1,2,3], k = 0
输出：0


提示:
1 <= nums.length <= 3 * 10^4
1 <= nums[i] <= 1000
0 <= k <= 10^6
*/

class Solution {
 public:
  int numSubarrayProductLessThanK(vector<int>& nums, int k) {
    if (k <= 1) {
      return 0;
    }
    int n = nums.size();
    int sum = 1;
    int left = 0;
    int right = 0;
    int ans = 0;
    while (right < n) {
      sum *= nums[right++];
      while (sum >= k) {
        sum /= nums[left++];
      }
      ans += right - left;
    }
    return ans;
  }
};