/*
 * @lc app=leetcode.cn id=1911 lang=c
 *
 * [1911] 最大子序列交替和
 */

// @lc code=start
/*
// 动态规划，模拟股票交易
long long maxAlternatingSum(int* nums, int numsSize) {
  long ans = 0;
  int pre = 0;
  for (int i = 0; i < numsSize; i++) {
    if (nums[i] > pre) {  // 价格比原先买入价格高，就卖出一股，并买入
      ans += nums[i] - pre;
      pre = nums[i];
    } else {
      pre = nums[i];  // 如果遇到价格更低的，则换成该天买入
    }
  }
  return ans;
}
*/

long long maxAlternatingSum(int* nums, int numsSize) {
  // dp[i][0]表示前i个数中长为偶数的子序列的最大交替和；
  // dp[i][1]表示前i个数中长为奇数的子序列的最大交替和。
  long long dp[numsSize][2];
  memset(dp, 0, sizeof(dp));
  dp[0][0] = nums[0];
  dp[0][1] = INT_MIN;

  for (int i = 1; i < numsSize; ++i) {
    dp[i][0] = fmax(dp[i - 1][0], fmax(nums[i], dp[i - 1][1] + nums[i]));
    dp[i][1] = fmax(dp[i - 1][1], dp[i - 1][0] - nums[i]);
  }

  return dp[numsSize - 1][0];
}

// 动态规划
long long maxAlternatingSum(int* nums, int numsSize) {
  long long dp[2] = {0};
  dp[0] = nums[0];
  dp[1] = INT_MIN;
  long long temp = 0;
  for (int i = 1; i < numsSize; i++) {
    temp = dp[0];
    dp[0] = fmax(dp[0], fmax(nums[i], (dp[1] + nums[i])));
    dp[1] = fmax(dp[1], temp - nums[i]);
  };
  return dp[0];
}

// @lc code=end
