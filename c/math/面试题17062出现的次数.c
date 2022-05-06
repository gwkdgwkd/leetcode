/*
编写一个方法，计算从0到n(含n)中数字2出现的次数。

示例:
输入: 25
输出: 9
解释: (2, 12, 20, 21, 22, 23, 24, 25)(注意22应该算作两次)

提示：n <= 10^9
*/

int numberOf2sInRange(int n) {
  int ans = 0;
  long mod = 10;
  long mul = 1;
  for (int i = 0; i < 10; i++) {
    ans += n / mod * mul;
    if (n % mod >= 2 * mul) {
      ans += fmin(n % mod - 2 * mul + 1, mul);
    }
    mod *= 10, mul *= 10;
  }
  return ans;
}