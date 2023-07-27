/*
求1+2+...+n，要求不能使用乘除法、for、while、if、else、
switch、case等关键字及条件判断语句（A?B:C）。

示例1：
输入：n = 3
输出：6

示例2：
输入：n = 9
输出：45

限制：1 <= n <= 10000
*/

int sumNums(int n) {
  // 递归需要递归出口，要使用条件判断
  // return n == 0 ? 0 : n + sumNums(n - 1); // 使用了条件语句

  n && (n += sumNums(n - 1));  // 利用短路性质，实现条件判断
  return n;
}

class Solution {
 public:
  int sumNums(int n) {
    n && (n += sumNums(n - 1));
    return n;
  }
};