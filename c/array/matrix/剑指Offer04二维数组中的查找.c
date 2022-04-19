/*
在一个n * m的二维数组中，每一行都按照从左到右递增的顺序排序，
每一列都按照从上到下递增的顺序排序。
请完成一个高效的函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。

示例:
现有矩阵matrix如下：
[
  [1,   4,  7, 11, 15],
  [2,   5,  8, 12, 19],
  [3,   6,  9, 16, 22],
  [10, 13, 14, 17, 24],
  [18, 21, 23, 26, 30]
]
给定target = 5，返回true。
给定target = 20，返回false。

限制：
0 <= n <= 1000
0 <= m <= 1000

注意：与240题相同
*/

// Z型查找
bool findNumberIn2DArray(int** matrix, int matrixSize, int* matrixColSize,
                         int target) {
  if (matrixSize == 0) {
    return false;
  }
  int m = matrixSize;
  int n = matrixColSize[0];

  int i = 0;
  int j = n - 1;
  while (i < m && j >= 0) {
    if (matrix[i][j] < target) {
      ++i;
    } else if (matrix[i][j] > target) {
      --j;
    } else {
      return true;
    }
  }
  return false;
}