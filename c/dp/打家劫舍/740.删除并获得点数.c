/*
 * @lc app=leetcode.cn id=740 lang=c
 *
 * [740] 删除并获得点数
 */

// @lc code=start

// 动态规划，和打家劫舍相似
int deleteAndEarn(int* nums, int numsSize) {
  if (numsSize == 1) {
    return nums[0];
  }
  int max = 0;
  for (int i = 0; i < numsSize; ++i) {
    max = fmax(max, nums[i]);
  }

  int sum[max + 1];
  memset(sum, 0, sizeof(sum));
  for (int i = 0; i < numsSize; ++i) {
    sum[nums[i]] += nums[i];
  }

  int dp[max + 1];  // 可以压缩
  memset(dp, 0, sizeof(dp));
  dp[0] = sum[0];
  dp[1] = fmax(sum[0], sum[1]);
  for (int i = 2; i <= max; ++i) {
    dp[i] = fmax(dp[i - 1], dp[i - 2] + sum[i]);
  }
  // for (int i = 0; i <= max; ++i) {
  //   printf("%d ", sum[i]);
  // }
  // printf("\n");
  // for (int i = 0; i <= max; ++i) {
  //   printf("%d ", dp[i]);
  // }
  // printf("\n");
  // [2,2,3,3,3,4]
  // 0 0 4 9 4
  // 0 0 4 9 9

  return dp[max];
}

// @lc code=end
