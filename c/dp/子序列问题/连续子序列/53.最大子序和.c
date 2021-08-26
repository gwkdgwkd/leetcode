/*
 * @lc app=leetcode.cn id=53 lang=c
 *
 * [53] 最大子序和
 */

// @lc code=start

int maxSubArray(int* nums, int numsSize) {
  // dp[i]：包括下标i之前的最⼤连续⼦序列和为dp[i]
  int dp[numsSize];
  memset(dp, 0, sizeof(dp));
  int max = dp[0] = nums[0];

  for (int i = 1; i < numsSize; ++i) {
    // dp[i]只有两个⽅向可以推出来：
    //  dp[i-1]+nums[i]，即：nums[i]加⼊当前连续⼦序列和
    //  nums[i]，即：从头开始计算当前连续⼦序列和
    dp[i] = fmax(dp[i - 1] + nums[i], nums[i]);
    max = fmax(max, dp[i]);
  }

  return max;
}

// 时间复杂度：O(N)
// 空间复杂度：O(N)

/*
// 官方题解
int maxSubArray(int* nums, int numsSize) {
  int pre = 0, maxAns = nums[0];
  for (int i = 0; i < numsSize; i++) {
    pre = fmax(pre + nums[i], nums[i]);
    maxAns = fmax(maxAns, pre);
  }
  return maxAns;
}

// 时间复杂度：O(N)
// 空间复杂度：O(1)
*/

// @lc code=end
