/*
给一个下标从0开始的整数数组nums。
如果nums中长度为m的子数组s满足以下条件，我们称它是一个交替子数组：
m大于1。
s1 = s0 + 1。
下标从0开始的子数组s与数组[s0, s1, s0, s1,...,s(m-1) % 2]一样。
也就是说，s1 - s0 = 1，s2 - s1 = -1，s3 - s2 = 1，s4 - s3 = -1，
以此类推，直到s[m - 1] - s[m - 2] = (-1)m。
请返回nums中所有交替子数组中，最长的长度，如果不存在交替子数组，请你返回-1。
子数组是一个数组中一段连续非空的元素序列。

示例 1：
输入：nums = [2,3,4,3,4]
输出：4
解释：交替子数组有[2,3]，[3,4]，[3,4,3] 和 [3,4,3,4]。
     最长的子数组为[3,4,3,4]，长度为4。

示例2：
输入：nums = [4,5,6]
输出：2
解释：[4,5]和[5,6]是仅有的两个交替子数组。它们长度都为2。


提示：
2 <= nums.length <= 100
1 <= nums[i] <= 10^4
*/

class Solution {
 public:
  int alternatingSubarray(vector<int>& nums) {
    int n = nums.size();
    int ans = -1;
    int right = 0;
    while (right < n - 1) {
      if (nums[right + 1] - nums[right] != 1) {
        ++right;
        continue;
      }
      int left = right;
      right += 2;
      while (right < n && nums[right - 2] == nums[right]) {
        ++right;
      }
      ans = max(ans, right - left);
      --right;
    }

    return ans;
  }
};