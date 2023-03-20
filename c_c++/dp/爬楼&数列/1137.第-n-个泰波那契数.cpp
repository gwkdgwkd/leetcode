/*
泰波那契序列Tn定义如下：
T0 = 0，T1 = 1，T2 = 1，且在n >= 0的条件下Tn+3 = Tn + Tn+1 + Tn+2
给整数n，请返回第n个泰波那契数Tn的值。

示例1：
输入：n = 4
输出：4
解释：
T_3 = 0 + 1 + 1 = 2
T_4 = 1 + 1 + 2 = 4

示例2：
输入：n = 25
输出：1389537

提示：
0 <= n <= 37
答案保证是一个32位整数，即answer <= 2^31 - 1。
*/

// 动态规划
int tribonacci(int n) {
  if (n < 2) return n;

  int pre1 = 0;
  int pre2 = 1;
  int pre3 = 1;
  int cur;

  for (int i = 3; i <= n; ++i) {
    cur = pre1 + pre2 + pre3;
    pre1 = pre2;
    pre2 = pre3;
    pre3 = cur;
  }

  return pre3;
}

class Solution {
 public:
  int tribonacci(int n) {
    if (n < 2) {
      return n;
    }
    int pre3 = 0;
    int pre2 = 1;
    int pre1 = 1;
    int cur;

    for (int i = 3; i <= n; ++i) {
      cur = pre1 + pre2 + pre3;
      pre3 = pre2;
      pre2 = pre1;
      pre1 = cur;
    }

    return pre1;
  }
};
