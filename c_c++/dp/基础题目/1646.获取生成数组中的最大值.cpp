/*
给你一个整数n，按下述规则生成一个长度为n + 1的数组nums：
nums[0] = 0
nums[1] = 1
当2 <= 2 * i <= n时，nums[2 * i] = nums[i]
当2 <= 2 * i + 1 <= n时，nums[2 * i + 1] = nums[i] + nums[i + 1]
返回生成数组nums中的最大值。

示例1：
输入：n = 7
输出：3
解释：根据规则：
  nums[0] = 0
  nums[1] = 1
  nums[(1 * 2) = 2] = nums[1] = 1
  nums[(1 * 2) + 1 = 3] = nums[1] + nums[2] = 1 + 1 = 2
  nums[(2 * 2) = 4] = nums[2] = 1
  nums[(2 * 2) + 1 = 5] = nums[2] + nums[3] = 1 + 2 = 3
  nums[(3 * 2) = 6] = nums[3] = 2
  nums[(3 * 2) + 1 = 7] = nums[3] + nums[4] = 2 + 1 = 3
因此，nums = [0,1,1,2,1,3,2,3]，最大值3

示例2：
输入：n = 2
输出：1
解释：根据规则nums[0]、nums[1]和nums[2]之中的最大值是1

示例3：
输入：n = 3
输出：2
解释：根据规则nums[0]、nums[1]、nums[2]和nums[3]之中的最大值是2

提示：0 <= n <= 100
*/

// 动态规划
int getMaximumGenerated(int n) {
  if (n < 2) {
    return n;
  }
  int dp[n + 1];
  dp[0] = 0;
  dp[1] = 1;
  int ret = 0;
  for (int i = 2; i <= n; ++i) {
    int t = i / 2;
    if (i % 2) {
      dp[i] = dp[t] + dp[t + 1];
    } else {
      dp[i] = dp[t];
    }
    ret = fmax(ret, dp[i]);
  }

  return ret;
}

class Solution {
 public:
  int getMaximumGenerated(int n) {
    if (n < 2) {
      return n;
    }
    vector<int> dp(n + 1, 0);
    dp[0] = 0;
    dp[1] = 1;
    int ans = 0;
    for (int i = 2; i <= n; ++i) {
      int t = i / 2;
      if (i % 2) {
        dp[i] = dp[t] + dp[t + 1];
      } else {
        dp[i] = dp[t];
      }
      ans = max(ans, dp[i]);
    }

    return ans;
  }
};
