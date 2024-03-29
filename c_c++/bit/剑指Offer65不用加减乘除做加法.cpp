/*
写一个函数，求两个整数之和，要求在函数体内不得使用+、-、*、/四则运算符号。

示例：
输入：a = 1, b = 1
输出：2

提示：
a，b均可能是负数或0
结果不会溢出32位整数
*/

// 面试题1701不用加号的加法

int add(int a, int b) {
  // a和b第一次计算完进位和、进位之后，将b赋值为进位，
  // 再与a进行第二次计算，直到进位为0，表示从低位到高位全部计算完，
  // 所以这里需要循环处理所有的进位

  while (b != 0) {
    int temp = (unsigned int)(a & b) << 1;
    a = a ^ b;  // a为无进位和
    b = temp;   // b为进位
  }
  return a;
}

class Solution {
 public:
  int add(int a, int b) {
    while (b != 0) {
      int tmp = (unsigned)(a & b) << 1;
      a ^= b;
      b = tmp;
    }
    return a;
  }
};