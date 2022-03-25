/*
给你一个m行n列的矩阵 matrix，请按照顺时针螺旋顺序，返回矩阵中的所有元素。

示例1：
输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
输出：[1,2,3,6,9,8,7,4,5]

示例2：
输入：matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
输出：[1,2,3,4,8,12,11,10,9,5,6,7]

提示：
m == matrix.length
n == matrix[i].length
1 <= m, n <= 10
-100 <= matrix[i][j] <= 100
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
