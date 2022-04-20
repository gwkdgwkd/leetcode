/*
输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字。

示例1：
输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
输出：[1,2,3,6,9,8,7,4,5]

示例2：
输入：matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
输出：[1,2,3,4,8,12,11,10,9,5,6,7]

限制：
0 <= matrix.length <= 100
0 <= matrix[i].length <= 100
*/

int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize,
                 int* returnSize) {
  int m = matrixSize;
  *returnSize = 0;
  if (m == 0) {
    return NULL;
  }
  int n = matrixColSize[0];
  int* res = (int*)malloc(sizeof(int) * m * n);

  int left = 0;
  int right = n - 1;
  int top = 0;
  int bottom = m - 1;
  while (left <= right && top <= bottom) {
    for (int col = left; col <= right; ++col) {
      res[(*returnSize)++] = matrix[top][col];
    }
    for (int row = top + 1; row <= bottom; ++row) {
      res[(*returnSize)++] = matrix[row][right];
    }
    if (left < right && top < bottom) {
      for (int col = right - 1; col > left; --col) {
        res[(*returnSize)++] = matrix[bottom][col];
      }
      for (int row = bottom; row > top; --row) {
        res[(*returnSize)++] = matrix[row][left];
      }
    }
    ++left;
    --right;
    ++top;
    --bottom;
  }

  return res;
}