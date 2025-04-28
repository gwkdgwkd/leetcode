/*
给一个整数数组nums，请返回长度为3的子数组的数量，
满足第一个数和第三个数的和恰好为第二个数的一半。
子数组指的是一个数组中连续非空的元素序列。

示例1：
输入：nums = [1,2,1,4,1]
输出：1
解释：只有子数组[1,4,1]包含3个元素且第一个和第三个数字之和是中间数字的一半。

示例2：
输入：nums = [1,1,1]
输出：0
解释：[1,1,1]是唯一长度为3的子数组，但第一个数和第三个数的和不是第二个数的一半。


提示：
3 <= nums.length <= 100
-100 <= nums[i] <= 100
*/

class Solution {
  // 时间复杂度：O(n)，其中n是 nums的长度。
  // 空间复杂度：O(1)。
 public:
  int countSubarrays(vector<int>& nums) {
    int ans = 0;
    for (int i = 2; i < nums.size(); ++i) {
      if ((nums[i - 2] + nums[i]) * 2 == nums[i - 1]) {
        ++ans;
      }
    }
    return ans;
  }
};