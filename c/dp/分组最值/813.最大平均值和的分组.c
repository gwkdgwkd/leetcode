/*
 * @lc app=leetcode.cn id=813 lang=c
 *
 * [813] 最大平均值和的分组
 */

// @lc code=start

// 动态规划
double largestSumOfAverages(int* nums, int numsSize, int k) {
  // 前缀和，可以快速求出数组某一段的和
  int sum[numsSize + 1];
  memset(sum, 0, sizeof(sum));
  for (int i = 1; i <= numsSize; ++i) {
    sum[i] = sum[i - 1] + nums[i - 1];
  }
  // dp[i][k]用于记录A数组前i个元素分成k段平均值和的最大值
  double dp[numsSize + 1][k];
  memset(dp, 0, sizeof(dp));

  for (int i = 1; i <= numsSize; ++i) {
    // 代表着把前i个元素分成1段，平均值和的最大值就是自身的平均值
    dp[i][0] = sum[i] * 1.0 / i;
    // 计算前i个元素分成j[1, k-1]段（注意j不能超过i，因为i个元素最多分成i段）
    for (int j = 1; j < k && i > j; ++j) {
      // 把前i个分成j-1段，将[j, i)分成一段
      for (int m = 1; m < i; ++m) {
        // sum[i]-sum[m]计算的是[m, i）和，方程表示把前m个分成k-1段，最后[m, i)单独看做一段计算的和
        dp[i][j] =
            fmax(dp[i][j], dp[m][j - 1] + (sum[i] - sum[m]) * 1.0 / (i - m));
      }
    }
  }

  // for (int i = 0; i <= numsSize; ++i) {
  //   printf("%d ", sum[i]);
  // }
  // printf("\n");
  // for (int j = 0; j < k; ++j) {
  //   for (int i = 0; i <= numsSize; ++i) {
  //     printf("%f ", dp[i][j]);
  //   }
  //   printf("\n");
  // }
  // [9,1,2,3,9] 3
  // sum
  // 0 9 10 12 15 24
  // dp
  // 0.000000 9.000000 5.000000 4.000000 3.750000 4.800000
  // 0.000000 0.000000 10.000000 10.500000 11.000000 12.750000
  // 0.000000 0.000000 0.000000 12.000000 13.500000 20.000000

  return dp[numsSize][k - 1];
}

// 压缩dp，滚动数组
double largestSumOfAverages(int* nums, int numsSize, int k) {
  int sum[numsSize + 1];
  memset(sum, 0, sizeof(sum));
  for (int i = 1; i <= numsSize; ++i) {
    sum[i] = sum[i - 1] + nums[i - 1];
  }
  double dp[numsSize + 1];
  memset(dp, 0, sizeof(dp));

  for (int j = 0; j < k; ++j) {
    for (int i = numsSize; i > 0; --i) {
      if (j == 0) {
        dp[i] = sum[i] * 1.0 / i;
      } else {
        for (int m = 1; m < i; ++m) {
          dp[i] = fmax(dp[i], dp[m] + (sum[i] - sum[m]) * 1.0 / (i - m));
        }
      }
      // printf("%f ", dp[i]);
    }
    // printf("\n");
  }

  // 4.800000 3.750000 4.000000 5.000000 9.000000
  // 12.750000 11.000000 10.500000 10.000000 9.000000
  // 20.000000 13.500000 12.000000 10.000000 9.000000

  return dp[numsSize];
}

// @lc code=end
