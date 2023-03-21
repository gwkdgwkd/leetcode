/*
给定一个未排序的整数数组nums，返回最长递增子序列的个数。
注意这个数列必须是严格递增的。

示例1：
输入：[1,3,5,4,7]
输出：2
解释：有两个最长递增子序列，分别是[1, 3, 4, 7]和[1, 3, 5, 7]。

示例2：
输入：[2,2,2,2,2]
输出：5
解释：最长递增子序列的长度是1，并且存在5个子序列的长度为1，因此输出5。

提示：
1 <= nums.length <= 2000
-10^6 <= nums[i] <= 10^6
*/

// 动态规划，与[300.最长递增子序列]相似
int findNumberOfLIS(int* nums, int numsSize) {
  if (numsSize == 1) {
    return numsSize;
  }

  int dp[numsSize];
  int count[numsSize];
  for (int i = 0; i < numsSize; ++i) {
    dp[i] = 1;
    count[i] = 1;
  }
  int max = 0;
  for (int i = 1; i < numsSize; ++i) {
    for (int j = 0; j < i; ++j) {
      if (nums[i] > nums[j]) {
        if (dp[j] + 1 > dp[i]) {
          count[i] = count[j];
        } else if (dp[j] + 1 == dp[i]) {
          count[i] += count[j];
        }
        dp[i] = fmax(dp[i], dp[j] + 1);
      }
      max = fmax(max, dp[i]);  // 放到if里面也行
    }
  }

  int ret = 0;
  for (int i = 0; i < numsSize; ++i) {
    if (max == dp[i]) {
      ret += count[i];
    }
  }

  return ret;
}

class Solution {
 public:
  int findNumberOfLIS(vector<int>& nums) {
    int n = nums.size();

    vector<int> dp(n, 1);
    vector<int> count(n, 1);
    int max = 1;
    for (int i = 1; i < n; ++i) {
      for (int j = 0; j < i; ++j) {
        if (nums[i] > nums[j]) {
          if (dp[j] + 1 > dp[i]) {
            count[i] = count[j];
          } else if (dp[j] + 1 == dp[i]) {
            count[i] += count[j];
          }

          dp[i] = std::max(dp[i], dp[j] + 1);
        }
        max = std::max(max, dp[i]);
      }
    }

    int ret = 0;
    for (int i = 0; i < n; ++i) {
      if (max == dp[i]) {
        ret += count[i];
      }
    }

    return ret;
  }
};
