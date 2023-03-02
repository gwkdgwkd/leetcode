/*
给你一个非负整数x，计算并返回x的算术平方根。
由于返回类型是整数，结果只保留整数部分，小数部分将被舍去。
注意：不允许使用任何内置指数函数和算符，例如pow(x,0.5)或者x**0.5。

示例1：
输入：x = 4
输出：2

示例2：
输入：x = 8
输出：2
解释：8的算术平方根是2.82842..., 由于返回类型是整数，小数部分将被舍去。

提示：
0 <= x <= 2^31 - 1
*/

// 剑指OfferII072求平方根

// 袖珍计算器算法是一种用指数函数exp和对数函数ln代替平方根函数的方法。
// 通过有限的可以使用的数学函数，得到我们想要计算的结果。
int mySqrt(int x) {
  if (x == 0) {
    return 0;
  }
  int ans = exp(0.5 * log(x));
  return ((long long)(ans + 1) * (ans + 1) <= x ? ans + 1 : ans);
}

// 二分查找法
int mySqrt(int x) {
  int left = 0;
  int right = x;
  int mid;
  int ans = -1;
  while (left <= right) {
    mid = left + (right - left) / 2;
    if ((long long)mid * mid <= x) {
      ans = mid;
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  return ans;
}

class Solution {
 public:
  int mySqrt(int x) {
    int left = 0;
    int right = x;
    int ret = 0;

    while (left <= right) {
      int mid = left + (right - left) / 2;
      if ((long long)mid * mid <= x) {
        ret = mid;
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }

    return ret;
  }
};
