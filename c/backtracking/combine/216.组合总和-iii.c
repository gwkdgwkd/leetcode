/*
 * @lc app=leetcode.cn id=216 lang=c
 *
 * [216] 组合总和 III
 */

// @lc code=start

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
// 回溯算法
int **result;
int resultSize;
int *path;
int pathSize;
void backtracking(int k, int n, int startIndex) {
  if (n < 0) {
    return;
  }
  if (pathSize == k) {
    if (0 == n) {
      result[resultSize] = (int *)malloc(sizeof(int) * k);
      for (int i = 0; i < k; ++i) {
        result[resultSize][i] = path[i];
      }
      resultSize++;
      return;
    }
    return;
  }

  // for(int i = startIndex; i <= 9; ++i) {
  for (int i = startIndex; i <= 9 - (k - pathSize) + 1 && n >= i; ++i) {
    path[pathSize++] = i;
    // printf("%*d[%d %d %d]\n", pathSize * 2, i, n, k, startIndex);
    backtracking(k, n - i, i + 1);
    pathSize--;
  }
  // 3 7
  //  1[7 3 1]
  //    2[6 3 2]
  //      3[4 3 3]
  //      4[4 3 3]
  //    3[6 3 2]
  //    4[6 3 2]
  //    5[6 3 2]
  //    6[6 3 2]
  //  2[7 3 1]
  //    3[5 3 3]
  //    4[5 3 3]
  //    5[5 3 3]
  //  3[7 3 1]
  //    4[4 3 4]
  //  4[7 3 1]
  //  5[7 3 1]
  //  6[7 3 1]
  //  7[7 3 1]

  return;
}
int **combinationSum3(int k, int n, int *returnSize, int **returnColumnSizes) {
  result = (int **)malloc(sizeof(int *) * 2001);
  path = (int *)malloc(sizeof(int) * k);
  resultSize = pathSize = 0;
  backtracking(k, n, 1);
  *returnSize = resultSize;
  *returnColumnSizes = malloc(sizeof(int) * resultSize);
  for (int i = 0; i < resultSize; i++) {
    (*returnColumnSizes)[i] = k;
  }

  return result;
}
// @lc code=end
