/*
给你一个整数数组nums，请你找出数组中乘积最大的非空连续子数组，
该子数组中至少包含一个数字，并返回该子数组所对应的乘积。
测试用例的答案是一个32位整数。
子数组是数组的连续子序列。

示例1:
输入: nums = [2,3,-2,4]
输出: 6
解释: 子数组[2,3]有最大乘积6。

示例2:
输入: nums = [-2,0,-1]
输出: 0
解释: 结果不能为2, 因为[-2,-1]不是子数组。

提示:
1 <= nums.length <= 2 * 10^4
-10 <= nums[i] <= 10
nums的任何前缀或后缀的乘积都保证是一个32位整数
*/

// 动态规划
int maxProduct(int* nums, int numsSize) {
  int dp[numsSize][2];
  memset(dp, 0, sizeof(dp));
  dp[0][0] = dp[0][1] = nums[0];

  int max = nums[0];
  for (int i = 1; i < numsSize; ++i) {
    // 前i个元素乘积和最大的值
    dp[i][0] =
        fmax(nums[i], fmax(dp[i - 1][0] * nums[i], dp[i - 1][1] * nums[i]));
    // 前i个元素乘积和最小的值
    dp[i][1] =
        fmin(nums[i], fmin(dp[i - 1][0] * nums[i], dp[i - 1][1] * nums[i]));
    max = fmax(max, dp[i][0]);
  }

  return max;
}

int maxProduct(int* nums, int numsSize) {
  int maxF = nums[0], minF = nums[0], ans = nums[0];
  for (int i = 1; i < numsSize; ++i) {
    int mx = maxF, mn = minF;
    maxF = fmax(mx * nums[i], fmax(nums[i], mn * nums[i]));
    minF = fmin(mn * nums[i], fmin(nums[i], mx * nums[i]));
    ans = fmax(maxF, ans);
  }
  return ans;
}

class Solution {
 public:
  int maxProduct(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> dp(n, vector<int>(2));
    dp[0][0] = nums[0];
    dp[0][1] = nums[0];

    int ans = nums[0];
    for (int i = 1; i < n; ++i) {
      dp[i][0] =
          max(nums[i], max(dp[i - 1][0] * nums[i], dp[i - 1][1] * nums[i]));
      dp[i][1] =
          min(nums[i], min(dp[i - 1][0] * nums[i], dp[i - 1][1] * nums[i]));
      ans = max(ans, dp[i][0]);
    }

    return ans;
  }
};

class Solution {
 public:
  int maxProduct(vector<int>& nums) {
    int n = nums.size();
    int maxNum = nums[0];
    int minNum = nums[0];

    int ans = nums[0];
    for (int i = 1; i < n; ++i) {
      int t1 = max(maxNum * nums[i], minNum * nums[i]);
      int t2 = min(maxNum * nums[i], minNum * nums[i]);
      maxNum = max(nums[i], t1);
      minNum = min(nums[i], t2);
      ans = max(ans, maxNum);
    }

    return ans;
  }
};
