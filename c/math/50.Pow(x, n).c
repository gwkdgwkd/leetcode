/*
实现pow(x, n)，即计算x的n次幂函数（即，xn）。

示例1：
输入：x = 2.00000, n = 10
输出：1024.00000

示例2：
输入：x = 2.10000, n = 3
输出：9.26100

示例3：
输入：x = 2.00000, n = -2
输出：0.25000
解释：2-2 = 1/22 = 1/4 = 0.25

提示：
-100.0 < x < 100.0
-2^31 <= n <= 2^31-1
-10^4 <= x^n <= 10^4
*/

// 暴力法，超时
// 时间复杂度：O(⁡n)
// 空间复杂度：O(1)
double myPow(double x, int n) {
  long long N = n;  // 处理负数越界的常用手段
  if (N < 0) {
    x = 1 / x;
    N = -N;
  }
  double ans = 1;
  for (long long i = 0; i < N; ++i) {
    ans *= x;
  }

  return ans;
}

// 分治，递归
// 时间复杂度：O(log⁡n)
// 空间复杂度：O(log⁡n)
double quickMul(double x, long long N) {
  if (N == 0) {
    return 1.0;
  }
  double y = quickMul(x, N / 2);  // 只算一半
  // 如果N为奇数，还要再乘以一个自己
  return N % 2 == 0 ? y * y : y * y * x;
}
double myPow(double x, int n) {
  long long N = n;  // 防止负数越界
  // 如果N是负数，先算正数的，然后再取倒数
  return N >= 0 ? quickMul(x, N) : 1.0 / quickMul(x, -N);
}

// 分治，迭代
double quickMul(double x, long long N) {
  double ans = 1.0;
  double x_contribute = x;
  // 在对N进行二进制拆分的同时计算答案
  while (N > 0) {
    if (N % 2 == 1) {
      // 如果N二进制表示的最低位为1，那么需要计入贡献
      ans *= x_contribute;
    }
    x_contribute *= x_contribute;  // 平方
    // 舍弃N二进制表示的最低位，这样我们每次只要判断最低位即可
    N /= 2;
  }
  return ans;
}
double myPow(double x, int n) {
  long long N = n;
  return N >= 0 ? quickMul(x, N) : 1.0 / quickMul(x, -N);
}