/*
给定一个正整数n，你可以做如下操作：
如果n是偶数，则用n/2替换n。
如果n是奇数，则可以用n+1或n-1替换n。
返回n变为1所需的最小替换次数。

示例1：
输入：n = 8
输出：3
解释：8 -> 4 -> 2 -> 1

示例2：
输入：n = 7
输出：4
解释：7 -> 8 -> 4 -> 2 -> 1
或7 -> 6 -> 3 -> 2 -> 1

示例3：
输入：n = 4
输出：2

提示：1 <= n <= 2^31 - 1
*/

// 动态规划，超时
int integerReplacement(int n) {
  int *dp = (int *)malloc(sizeof(int) * (n + 1));
  memset(dp, 0, sizeof(int) * (n + 1));
  dp[0] = dp[1] = 0;
  for (int i = 2; i <= n; ++i) {
    if (i % 2) {
      // dp[i] = fmin(dp[(i + 1)/2], dp[(i - 1)/2]) + 2;
      dp[i] = fmin(dp[(i + 1) >> 1], dp[(i - 1) >> 1]) + 2;
    } else {
      // dp[i] = dp[i/2] + 1;
      dp[i] = dp[i >> 1] + 1;
    }
  }

  return dp[n];
}

int integerReplacement(int n) {
  int count = 0;
  while (n != 1) {
    if ((n & 1) == 0) {
      n >>= 1;
    } else {
      if (3 == n || (n & 2) == 0) {
        n -= 1;
      } else if (n == INT_MAX) {
        // why n -= 1 return 33?
        return 32;
      } else {
        n += 1;
      }
    }
    ++count;
  }
  return count;
}

// 超时
class Solution {
 public:
  int integerReplacement(int n) {
    vector<int> dp(n + 1, 0);
    for (int i = 2; i <= n; ++i) {
      if (i % 2) {
        dp[i] = min(dp[(i + 1) >> 1], dp[(i - 1) >> 1]) + 2;
      } else {
        dp[i] = dp[i >> 1] + 1;
      }
    }

    return dp[n];
  }
};
