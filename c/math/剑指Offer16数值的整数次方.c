/*
实现 pow(x,n)，即计算x的n次幂函数（即，x^n）。
不得使用库函数，同时不需要考虑大数问题。

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
-10^4 <= xn <= 10^4

注意：本题与50题相同
*/

double quickMul(double x, long long N) {
  if (N == 0) return 1.0;

  double half = quickMul(x, N / 2);
  return N % 2 ? half * half * x : half * half;
}
double myPow(double x, int n) {
  long long N = n;
  return N >= 0 ? quickMul(x, N) : 1.0 / quickMul(x, -N);
}