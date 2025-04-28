/*
给一个二进制数组nums，需要从中删掉一个元素。
请在删掉元素的结果数组中，返回最长的且只包含1的非空子数组的长度。
如果不存在这样的子数组，请返回0。

提示1：
输入：nums = [1,1,0,1]
输出：3
解释：删掉位置2的数后，[1,1,1]包含3个1。

示例2：
输入：nums = [0,1,1,1,0,1,1,0,1]
输出：5
解释：删掉位置4的数字后，[0,1,1,1,1,1,0,1]的最长全1子数组为[1,1,1,1,1]。

示例3：
输入：nums = [1,1,1]
输出：2
解释：必须要删除一个元素。


提示：
1 <= nums.length <= 10^5
nums[i]要么是0要么是1。
*/

class Solution {
 public:
  int longestSubarray(vector<int>& nums) {
    int n = nums.size();
    int ans = 0;
    int right = 0;
    int left = 0;
    int cnt = 0;
    while (right < n) {
      if (nums[right] != 1) {
        ++cnt;
      }
      while (cnt > 1) {
        if (nums[left++] != 1) {
          --cnt;
        }
      }
      ans = max(ans, right - left);
      right++;
    }
    return ans;
  }
};