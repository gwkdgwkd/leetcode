/*
 * @lc app=leetcode.cn id=152 lang=c
 *
 * [152] 乘积最大子数组
 */

// @lc code=start

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

// @lc code=end
