/*
给定一个含有n个正整数的数组和一个正整数target。
找出该数组中满足其总和大于等于target的长度最小的
[numsl,numsl+1, ..., numsr-1, numsr]，并返回其长度。
如果不存在符合条件的子数组，返回0。

示例1：

输入：target = 7, nums = [2,3,1,2,4,3]
输出：2
解释：子数组[4,3]是该条件下的长度最小的子数组。

示例2：
输入：target = 4, nums = [1,4,4]
输出：1

示例3：
输入：target = 11, nums = [1,1,1,1,1,1,1,1]
输出：0


提示：
1 <= target <= 10^9
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^4
*/

class Solution {
 public:
  int minSubArrayLen(int target, vector<int>& nums) {
    int n = nums.size();
    int right = 0;
    int left = 0;
    int ans = n + 1;
    int sum = 0;
    while (right < n) {
      sum += nums[right++];
      while (sum >= target) {
        ans = min(ans, right - left);
        sum -= nums[left++];
      }
    }
    return ans == n + 1 ? 0 : ans;
  }
};