/*
整数转换，编写一个函数，确定需要改变几个位才能将整数A转成整数B。

示例1：
输入：A = 29 （或者0b11101）, B = 15（或者0b01111）
输出：2

示例2：
输入：A = 1，B = 2
输出：2

提示:A，B范围在[-2147483648, 2147483647]之间
*/

int convertInteger(int A, int B) {
  int tmp = A ^ B;  // 异或的结果表示两个数的差异位
  int count = 0;
  for (int i = 0; i < 32; i++) {
    if ((tmp >> i) & 1 == 1) {
      count++;
    }
  }
  return count;
}

class Solution {
 public:
  int convertInteger(int A, int B) {
    int diff = A ^ B;
    int count = 0;

    for (int i = 0; i < 32; ++i) {
      if ((diff >> i) & 1 == 1) {
        ++count;
      }
    }

    return count;
  }
};

class Solution {
 public:
  int convertInteger(int A, int B) {
    unsigned int x = A ^ B;
    int count = 0;

    while (x) {
      ++count;
      x &= (x - 1);
    }

    return count;
  }
};