#include <cstring>
#include <iostream>

/*
给你一个整数x，如果x是一个回文整数，返回true；否则，返回false。
回文数是指正序和倒序读都是一样的整数，例如，121是回文，而123不是。

示例1：
输入：x = 121
输出：true

示例2：
输入：x = -121
输出：false
解释：从左向右读,为-121。
     从右向左读,为121-。因此它不是一个回文数。

示例3：
输入：x = 10
输出：false
解释：从右向左读,为01。因此它不是一个回文数。

提示：-2^31 <= x <= 2^31 - 1
*/

namespace n1 {
bool isPalindrome(int x) {
  char str[13];
  memset(str, 0, sizeof(str));

  if (x < 0) {
    return false;
  }

  int index = 0;
  while (x) {
    str[index++] = x % 10 + '0';
    x /= 10;
  }

  for (int l = 0, r = index - 1; l < r; ++l, --r) {
    if (str[l] != str[r]) {
      return false;
    }
  }

  return true;
}
}  // namespace n1

namespace n2 {
bool isPalindrome(int x) {
  // 特殊情况：
  // 1.当x<0时，x不是回文数；
  // 2.如果数字的最后一位是0，为了使该数字为回文，则其第一位数字也应该是0，只有0才满足。
  if (x < 0 || (x % 10 == 0 && x != 0)) {
    return false;
  }

  int revertedNumber = 0;
  while (x > revertedNumber) {
    revertedNumber = revertedNumber * 10 + x % 10;
    x /= 10;
  }

  // 当数字长度为奇数时，可以通过revertedNumber/10去除处于中位的数字。
  // 例如，当输入为12321时，在while循环的末尾可以得到x=12，
  // revertedNumber=123，由于处于中位的数字不影响回文，所以可以去除。
  return x == revertedNumber || x == revertedNumber / 10;
}
}  // namespace n2

using namespace std;
namespace n3 {
class Solution {
 public:
  bool isPalindrome(int x) {
    if (x < 0 || (x % 10 == 0 && x != 0)) {
      return false;
    }

    int reverse = 0;
    while (x > reverse) {
      reverse = reverse * 10 + x % 10;
      x /= 10;
    }

    // std::cout << x << "," << reverse << " : ";

    return reverse == x || x == reverse / 10;
  }
};
}  // namespace n3

int main() {
  n3::Solution s;
  std::cout.setf(ios_base::boolalpha);
  std::cout << s.isPalindrome(1234) << std::endl;
  std::cout << s.isPalindrome(1221) << std::endl;
  std::cout << s.isPalindrome(12321) << std::endl;

  // 12,43 : false
  // 12,12 : true
  // 12,123 : true
}