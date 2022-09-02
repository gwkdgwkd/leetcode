/*
给定一个正整数num，编写一个函数，
如果num是一个完全平方数，则返回true，否则返回false。
进阶：不要使用任何内置的库函数，如sqrt。

示例1：
输入：num = 16
输出：true

示例2：
输入：num = 14
输出：false

提示：
1 <= num <= 2^31 - 1
*/

// 二分查找法
bool isPerfectSquare(int num) {
  int left = 0;
  int right = num;
  while (left <= right) {
    int mid = left + (right - left) / 2;
    if ((long long)mid * mid == num) {
      return true;
    } else if ((long long)mid * mid < num) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  return false;
}

class Solution {
 public:
  bool isPerfectSquare(int num) {
    int left = 0;
    int right = num;

    while (left <= right) {
      int mid = left + (right - left) / 2;
      long i = (long)mid * mid;
      if (i < num) {
        left = mid + 1;
      } else if (i > num) {
        right = mid - 1;
      } else {
        return true;
      }
    }

    return false;
  }
};
