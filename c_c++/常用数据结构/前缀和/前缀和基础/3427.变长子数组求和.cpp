/*
给一个长度为n的整数数组nums。
对于每个下标i（0<=i<n），定义对应的子数组nums[start...i]（start=max(0,
i-nums[i])）。 返回为数组中每个下标定义的子数组中所有元素的总和。
子数组是数组中的一个连续、非空的元素序列。

示例1：
输入：nums = [2,3,1]
输出：11
解释：下标i子数组和
     0	nums[0]       = [2]	    2
     1	nums[0 ... 1] = [2, 3]	5
     2	nums[1 ... 2] = [3, 1]	4
     总和为11。因此，输出11。

示例2：
输入：nums = [3,1,1,2]
输出：13
解释：下标i子数组和
     0	nums[0]       = [3]	        3
     1	nums[0 ... 1] = [3, 1]	    4
     2	nums[1 ... 2] = [1, 1]	    2
     3	nums[1 ... 3] = [1, 1, 2]	4
     总和为13。因此，输出为13。


提示：
1 <= n == nums.length <= 100
1 <= nums[i] <= 1000
*/

// 暴力
class Solution {
 public:
  int subarraySum(vector<int>& nums) {
    int ans = 0;
    for (int i = 0; i < nums.size(); i++) {
      for (int j = max(i - nums[i], 0); j <= i; j++) {
        ans += nums[j];
      }
    }
    return ans;
  }
};

// 前缀和
class Solution {
 public:
  int subarraySum(vector<int>& nums) {
    int n = nums.size();
    vector<int> pre(n + 1);

    // partial_sum(nums.begin(), nums.end(), pre.begin() + 1);
    for (int i = 0; i < n; ++i) {
      pre[i + 1] = pre[i] + nums[i];
    }

    int ans = 0;
    for (int i = 0; i < n; ++i) {
      int l = max(0, i - nums[i]);
      int r = i + 1;
      ans += pre[r] - pre[l];
    }

    return ans;
  }
};

// 差分数组
class Solution {
 public:
  int subarraySum(vector<int>& nums) {
    int n = nums.size();
    vector<int> diff(n + 1);
    for (int i = 0; i < n; i++) {
      diff[max(i - nums[i], 0)]++;
      diff[i + 1]--;
    }

    int ans = 0, sd = 0;
    for (int i = 0; i < n; i++) {
      sd += diff[i];
      ans += nums[i] * sd;
    }
    return ans;
  }
};
