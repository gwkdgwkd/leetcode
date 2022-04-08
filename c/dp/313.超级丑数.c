/*
超级丑数是一个正整数，并满足其所有质因数都出现在质数数组primes中。
给你一个整数n和一个整数数组primes，返回第n个超级丑数。
题目数据保证第n个超级丑数在32-bit带符号整数范围内。

示例1：
输入：n = 12, primes = [2,7,13,19]
输出：32 
解释：给定长度为4的质数数组primes = [2,7,13,19]，
     前12个超级丑数序列为：[1,2,4,7,8,13,14,16,19,26,28,32]。

示例2：
输入：n = 1, primes = [2,3,5]
输出：1
解释：1不含质因数，因此它的所有质因数都在质数数组primes = [2,3,5]中。

提示：
1 <= n <= 106
1 <= primes.length <= 100
2 <= primes[i] <= 1000
题目数据保证primes[i]是一个质数
primes中的所有值都互不相同，且按递增顺序排列
*/

// 动态规划
int nthSuperUglyNumber(int n, int* primes, int primesSize) {
  int dp[n + 1];
  dp[1] = 1;
  int m = primesSize;
  int pointers[m];
  for (int i = 0; i < m; i++) {
    pointers[i] = 1;
  }
  for (int i = 2; i <= n; i++) {
    int nums[m];
    int minNum = INT_MAX;
    for (int j = 0; j < m; j++) {
      nums[j] = dp[pointers[j]] * primes[j];
      minNum = fmin(minNum, nums[j]);
    }
    dp[i] = minNum;
    for (int j = 0; j < m; j++) {
      if (minNum == nums[j]) {
        pointers[j]++;
      }
    }
  }
  return dp[n];
}
