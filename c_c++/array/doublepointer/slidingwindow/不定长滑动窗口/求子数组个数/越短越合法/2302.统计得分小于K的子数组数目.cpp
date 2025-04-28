/*
一个数组的分数定义为数组之和乘以数组的长度。
比方说，[1, 2, 3, 4, 5]的分数为(1 + 2 + 3 + 4 + 5) * 5 = 75。
正整数数组nums和一个整数k，请返回nums中分数严格小于k的非空整数子数组数目。
子数组是数组中的一个连续元素序列。

示例1：
输入：nums = [2,1,4,3,5], k = 10
输出：6
解释：有6个子数组的分数小于10：
     [2]分数为2 * 1 = 2。
     [1]分数为1 * 1 = 1。
     [4]分数为4 * 1 = 4。
     [3]分数为3 * 1 = 3。
     [5]分数为5 * 1 = 5。
     [2,1]分数为(2 + 1) * 2 = 6。
     注意，子数组[1,4]和[4,3,5]不符合要求，
     因为它们的分数分别为10和36，但要求子数组的分数严格小于10。

示例2：
输入：nums = [1,1,1], k = 5
输出：5
解释：除了[1,1,1]以外每个子数组分数都小于5。
     [1,1,1]分数为(1 + 1 + 1) * 3 = 9，大于5。
     所以总共有5个子数组得分小于5。


提示：
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^5
1 <= k <= 10^15
*/

class Solution {
 public:
  long long countSubarrays(vector<int>& nums, long long k) {
    int n = nums.size();
    long long sum = 0;
    long long ans = 0;
    int left = 0;
    int right = 0;
    while (right < n) {
      sum += nums[right++];
      while (sum * (right - left) >= k) {
        sum -= nums[left++];
      }
      ans += right - left;
    }
    return ans;
  }
};