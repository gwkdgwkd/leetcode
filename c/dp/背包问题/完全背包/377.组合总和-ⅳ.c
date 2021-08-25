/*
 * @lc app=leetcode.cn id=377 lang=c
 *
 * [377] 组合总和 Ⅳ
 */

// @lc code=start

// 求装满背包有⼏种⽅法，递归公式都是⼀样的，没有什么差别，但关键在于遍历顺序！
// 本题与518.零钱兑换II就是⼀个鲜明的对⽐，⼀个是求排列，⼀个是求组合，遍历顺序完全不同。
// 如果本题要把排列都列出来的话，只能使⽤回溯算法爆搜。

// 完全背包，装满的排列数
int combinationSum4(int* nums, int numsSize, int target) {
  unsigned int dp[target + 1];
  memset(dp, 0, sizeof(dp));
  dp[0] = 1;

  for (int j = 0; j <= target; ++j) {
    for (int i = 0; i < numsSize; ++i) {
      if (j >= nums[i]) {
        dp[j] += dp[j - nums[i]];
      }
    }
  }

  return dp[target];
}

// @lc code=end
