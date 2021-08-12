/*
 * @lc app=leetcode.cn id=45 lang=c
 *
 * [45] 跳跃游戏 II
 */

// @lc code=start

/*
// 动态规划
int jump(int* nums, int numsSize) {
  int dp[numsSize];
  dp[0] = 0;
  for (int i = 1; i < numsSize; ++i) {
    dp[i] = numsSize + 1;
  }

  for (int i = 1; i < numsSize; ++i) {
    for (int j = 0; j < i; ++j) {
      if (j + nums[j] >= i) {
        dp[i] = fmin(dp[i], dp[j] + 1);
      }
    }
  }

  return dp[numsSize - 1];
}
*/

// 贪心算法
int jump(int* nums, int numsSize) {
  int longest = 0, step = 0, pre = 0;

  for (int i = 0; i < numsSize - 1; ++i) {
    longest = fmax(longest, nums[i] + i);
    if (i == pre) {
      ++step;
      pre = longest;
    }
  }

  return step;
}

// 时间复杂度：O(n)
// 空间复杂度：O(1)

// @lc code=end
