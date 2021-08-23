/*
 * @lc app=leetcode.cn id=983 lang=c
 *
 * [983] 最低票价
 */

// @lc code=start

// 动态规划
int mincostTickets(int* days, int daysSize, int* costs, int costsSize) {
  int dp[366] = {0};
  int index = 0;

  for (int i = 1; i <= 365; i++) {
    if (i == days[index]) {  // 第i天有出行计划
      dp[i] = dp[i - 1] + costs[0];
      dp[i] = dp[i] < (dp[(i >= 7 ? (i - 7) : 0)] + costs[1])
                  ? dp[i]
                  : (dp[(i >= 7 ? (i - 7) : 0)] + costs[1]);
      dp[i] = dp[i] < (dp[(i >= 30 ? (i - 30) : 0)] + costs[2])
                  ? dp[i]
                  : (dp[(i >= 30 ? (i - 30) : 0)] + costs[2]);
      if (index < daysSize - 1) {  // 之后还有出行计划
        index++;
      } else {
        return dp[i];  // 之后没有出行计划就直接返回，后面就不用计算了
      }
    } else {
      dp[i] = dp[i - 1];
    }
  }
  return dp[days[daysSize - 1]];
}

// @lc code=end
