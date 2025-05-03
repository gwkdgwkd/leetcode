/*
给一个整数数组nums和一个整数k。
如果某个连续子数组中恰好有k个奇数数字，我们就认为这个子数组是优美子数组。
请返回这个数组中优美子数组的数目。

示例1：
输入：nums = [1,1,2,1,1], k = 3
输出：2
解释：包含3个奇数的子数组是[1,1,2,1]和[1,2,1,1]。

示例2：
输入：nums = [2,4,6], k = 1
输出：0
解释：数列中不包含任何奇数，所以不存在优美子数组。

示例3：
输入：nums = [2,2,2,1,2,2,1,2,2,2], k = 2
输出：16


提示：
1 <= nums.length <= 50000
1 <= nums[i] <= 10^5
1 <= k <= nums.length
*/

class Solution {
 public:
  int numberOfSubarrays(vector<int>& nums, int k) {
    int n = nums.size();
    int l1 = 0, l2 = 0;
    int r = 0;
    int c1 = 0, c2 = 0;
    int ans = 0;
    while (r < n) {
      c1 += nums[r] % 2;
      while (c1 >= k) {
        c1 -= nums[l1++] % 2;
      }
      c2 += nums[r] % 2;
      while (c2 >= k + 1) {
        c2 -= nums[l2++] % 2;
      }
      ans += l1 - l2;
      ++r;
    }
    return ans;
  }
};

class Solution {
 public:
  int numberOfSubarrays(vector<int>& nums, int k) {
    int n = nums.size();
    int l1 = 0, l2 = 0;
    int r = 0;
    int c1 = 0, c2 = 0;
    int ans = 0;
    while (r < n) {
      c1 += nums[r] % 2;
      while (c1 > k) {
        c1 -= nums[l1++] % 2;
      }
      c2 += nums[r] % 2;
      while (c2 > k - 1) {
        c2 -= nums[l2++] % 2;
      }
      ++r;
      ans += l2 - l1;  // (r - l1) - (r - l2)
    }
    return ans;
  }
};