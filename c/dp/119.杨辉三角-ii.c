/*
 * @lc app=leetcode.cn id=119 lang=c
 *
 * [119] 杨辉三角 II
 */

// @lc code=start

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* getRow(int rowIndex, int* returnSize) {
  *returnSize = rowIndex + 1;
  int* ret = (int*)malloc(*returnSize * sizeof(int));
  memset(ret, 0, sizeof(int) * (*returnSize));

  ret[0] = 1;
  for (int i = 1; i <= rowIndex; ++i) {
    for (int j = i; j > 0; --j) {
      ret[j] += ret[j - 1];
    }
  }

  return ret;
}
// @lc code=end
