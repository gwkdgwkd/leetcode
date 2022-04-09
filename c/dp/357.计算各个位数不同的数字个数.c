/*
给你一个整数n，统计并返回各位数字都不同的数字x的个数，其中0<=x<10^n。

示例1：
输入：n = 2
输出：91
解释：答案应为除去11、22、33、44、55、66、77、88、99外，在0≤x<100范围内的所有数字。

示例2：
输入：n = 0
输出：1

提示：0 <= n <= 8
*/

// 动态规划
int countNumbersWithUniqueDigits(int n) {
  if (1 == n) {
    return 10;
  }

  int dp[n + 1];  // d[i]表示对于i位数字里重复的数字的个数
  memset(dp, 0, sizeof(dp));
  // 初始化
  // d[0] = 0,对于0位数字不可能有重复的数字
  // d[1] = 0,对于1位数字也没有重复

  for (int i = 2; i <= n; ++i) {
    // d[i]考虑两种情况：
    // 1.前面i-1有重复，那么最后一位是0~9的10个数字都可以：d[i-1]*10
    // 2.前面i-1没重复，那么最后一位就是i-1里取一个就重复了：(9*pow(10,i-2)-d[i-1])*(i-1)，
    //   解释如下：
    //   9*pow(10,i-2)表示对于i-1位数字有这么多种可能，9是1-9在第一位，后面就是10^(i-2)
    //   9*pow(10,i-2)-d[i-1]表示i-1没重复的数字个数
    //   (*)*(i-1)就是取i-1位数字里一个即可
    dp[i] = dp[i - 1] * 10 + (9 * pow(10, i - 2) - dp[i - 1]) * (i - 1);
    // 为什么是(9*pow(10,i-2)呢？
    // 因为pow(10,i-1)包括了不是i位的数字，假设i==3那么pow(10,i-1) == 100,
    // 注意这里包括了0-9所以我们要减去这0-9个数字，
    // 也就是pow(10,i-1)-pow(10,i-2), 简化后成了(9*pow(10,i-2)。
  }

  int sum = 0;
  for (int i = 0; i <= n; ++i) {
    sum += dp[i];
  }

  return pow(10, n) - sum;  // 总数字减去重复情况的数字之和
}

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
