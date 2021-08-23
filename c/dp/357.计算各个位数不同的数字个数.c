/*
 * @lc app=leetcode.cn id=357 lang=c
 *
 * [357] 计算各个位数不同的数字个数
 */

// @lc code=start

/*
// 动态规划
int countNumbersWithUniqueDigits(int n) {
  if (1 == n) {
    return 10;
  }

  int dp[n + 1];
  memset(dp, 0, sizeof(dp));

  for (int i = 2; i <= n; ++i) {
    // dp[i - 1] * 10表示i-1有重复的数字，最后意味是0-9都可以
    // (9 * pow(10, i - 2) - dp[i - 1]) * (i - 1)表示i-1没有重复的数字，最后一位是和前面一样的数字
    dp[i] = dp[i - 1] * 10 + (9 * pow(10, i - 2) - dp[i - 1]) * (i - 1);
    // 为什么是(9*pow(10, i-2)呢？因为pow(10,i-1)包括了不是i位的数字，假设i==3那么pow(10,i-1) == 100,
    // 注意这里包括了0-9所以我们要减去这0-9个数字，也就是pow(10,i-1) - pow(10,i-2), 简化后成了(9*pow(10, i-2)。

  }

  int sum = 0;
  for (int i = 0; i <= n; ++i) {
    sum += dp[i];
  }

  return pow(10, n) - sum;
}
*/

int countNumbersWithUniqueDigits(int n) {
  if (1 == n) {
    return 10;
  }

  int dp[n + 1];
  memset(dp, 0, sizeof(dp));

  int pre = 0;
  int sum = 0;
  for (int i = 2; i <= n; ++i) {
    pre = pre * 10 + (9 * pow(10, i - 2) - pre) * (i - 1);
    sum += pre;
  }

  return pow(10, n) - sum;
}
// @lc code=end
