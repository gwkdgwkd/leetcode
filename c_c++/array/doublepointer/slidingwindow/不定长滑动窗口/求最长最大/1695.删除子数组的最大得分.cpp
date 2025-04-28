/*
给一个正整数数组nums，请从中删除一个含有若干不同元素的子数组。
删除子数组的得分就是子数组各元素之和。
返回只删除一个子数组可获得的最大得分。
如果数组b是数组a的一个连续子序列，
即如果它等于a[l],a[l+1],...,a[r]，那么它就是a的一个子数组。

示例1：
输入：nums = [4,2,4,5,6]
输出：17
解释：最优子数组是[2,4,5,6]

示例2：
输入：nums = [5,2,1,2,5,2,1,2,5]
输出：8
解释：最优子数组是[5,2,1]或[1,2,5]


提示：
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^4
*/

class Solution {
 public:
  int maximumUniqueSubarray(vector<int>& nums) {
    int n = nums.size();
    unordered_map<int, int> cnt;
    int right = 0;
    int left = 0;
    int ans = 0;
    int sum = 0;
    while (right < n) {
      int r = nums[right++];
      cnt[r]++;
      sum += r;
      while (cnt.size() < right - left) {
        int l = nums[left++];
        if (--cnt[l] == 0) {
          cnt.erase(l);
        }
        sum -= l;
      }
      ans = max(ans, sum);
    }
    return ans;
  }
};