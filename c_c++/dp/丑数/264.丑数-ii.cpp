/*
给你一个整数n，请你找出并返回第n个丑数。
丑数就是只包含质因数2、3或5的正整数。

示例1：
输入：n = 10
输出：12
解释：[1, 2, 3, 4, 5, 6, 8, 9, 10, 12]是由前10个丑数组成的序列。

示例2：
输入：n = 1
输出：1
解释：1通常被视为丑数。

提示：1 <= n <= 1690
*/

// 剑指Offer49丑数

// 动态规划
int nthUglyNumber(int n) {
  int dp[n + 1];
  dp[1] = 1;
  int p2 = 1, p3 = 1, p5 = 1;
  for (int i = 2; i <= n; i++) {
    int num2 = dp[p2] * 2, num3 = dp[p3] * 3, num5 = dp[p5] * 5;
    dp[i] = fmin(fmin(num2, num3), num5);
    if (dp[i] == num2) {
      p2++;
    }
    if (dp[i] == num3) {
      p3++;
    }
    if (dp[i] == num5) {
      p5++;
    }
  }
  return dp[n];
}

class Solution {
 public:
  int nthUglyNumber(int n) {
    vector<int> dp(n);
    dp[0] = 1;

    int p2 = 0;
    int p3 = 0;
    int p5 = 0;
    for (int i = 1; i < n; ++i) {
      int n2 = dp[p2] * 2;
      int n3 = dp[p3] * 3;
      int n5 = dp[p5] * 5;
      dp[i] = min(n2, min(n3, n5));
      if (dp[i] == n2) ++p2;
      if (dp[i] == n3) ++p3;
      if (dp[i] == n5) ++p5;
    }

    return dp[n - 1];
  }
};