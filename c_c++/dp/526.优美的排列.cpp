/*
假设有从1到n的n个整数。
用这些整数构造一个数组perm（下标从1开始），只要满足下述条件之一，该数组就是一个优美的排列：
perm[i]能够被i整除
i能够被perm[i]整除
给你一个整数n，返回可以构造的优美排列的数量。

示例1：
输入：n = 2
输出：2
解释：
第1个优美的排列是[1,2]：
    - perm[1] = 1能被i = 1整除
    - perm[2] = 2能被i = 2整除
第2个优美的排列是[2,1]:
    - perm[1] = 2能被i = 1整除
    - i = 2能被perm[2] = 1整除

示例2：
输入：n = 1
输出：1

提示：1 <= n <= 15
*/

// 动态规划
int countArrangement(int n) {
  // 使用一个n位的整数mask表示当前数组的构造情况:
  // 1.整数mask的二进制表示中1的个数m表示当前数组前m位已经填入数字;
  // 2.整数mask的二进制表示中第i位为1表示整数i已经被选取放入数组内;

  // 设f(mask)表示整数mask对应构造情况下的优美排列数量，最终结果是f(2^n - 1);
  int f[1 << n];
  memset(f, 0, sizeof(f));
  f[0] = 1;
  for (int mask = 1; mask < (1 << n); mask++) {
    int num = __builtin_popcount(mask);
    for (int i = 0; i < n; i++) {
      f[mask] += f[mask ^ (1 << i)];
      // 转移方程为： f[mask] += f[mask ^ (1 << i)];
      // 其中 0 <= i < n 且满足条件：
      // 1.mask & (1 << i) != 0，即数字i+1被选取
      // 2.(m % (i + 1)) == 0 || (i + 1) % m == 0)，即数字i+1可以被放入第m位
      // 转移方程的含义是累加将数字i+1放入第m位后，剩下数字排列进前m-1位的优美排列数量；
      if (mask & (1 << i) && (num % (i + 1) == 0 || (i + 1) % num == 0)) {
        f[mask] += f[mask ^ (1 << i)];
      }
    }
  }
  return f[(1 << n) - 1];
}

class Solution {
 public:
  int countArrangement(int n) {
    vector<int> f(1 << n);
    f[0] = 1;
    for (int mask = 1; mask < (1 << n); mask++) {
      int num = __builtin_popcount(mask);
      for (int i = 0; i < n; i++) {
        if (mask & (1 << i) && (num % (i + 1) == 0 || (i + 1) % num == 0)) {
          f[mask] += f[mask ^ (1 << i)];
        }
      }
    }
    return f[(1 << n) - 1];
  }
};
