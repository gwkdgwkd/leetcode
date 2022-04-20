/*
0,1,···,n-1这n个数字排成一个圆圈，从数字0开始，
每次从这个圆圈里删除第m个数字（删除后从下一个数字开始计数）。
求出这个圆圈里剩下的最后一个数字。
例如，0、1、2、3、4这5个数字组成一个圆圈，从数字0开始每次删除第3个数字，
则删除的前4个数字依次是2、0、4、1，因此最后剩下的数字是3。

示例1：
输入: n = 5, m = 3
输出: 3

示例2：
输入: n = 10, m = 17
输出: 2

限制：
1 <= n <= 10^5
1 <= m <= 10^6
*/

// 这个问题实际上是约瑟夫问题，从最终活着的人编号的反推
int lastRemaining(int n, int m) {
  int ret = 0;  // 最终活下来那个人的初始位置，只有一个人，下标为0
  for (int i = 2; i <= n; ++i) {  // 每次计算i，m的值
    ret = (ret + m) % i;          // 每次循环右移
  }

  return ret;
}