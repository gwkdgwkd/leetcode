/*
给定一个整数n，计算所有小于等于n的非负整数中数字1出现的个数。

示例1：
输入：n = 13
输出：6

示例2：
输入：n = 0
输出：0

提示：0 <= n <= 109
*/

int countDigitOne(int n) {
  // i表示记录到了第几位，ans是总和，befor身后的数字
  unsigned i = 1, ans = 0, befor = 0;
  while (n) {
    int tmp = n % 10;  // 记录这个位置是什么
    n /= 10;           // n此时是这个位置前面的数字
    if (tmp > 1)
      ans += (n + 1) * i;  // 如果这个位置大于1，前面的位置有n+1种取法
    else if (tmp == 1)
      ans += n * i + befor + 1;  // 等于1，前面的位置有n+1种取法，
    else
      ans += n * i;    // 这个位置是0，则只有n种取法
    befor += tmp * i;  // 记录身后的数字
    i *= 10;           // 往下一位
  }
  return ans;
}