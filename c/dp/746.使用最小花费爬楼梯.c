/*
 * @lc app=leetcode.cn id=746 lang=c
 *
 * [746] 使用最小花费爬楼梯
 */

// @lc code=start

/*
// 动态规划
int minCostClimbingStairs(int* cost, int costSize) {
  int dp[costSize + 1];
  dp[0] = dp[1] = 0;
  for (int i = 2; i <= costSize; ++i) {
    dp[i] = fmin(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
  }

  for (int i = 0; i <= costSize; ++i) {
    printf("%3d ", dp[i]);
  }
  printf("\n");
  // [1, 100, 1, 1, 1, 100, 1, 1, 100, 1]
  // 0   0   1   2   2   3   3   4   4   5   6

  return dp[costSize];
}
*/

int minCostClimbingStairs(int* cost, int costSize) {
  int pre = 0;
  int curr = 0;
  for (int i = 2; i <= costSize; ++i) {
    int tmp = fmin(curr + cost[i - 1], pre + cost[i - 2]);
    pre = curr;
    curr = tmp;
  }

  return curr;
}

// @lc code=end
