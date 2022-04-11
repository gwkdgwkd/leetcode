/*
给定一个整数数组arr，返回arr的最大湍流子数组的长度。
如果比较符号在子数组中的每个相邻元素对之间翻转，则该子数组是湍流子数组 。
更正式地来说，当arr的子数组A[i],A[i+1],...,A[j]满足仅满足下列条件时，我们称其为湍流子数组：
若i <= k < j ：
    当k为奇数时， A[k] > A[k+1]，且
    当k为偶数时，A[k] < A[k+1]；
或若i <= k < j ：
    当k为偶数时，A[k] > A[k+1]，且
    当k为奇数时，A[k] < A[k+1]。

示例1：
输入：arr = [9,4,2,10,7,8,8,1,9]
输出：5
解释：arr[1] > arr[2] < arr[3] > arr[4] < arr[5]

示例2：
输入：arr = [4,8,12,16]
输出：2

示例3：
输入：arr = [100]
输出：1

提示：
1 <= arr.length <= 4 * 104
0 <= arr[i] <= 109
*/

// 动态规划
// 和376的区别：子序列和子数组
int maxTurbulenceSize(int* arr, int arrSize) {
  // dp[i][0]为以arr[i]结尾，且arr[i−1]>arr[i]的湍流子数组的最大长度；
  // dp[i][1]为以arr[i]结尾，且arr[i−1]<arr[i]的湍流子数组的最大长度。
  int dp[arrSize][2];
  memset(dp, 0, sizeof(dp));
  for (int i = 0; i < arrSize; i++) {
    dp[i][0] = dp[i][1] = 1;
  }

  int max = 1;
  for (int i = 1; i < arrSize; ++i) {
    if (arr[i - 1] > arr[i]) {
      dp[i][0] = dp[i - 1][1] + 1;
    } else if (arr[i - 1] < arr[i]) {
      dp[i][1] = dp[i - 1][0] + 1;
    }
    max = fmax(max, fmax(dp[i][0], dp[i][1]));
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

  return max;
}
