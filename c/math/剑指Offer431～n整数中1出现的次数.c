/*
输入一个整数n，求1～n这n个整数的十进制表示中1出现的次数。
例如，输入12，1～12这些整数中包含1的数字有1、10、11和12，1一共出现了5次。

示例1：
输入：n = 12
输出：5

示例2：
输入：n = 13
输出：6

限制：1 <= n < 2^31

注意：本题与233题相同
*/

int countDigitOne(int n) {
  unsigned i = 1, ans = 0, befor = 0;
  while (n) {
    int tmp = n % 10;
    n /= 10;
    if (tmp > 1)
      ans += (n + 1) * i;
    else if (tmp == 1)
      ans += n * i + befor + 1;
    else
      ans += n * i;
    befor += tmp * i;
    i *= 10;
  }
  return ans;
}