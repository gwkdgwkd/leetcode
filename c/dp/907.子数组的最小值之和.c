/*
 * @lc app=leetcode.cn id=907 lang=c
 *
 * [907] 子数组的最小值之和
 */

// @lc code=start

/*
// 动态规划，栈溢出
int sumSubarrayMins(int* arr, int arrSize) {
  if (arrSize == 1) {
    return arr[0];
  }
  int dp[arrSize][arrSize];
  memset(dp, 0, sizeof(dp));
  long sum = 0;
  for (int i = 0; i < arrSize; ++i) {
    dp[i][i] = arr[i];
    sum += dp[i][i];
  }

  for (int i = arrSize - 1; i >= 0; --i) {
    for (int j = i + 1; j < arrSize; ++j) {
      dp[i][j] = fmin(dp[i + 1][j], dp[i][j - 1]);
      sum += dp[i][j];
    }
  }

  return sum % 1000000007;
}
*/

// 动态规划，超出时间限制
int sumSubarrayMins(int* arr, int arrSize) {
  if (arrSize == 1) {
    return arr[0];
  }
  int dp[arrSize];
  memset(dp, 0, sizeof(dp));
  long sum = 0;
  for (int i = 0; i < arrSize; ++i) {
    dp[i] = arr[i];
    sum += dp[i];
  }

  for (int i = arrSize - 1; i >= 0; --i) {
    for (int j = i + 1; j < arrSize; ++j) {
      dp[j] = fmin(dp[j], dp[j - 1]);
      sum += dp[j];
    }
  }

  return sum % 1000000007;
}

// @lc code=end
