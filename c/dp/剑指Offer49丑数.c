/*
我们把只包含质因子2、3和5的数称作丑数（Ugly Number）。
求按从小到大的顺序的第n个丑数。

示例:
输入: n = 10
输出: 12
解释: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12是前10个丑数。

说明:
1是丑数。
n不超过1690。

注意：本题与264题相同
*/

int nthUglyNumber(int n) {
  int dp[n + 1];
  dp[1] = 1;
  int p2 = 1;
  int p3 = 1;
  int p5 = 1;

  for (int i = 2; i <= n; ++i) {
    int nums2 = dp[p2] * 2;
    int nums3 = dp[p3] * 3;
    int nums5 = dp[p5] * 5;
    dp[i] = fmin(nums2, fmin(nums3, nums5));
    if (dp[i] == nums2) {
      ++p2;
    }
    if (dp[i] == nums3) {
      ++p3;
    }
    if (dp[i] == nums5) {
      ++p5;
    }
  }

  return dp[n];
}