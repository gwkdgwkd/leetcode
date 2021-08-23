/*
 * @lc app=leetcode.cn id=978 lang=c
 *
 * [978] 最长湍流子数组
 */

// @lc code=start

// 动态规划
int maxTurbulenceSize(int* arr, int arrSize) {
  // dp[i][0]为以arr[i]结尾，且arr[i−1]>arr[i]的「湍流子数组」的最大长度；
  // dp[i][1]为以arr[i]结尾，且arr[i−1]<arr[i]的「湍流子数组」的最大长度。
  int dp[arrSize][2];
  for (int i = 0; i < arrSize; i++) {
    dp[i][0] = dp[i][1] = 1;
  }

  for (int i = 1; i < arrSize; i++) {
    if (arr[i - 1] > arr[i]) {
      dp[i][0] = dp[i - 1][1] + 1;
    } else if (arr[i - 1] < arr[i]) {
      dp[i][1] = dp[i - 1][0] + 1;
    }
  }

  int ret = 1;
  for (int i = 0; i < arrSize; i++) {
    ret = fmax(ret, dp[i][0]);
    ret = fmax(ret, dp[i][1]);
  }

  // for (int i = 0; i < arrSize; i++) {
  //   printf("%3d ",arr[i]);
  // }
  // printf("\n");
  // for (int i = 0; i < 2; i++) {
  //   for (int j = 0; j < arrSize; j++) {
  //     printf("%3d ",dp[j][i]);
  //   }
  //   printf("\n");
  // }
  //   9   4   2  10   7   8   8   1   9
  //   1   2   2   1   4   1   1   2   1
  //   1   1   1   3   1   5   1   1   3

  return ret;
}
// @lc code=end
