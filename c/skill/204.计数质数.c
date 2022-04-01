/*
给定整数n，返回所有小于非负整数n的质数的数量。

示例1：
输入：n = 10
输出：4
解释：小于10的质数一共有4个, 它们是2, 3, 5, 7。

示例2：
输入：n = 0
输出：0

示例3：
输入：n = 1
输出：0

提示：0 <= n <= 5 * 106
*/

// 常规写法，超时
// 间复杂度：O(n^2)
bool isPrime(int n) {
  for (int i = 2; i < n; i++)
    if (n % i == 0) return false;
  return true;
}
int countPrimes(int n) {
  int count = 0;
  for (int i = 2; i < n; i++)
    if (isPrime(i)) count++;
  return count;
}

// Sieve of Eratosthenes
int countPrimes(int n) {
  if (n < 2) return 0;
  bool isPrim[n];
  for (int i = 0; i < n; ++i) {
    isPrim[i] = true;
  }
  for (int i = 2; i * i < n; i++) {
    if (isPrim[i]) {
      for (int j = i * i; j < n; j += i) {
        isPrim[j] = false;
      }
    }
  }

  int count = 0;
  for (int i = 2; i < n; i++) {
    if (isPrim[i]) count++;
  }

  return count;
}