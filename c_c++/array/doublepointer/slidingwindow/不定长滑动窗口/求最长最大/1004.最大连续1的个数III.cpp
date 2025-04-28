/*
给定一个二进制数组nums和一个整数k，假设最多可以翻转k个0，
则返回执行操作后数组中连续1的最大个数。

示例1：
输入：nums = [1,1,1,0,0,0,1,1,1,1,0], K = 2
输出：6
解释：[1,1,1,0,0,1,1,1,1,1,1]
     粗体数字从0翻转到1，最长的子数组长度为6。

示例2：
输入：nums = [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], K = 3
输出：10
解释：[0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1]
     粗体数字从0翻转到1，最长的子数组长度为10。


提示：
1 <= nums.length <= 10^5
nums[i]不是0就是1
0 <= k <= nums.length
*/

class Solution {
 public:
  int longestOnes(vector<int>& nums, int k) {
    int n = nums.size();
    int ans = 0;
    int cnt = 0;
    int left = 0;
    int right = 0;
    while (right < n) {
      if (nums[right++] == 0) {
        ++cnt;
      }
      while (cnt > k) {
        if (nums[left++] == 0) {
          --cnt;
        }
      }
      ans = max(ans, right - left);
    }
    return ans;
  }
};