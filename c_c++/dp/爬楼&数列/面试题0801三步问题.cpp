/*
三步问题，有个小孩正在上楼梯，楼梯有n阶台阶，小孩一次可以上1阶、2阶或3阶。
实现一种方法，计算小孩有多少种上楼梯的方式，结果可能很大，需要对结果模1000000007。

示例1：
输入：n = 3
输出：4
说明：有四种走法

示例2：
输入：n = 5
输出：13

提示：n范围在[1，1000000]之间
*/

int waysToStep(int n) {
  if (n <= 2) return n;
  int c1 = 1;
  int c2 = 2;
  int c3 = 4;
  for (int i = 3; i < n; ++i) {
    int curr = ((c1 + c2) % 1000000007 + c3) % 1000000007;
    c1 = c2;
    c2 = c3;
    c3 = curr;
  }

  return c3;
}

class Solution {
 public:
  int waysToStep(int n) {
    if (n <= 2) {
      return n;
    }
    int pre3 = 1;
    int pre2 = 2;
    int pre1 = 4;
    int cur;
    for (int i = 4; i <= n; ++i) {
      cur = ((pre3 + pre2) % 1000000007 + pre1) % 1000000007;
      pre3 = pre2;
      pre2 = pre1;
      pre1 = cur;
    }

    return pre1;
  }
};