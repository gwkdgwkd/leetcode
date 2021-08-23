/*
 * @lc app=leetcode.cn id=1049 lang=c
 *
 * [1049] 最后一块石头的重量 II
 */

// @lc code=start

/*
// 动态规划，0-1背包问题
int lastStoneWeightII(int* stones, int stonesSize) {
  int sum = 0;
  for (int i = 0; i < stonesSize; ++i) {
    sum += stones[i];
  }
  int target = sum / 2;  // 想到这个是难点
  int dp[stonesSize + 1][target + 1];
  memset(dp, 0, sizeof(dp));
  for (int i = 1; i <= stonesSize; ++i) {
    for (int j = 0; j <= target; ++j) {
      if (stones[i - 1] > j) {
        dp[i][j] = dp[i - 1][j];
      } else {
        dp[i][j] =
            fmax(dp[i - 1][j], dp[i - 1][j - stones[i - 1]] + stones[i - 1]);
      }
    }
  }

  // for(int i = 0; i <= stonesSize; ++i) {
  //   for(int j = 0; j <= target; ++j) {
  //       printf("%3d ", dp[i][j]);
  //   }
  //   printf("\n");
  // }

  return sum - 2 * dp[stonesSize][target];
}
*/

// 动态规划，一维dp
int lastStoneWeightII(int* stones, int stonesSize) {
  int sum = 0;
  for (int i = 0; i < stonesSize; ++i) {
    sum += stones[i];
  }
  int target = sum / 2;
  int dp[target + 1];
  memset(dp, 0, sizeof(dp));
  for (int i = 1; i <= stonesSize; ++i) {
    for (int j = target; j >= stones[i - 1]; --j) {
      dp[j] = fmax(dp[j], dp[j - stones[i - 1]] + stones[i - 1]);
    }
  }

  return sum - 2 * dp[target];
}

// @lc code=end
