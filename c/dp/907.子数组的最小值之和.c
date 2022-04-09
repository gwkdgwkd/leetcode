/*
给定一个整数数组arr，找到min(b)的总和，其中b的范围为arr的每个（连续）子数组。
由于答案可能很大，因此返回答案模10^9 + 7。

示例1：
输入：arr = [3,1,2,4]
输出：17
解释：
子数组为[3]，[1]，[2]，[4]，[3,1]，[1,2]，[2,4]，[3,1,2]，[1,2,4]，[3,1,2,4]。
最小值为3，1，2，4，1，1，2，1，1，1，和为17。

示例2：
输入：arr = [11,81,94,43,3]
输出：444

提示：
1 <= arr.length <= 3 * 104
1 <= arr[i] <= 3 * 104
*/

// 动态规划，栈溢出
int sumSubarrayMins(int* arr, int arrSize) {
  if (arrSize == 1) {
    return arr[0];
  }
  // dp[i][j]表示从i到j的子数组中的最小值
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