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
  int f[1 << n];
  memset(f, 0, sizeof(f));
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
