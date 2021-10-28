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

// 贪心算法
int jump(int* nums, int numsSize) {
  int curDistance = 0;   // 当前覆盖的最远距离下标
  int ans = 0;           // 记录走的最大步数
  int nextDistance = 0;  // 下一步覆盖的最远距离下标
  // 注意这里是小于numsSize-1，这是关键所在
  for (int i = 0; i < numsSize - 1; i++) {
    // 更新下一步覆盖的最远距离下标
    nextDistance = fmax(nums[i] + i, nextDistance);
    if (i == curDistance) {        // 遇到当前覆盖的最远距离下标
      curDistance = nextDistance;  // 更新当前覆盖的最远距离下标
      ans++;
    }
  }
  return ans;
}
// @lc code=end
