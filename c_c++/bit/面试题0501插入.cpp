/*
给定两个整型数字N与M，以及表示比特位置的i与j（i<=j，且从0位开始计算）。
编写一种方法，使M对应的二进制数字插入N对应的二进制数字的第i~j位区域，
不足之处用0补齐。
题目保证从i位到j位足以容纳M，例如：M=10011，则i～j区域至少可容纳5位。

示例1:
输入：N = 1024(10000000000), M = 19(10011), i = 2, j = 6
输出：N = 1100(10001001100)

示例2:
输入： N = 0, M = 31(11111), i = 0, j = 4
输出：N = 31(11111)
*/

int insertBits(int N, int M, int i, int j) {
  for (int start = i; start <= j; start++) {
    N &= ~((unsigned int)1 << start);
  }
  N |= (M << i);
  return N;
}

class Solution {
 public:
  int insertBits(int N, int M, int i, int j) {
    int mask = ((1 << (j - i + 1)) - 1) << i;
    mask = ~mask;
    N &= mask;
    return N | (M << i);
  }
};