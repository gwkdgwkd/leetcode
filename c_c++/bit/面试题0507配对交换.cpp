/*
配对交换。编写程序，交换某个整数的奇数位和偶数位，
尽量使用较少的指令（也就是说，位0与位1交换，位2与位3交换，以此类推）。

示例1:
输入：num = 2（或者0b10）
输出：1(或者0b01)

示例2:
输入：num = 3
输出：3

提示:num的范围在[0, 2^30 - 1]之间，不会发生整数溢出。
*/

int exchangeBits(int num) {
  return (((num & 0x55555555) << 1) | ((num & 0xaaaaaaaa) >> 1));
}

int exchangeBits(int num) {
  int a = 0B10101010101010101010101010101010;
  int b = 0B01010101010101010101010101010101;
  a &= num;  // 保留奇数位
  b &= num;  // 保留偶数位
  a >>= 1;   // 交换奇偶位
  b <<= 1;
  int ans = a | b;  // 分别将奇偶位组合在一起就可以
  return ans;
}

int exchangeBits(int num) {
  int i = 0, j = 1;
  while (i <= 30) {
    int a = num >> i & 1, b = num >> j & 1;
    if (a != b) {
      num ^= 1 << i;
      num ^= 1 << j;
    }
    i += 2;
    j += 2;
  }
  return num;
}

class Solution {
 public:
  int exchangeBits(int num) {
    for (int i = 0; i <= 30; i += 2) {
      int a = num >> i & 1;
      int b = num >> (i + 1) & 1;
      if (a != b) {
        num ^= 1 << i;
        num ^= 1 << (i + 1);
      }
    }

    return num;
  }
};