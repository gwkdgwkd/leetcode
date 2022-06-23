/*
给定两个整数，被除数dividend和除数divisor。
将两数相除，要求不使用乘法、除法和mod运算符。
返回被除数dividend除以除数divisor得到的商。
整数除法的结果应当截去（truncate）其小数部分，
例如：truncate(8.345) = 8以及truncate(-2.7335) = -2

示例1:
输入: dividend = 10, divisor = 3
输出: 3
解释: 10/3 = truncate(3.33333..) = truncate(3) = 3

示例2:
输入: dividend = 7, divisor = -3
输出: -2
解释: 7/-3 = truncate(-2.33333..) = -2

提示：
被除数和除数均为32位有符号整数，除数不为0。
假设我们的环境只能存储32位有符号整数，其数值范围是[-2^31,2^31 - 1]。
本题中，如果除法结果溢出，则返回2^31 - 1。
*/

// 剑指OfferII001整数除法

#define INT_MAX 0X7FFFFFFF
#define INT_MIN 0X80000000
int divide(int dividend, int divisor) {
  int result = 0;       // 存放结果值
  if (dividend == 0) {  // 特殊情况判断
    return 0;
  } else if (dividend == INT_MIN && divisor == -1) {
    // 被除数为INT_MIN的两种特殊情况
    return INT_MAX;
  } else if (dividend == INT_MIN && divisor == 1) {
    return INT_MIN;
  } else if (dividend == INT_MIN && divisor == INT_MIN) {
    // 除数为INT_MIN，就这两种情况
    return 1;
  } else if (divisor == INT_MIN) {
    return 0;
  }

  bool negative = (dividend ^ divisor) < 0;  // 判断结果是否为负数

  if (dividend == INT_MIN) {  // 若被除数为INT_MIN，先减一次，在再进行运算
    dividend += abs(divisor);
    result++;
  }
  int t = abs(dividend);
  int d = abs(divisor);

  for (int i = 31; i >= 0; i--) {
    if ((t >> i) >= d) {
      result += 1 << i;
      t -= d << i;
    }
  }

  if (result == INT_MIN)
    return INT_MAX;
  else
    return negative ? -result : result;
  return 0;
}