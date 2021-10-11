/*
 * @lc app=leetcode.cn id=54 lang=c
 *
 * [54] 螺旋矩阵
 */

// @lc code=start

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize,
                 int* returnSize) {
  int m = matrixSize;
  int n = *matrixColSize;
  int* res = (int*)malloc(sizeof(int) * m * n);
  *returnSize = 0;

  int left = 0, right = n - 1, top = 0, bottom = m - 1;
  while (left <= right && top <= bottom) {
    for (int col = left; col <= right; ++col) {
      res[(*returnSize)++] = matrix[top][col];
    }
    for (int row = top + 1; row <= bottom; ++row) {
      res[(*returnSize)++] = matrix[row][right];
    }
    if (left < right && top < bottom) {
      for (int col = right - 1; col > left; col--) {
        res[(*returnSize)++] = matrix[bottom][col];
      }
      for (int row = bottom; row > top; row--) {
        res[(*returnSize)++] = matrix[row][left];
      }
    }
    left++;
    right--;
    top++;
    bottom--;
  }
  return res;
}
// @lc code=end
