/*
给定一个m x n的矩阵，如果一个元素为0，则将其所在行和列的所有元素都设为0。
请使用原地算法。

示例1：
输入：matrix = [[1,1,1],[1,0,1],[1,1,1]]
输出：[[1,0,1],[0,0,0],[1,0,1]]

示例2：
输入：matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
输出：[[0,0,0,0],[0,4,5,0],[0,3,1,0]]

提示：
m == matrix.length
n == matrix[0].length
1 <= m, n <= 200
-2^31 <= matrix[i][j] <= 2^31 - 1

进阶：
一个直观的解决方案是使用O(mn)的额外空间，但这并不是一个好的解决方案。
一个简单的改进方案是使用O(m + n)的额外空间，但这仍然不是最好的解决方案。
你能想出一个仅使用常量空间的解决方案吗？
*/

// 面试题0108零矩阵

void setZeroes(int** matrix, int matrixSize, int* matrixColSize) {
  int m = matrixSize;
  int n = matrixColSize[0];
  int row[m], col[n];
  memset(row, 0, sizeof(row));
  memset(col, 0, sizeof(col));
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (!matrix[i][j]) {
        row[i] = col[j] = true;
      }
    }
  }
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (row[i] || col[j]) {
        matrix[i][j] = 0;
      }
    }
  }
}

void setZeroes(int** matrix, int matrixSize, int* matrixColSize) {
  int m = matrixSize;
  int n = matrixColSize[0];
  int flag_col0 = false, flag_row0 = false;
  for (int i = 0; i < m; i++) {
    if (!matrix[i][0]) {
      flag_col0 = true;
    }
  }
  for (int j = 0; j < n; j++) {
    if (!matrix[0][j]) {
      flag_row0 = true;
    }
  }
  for (int i = 1; i < m; i++) {
    for (int j = 1; j < n; j++) {
      if (!matrix[i][j]) {
        matrix[i][0] = matrix[0][j] = 0;
      }
    }
  }
  for (int i = 1; i < m; i++) {
    for (int j = 1; j < n; j++) {
      if (!matrix[i][0] || !matrix[0][j]) {
        matrix[i][j] = 0;
      }
    }
  }
  if (flag_col0) {
    for (int i = 0; i < m; i++) {
      matrix[i][0] = 0;
    }
  }
  if (flag_row0) {
    for (int j = 0; j < n; j++) {
      matrix[0][j] = 0;
    }
  }
}