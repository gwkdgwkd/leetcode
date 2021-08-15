/*
 * @lc app=leetcode.cn id=338 lang=c
 *
 * [338] 比特位计数
 */

// @lc code=start

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

/*
// Brian Kernighan算法
int countOnes(int x) {
  int ones = 0;
  while (x > 0) {
    x &= (x - 1);
    ones++;
  }
  return ones;
}
int* countBits(int n, int* returnSize) {
  int* bits = malloc(sizeof(int) * (n + 1));
  *returnSize = n + 1;
  for (int i = 0; i <= n; i++) {
    bits[i] = countOnes(i);
  }
  return bits;
}
*/

/*
// 动态规划——最高有效位
int* countBits(int n, int* returnSize) {
  int* ret = (int*)malloc(sizeof(int) * (n + 1));
  *returnSize = n + 1;
  ret[0] = 0;
  int high = 0;
  for (int i = 1; i <= n; ++i) {
    // i & (i - 1) : 把二进制最低位的1变成0
    // (n > 0 && ((n & (n - 1)) == 0)是判断n是不是2的次幂
    if ((i & (i - 1)) == 0) {
      high = i;
    }
    ret[i] = ret[i - high] + 1;
  }

  return ret;
}
*/

/*
// 动态规划——最低有效位
int* countBits(int n, int* returnSize) {
  int* bits = malloc(sizeof(int) * (n + 1));
  *returnSize = n + 1;
  bits[0] = 0;
  for (int i = 1; i <= n; i++) {
    bits[i] = bits[i >> 1] + (i & 1);
  }
  return bits;
}
*/

// 动态规划——最低设置位
// 定义正整数x的「最低设置位」为x的二进制表示中的最低的1所在位。
int* countBits(int n, int* returnSize) {
  int* bits = malloc(sizeof(int) * (n + 1));
  *returnSize = n + 1;
  bits[0] = 0;
  for (int i = 1; i <= n; i++) {
    bits[i] = bits[i & (i - 1)] + 1;
  }
  return bits;
}

// @lc code=end
