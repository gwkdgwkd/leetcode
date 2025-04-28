/*
给一个整数数组nums和一个整数k。
一个元素x在数组中的频率指的是它在数组中的出现次数。
如果一个数组中所有元素的频率都小于等于k，那么我们称这个数组是好数组。
请返回nums中最长好子数组的长度。
子数组指的是一个数组中一段连续非空的元素序列。

示例1：
输入：nums = [1,2,3,1,2,3,1,2], k = 2
输出：6
解释：最长好子数组是[1,2,3,1,2,3]，
     值1，2和3在子数组中的频率都没有超过k = 2。
     [2,3,1,2,3,1]和[3,1,2,3,1,2]也是好子数组。
     最长好子数组的长度为6。

示例2：
输入：nums = [1,2,1,2,1,2,1,2], k = 1
输出：2
解释：最长好子数组是[1,2]，值1和2在子数组中的频率都没有超过k = 1。
     [2,1]也是好子数组。
     最长好子数组的长度为2。

示例3：
输入：nums = [5,5,5,5,5,5,5], k = 4
输出：4
解释：最长好子数组是[5,5,5,5]，值5在子数组中的频率没有超过k = 4。
     最长好子数组的长度为4。


提示：
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
1 <= k <= nums.length
*/

class Solution {
  // 时间复杂度：O(n)，其中n为nums的长度。
  // 空间复杂度：O(n)。
 public:
  int maxSubarrayLength(vector<int>& nums, int k) {
    int n = nums.size();
    unordered_map<int, int> cnt;
    int left = 0;
    int right = 0;
    int ans = 0;

    while (right < n) {
      int r = nums[right++];
      cnt[r]++;
      while (cnt[r] > k) {
        int l = nums[left++];
        --cnt[l];
        // if(--cnt[l] == 0) {
        //     cnt.erase(l);
        // }
      }
      ans = max(ans, right - left);
    }
    return ans;
  }
};