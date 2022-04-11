/*
给你一个整数x，如果x是一个回文整数，返回true；否则，返回false。
回文数是指正序（从左向右）和倒序（从右向左）读都是一样的整数。
例如，121是回文，而123不是。

示例1：
输入：x = 121
输出：true

示例2：
输入：x = -121
输出：false
解释：从左向右读, 为-121。从右向左读, 为121-。因此它不是一个回文数。

示例3：
输入：x = 10
输出：false
解释：从右向左读, 为01。因此它不是一个回文数。

提示：-2^31 <= x <= 2^31 - 1
*/

bool isPalindrome(int x) {
  char str[13];
  memset(str, 0, sizeof(str));

  int index = 0;
  bool flag = false;
  if (x < 0) {
    flag = true;
  }

  while (x) {
    str[index++] = x % 10 + '0';
    x /= 10;
  }
  if (flag) {
    str[index++] = '-';
  }

  for (int l = 0, r = index - 1; l < r; ++l, --r) {
    if (str[l] != str[r]) {
      return false;
    }
  }

  return true;
}

bool isPalindrome(int x) {
  // 特殊情况：
  // 如上所述，当x<0时，x不是回文数。
  // 同样地，如果数字的最后一位是0，为了使该数字为回文，则其第一位数字也应该是0，只有0满足这一属性
  if (x < 0 || (x % 10 == 0 && x != 0)) {
    return false;
  }

  int revertedNumber = 0;
  while (x > revertedNumber) {
    revertedNumber = revertedNumber * 10 + x % 10;
    x /= 10;
  }

  // 当数字长度为奇数时，可以通过revertedNumber/10去除处于中位的数字。
  // 例如，当输入为12321时，在while循环的末尾我们可以得到x=12，revertedNumber=123，
  // 由于处于中位的数字不影响回文（它总是与自己相等），所以可以简单地将其去除。
  return x == revertedNumber || x == revertedNumber / 10;
}