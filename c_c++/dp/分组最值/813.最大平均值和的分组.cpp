/*
给定数组nums和一个整数k，将给定的数组nums分成最多k个相邻的非空子数组。
分数由每个子数组内的平均值的总和构成，注意必须使用nums数组中的每一个数进行分组，
并且分数不一定需要是整数，返回所能得到的最大分数是多少，误差在10^-6内是正确的。

示例1：
输入：nums = [9,1,2,3,9], k = 3
输出：20.00000
解释：
nums的最优分组是[9],[1, 2, 3],[9]，
得到的分数是9 + (1 + 2 + 3) / 3 + 9 = 20。
我们也可以把nums分成[9, 1], [2], [3, 9]，
这样的分组得到的分数为5 + 2 + 6 = 13,但不是最大值。

示例2：
输入： nums = [1,2,3,4,5,6,7], k = 4
输出： 20.50000
*/

// 动态规划
double largestSumOfAverages(int* nums, int numsSize, int k) {
  // 前缀和，可以快速求出数组某一段的和
  int sum[numsSize + 1];
  memset(sum, 0, sizeof(sum));
  for (int i = 1; i <= numsSize; ++i) {
    sum[i] = sum[i - 1] + nums[i - 1];
  }
  // dp[i][j]用于记录数组前i个元素分成j段平均值和的最大值
  double dp[numsSize + 1][k];
  memset(dp, 0, sizeof(dp));

  for (int i = 1; i <= numsSize; ++i) {
    // 代表着把前i个元素分成1段，平均值和的最大值就是自身的平均值
    dp[i][0] = sum[i] * 1.0 / i;
    // 计算前i个元素分成j[1, k-1]段，注意j不能超过i，因为i个元素最多分成i段
    for (int j = 1; j < k && i > j; ++j) {
      // 把前i个分成j-1段，将[j, i)分成一段
      for (int m = 1; m < i; ++m) {
        // sum[i]-sum[m]计算的是[m, i)和，方程表示把前m个分成k-1段，
        // 最后[m,i)单独看做一段计算的和
        dp[i][j] =
            fmax(dp[i][j], dp[m][j - 1] + (sum[i] - sum[m]) * 1.0 / (i - m));
      }
    }
  }

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
    }
  }

  return dp[numsSize];
}

class Solution {
 public:
  double largestSumOfAverages(vector<int>& nums, int k) {
    int n = nums.size();

    vector<int> presum(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
      presum[i] = presum[i - 1] + nums[i - 1];
    }

    vector<vector<double>> dp(n + 1, vector<double>(k, 0));
    for (int i = 1; i <= n; ++i) {
      dp[i][0] = presum[i] * 1.0 / i;
      for (int j = 1; j < k && i > j; ++j) {
        for (int m = 1; m < i; ++m) {
          dp[i][j] = max(
              dp[i][j], dp[m][j - 1] + (presum[i] - presum[m]) * 1.0 / (i - m));
        }
      }
    }

    return dp[n][k - 1];
  }
};
