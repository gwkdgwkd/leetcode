/*
给一个整数数组nums和一个整数k，请你返回nums中好子数组的数目。
一个子数组arr如果有至少k对下标(i, j)满足i < j且arr[i] == arr[j]，
那么称它是一个好子数组。
子数组是原数组中一段连续非空的元素序列。

示例1：
输入：nums = [1,1,1,1,1], k = 10
输出：1
解释：唯一的好子数组是这个数组本身。

示例2：
输入：nums = [3,1,4,3,2,2,4], k = 2
输出：4
解释：总共有4个不同的好子数组：
     [3,1,4,3,2,2]有2对。
     [3,1,4,3,2,2,4]有3对。
     [1,4,3,2,2,4]有2对。
     [4,3,2,2,4]有2对。


提示：
1 <= nums.length <= 10^5
1 <= nums[i], k <= 10^9
*/

class Solution {
 public:
  long long countGood(vector<int>& nums, int k) {
    int n = nums.size();
    int pairs = 0;
    long long ans = 0;
    int right = 0;
    int left = 0;

    unordered_map<int, int> cnt;
    while (right < n) {
      pairs += cnt[nums[right++]]++;
      while (pairs >= k) {
        pairs -= --cnt[nums[left++]];
      }
      ans += left;
    }
    return ans;
  }
};