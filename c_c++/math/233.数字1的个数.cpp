/*
给定一个整数n，计算所有小于等于n的非负整数中数字1出现的个数。

示例1：
输入：n = 13
输出：6

示例2：
输入：n = 0
输出：0

提示：0 <= n <= 10^9
*/

// 剑指Offer431～n整数中1出现的次数

int countDigitOne(int n) {
  long long mulk = 1;
  int ans = 0;
  for (int k = 0; n >= mulk; ++k) {
    ans += (n / (mulk * 10)) * mulk +
           fmin(fmax(n % (mulk * 10) - mulk + 1, 0LL), mulk);
    mulk *= 10;
  }
  return ans;
}

class Solution {
 public:
  int countDigitOne(int n) {
    long long mulk = 1;  // 位数，1表示个位
    int ans = 0;

    // 从低往高位，计算每一位的数量：
    for (int k = 0; n >= mulk; ++k) {
      ans += (n / (mulk * 10)) * mulk +
             min(max(n % (mulk * 10) - mulk + 1, 0LL), mulk);
      mulk *= 10;
    }
    return ans;
  }
};