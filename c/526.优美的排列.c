/*
 * @lc app=leetcode.cn id=526 lang=c
 *
 * [526] 优美的排列
 */

// @lc code=start

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
// @lc code=end
