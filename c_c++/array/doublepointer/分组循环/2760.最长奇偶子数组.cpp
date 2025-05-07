/*
给一个下标从0开始的整数数组nums和一个整数threshold。
请从nums的子数组中找出以下标l开头，
下标r结尾(0<=l<=r<nums.length)且满足以下条件的最长子数组：
nums[l] % 2 == 0
对于范围[l, r - 1]内的所有下标i，nums[i] % 2 != nums[i + 1] % 2
对于范围[l, r]内的所有下标i，nums[i] <= threshold
以整数形式返回满足题目要求的最长子数组的长度。
注意：子数组是数组中的一个连续非空元素序列。

示例1：
输入：nums = [3,2,5,4], threshold = 5
输出：3
解释：在这个示例中，我们选择从l=1开始、到r=3结束的子数组=>[2,5,4]，满足上述条件。
     因此，答案就是这个子数组的长度3。可以证明3是满足题目要求的最大长度。

示例2：
输入：nums = [1,2], threshold = 2
输出：1
解释：在这个示例中，我们选择从l=1开始、到r=1结束的子数组=>[2]。
     该子数组满足上述全部条件。可以证明1是满足题目要求的最大长度。

示例3：
输入：nums = [2,3,4,5], threshold = 4
输出：3
解释：在这个示例中，我们选择从l=0开始、到r=2结束的子数组=>[2,3,4]。
     该子数组满足上述全部条件。
     因此，答案就是这个子数组的长度3。可以证明3是满足题目要求的最大长度。


提示：
1 <= nums.length <= 100
1 <= nums[i] <= 100
1 <= threshold <= 100
*/

// 分组循环
class Solution {
 public:
  int longestAlternatingSubarray(vector<int>& nums, int threshold) {
    int n = nums.size();
    int ans = 0;
    int right = 0;
    while (right < n) {
      if (nums[right] > threshold || nums[right] % 2) {
        ++right;
        continue;
      }
      int left = right++;
      while (right < n && nums[right] <= threshold &&
             nums[right] % 2 != nums[right - 1] % 2) {
        ++right;
      }
      ans = max(ans, right - left);
    }
    return ans;
  }
};

// 动态规划
class Solution {
 public:
  int longestAlternatingSubarray(vector<int>& nums, int threshold) {
    int res = 0, dp = 0, n = nums.size();
    for (int l = n - 1; l >= 0; l--) {
      if (nums[l] > threshold) {
        dp = 0;
      } else if (l == n - 1 || nums[l] % 2 != nums[l + 1] % 2) {
        dp++;
      } else {
        dp = 1;
      }
      if (nums[l] % 2 == 0) {
        res = max(res, dp);
      }
    }
    return res;
  }
};
