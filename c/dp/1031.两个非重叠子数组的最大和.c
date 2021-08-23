/*
 * @lc app=leetcode.cn id=1031 lang=c
 *
 * [1031] 两个非重叠子数组的最大和
 */

// @lc code=start

// 前缀和+动态规划
#define max(a, b) ((a) > (b) ? (a) : (b))
int maxSumTwoNoOverlap(int* A, int ASize, int L, int M) {
  int* s;
  int prevMaxSum, sum, i, t;

  s = malloc((ASize + 1) * sizeof(int));
  s[0] = sum = 0;
  for (i = 1; i <= ASize; i++) s[i] = s[i - 1] + A[i - 1];

  // L、M前后关系的两种情况
  for (t = 0; t < 2; t++) {
    prevMaxSum = 0;
    for (i = L; i + M <= ASize; i++) {
      prevMaxSum = max(prevMaxSum, s[i] - s[i - L]);
      sum = max(sum, prevMaxSum + s[i + M] - s[i]);
    }
    // 借用prevMaxSum来交换一下L和M
    prevMaxSum = L;
    L = M;
    M = prevMaxSum;
  }

  free(s);
  return sum;
}
// @lc code=end
