/*
给定一个n×n的二维矩阵matrix表示一个图像。请你将图像顺时针旋转90度。
你必须在原地旋转图像，这意味着你需要直接修改输入的二维矩阵。请不要使用另一个矩阵来旋转图像。

示例 1：
输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
输出：[[7,4,1],[8,5,2],[9,6,3]]

示例2：
输入：matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
输出：[[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]

提示：
n == matrix.length == matrix[i].length
1 <= n <= 20
-1000 <= matrix[i][j] <= 1000
*/

void print(int** matrix, int matrixSize) {
  for (int i = 0; i < matrixSize; ++i) {
    for (int j = 0; j < matrixSize; ++j) {
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }
}
// 将二维矩阵原地逆时针旋转90度
void rotate2(int** matrix, int matrixSize, int* matrixColSize) {
  // 沿左下到右上的对角线镜像对称二维矩阵
  for (int i = 0; i < matrixSize; i++) {
    for (int j = 0; j < matrixSize - i; j++) {
      // swap(matrix[i][j], matrix[n-j-1][n-i-1])
      int temp = matrix[i][j];
      matrix[i][j] = matrix[matrixSize - j - 1][matrixSize - i - 1];
      matrix[matrixSize - j - 1][matrixSize - i - 1] = temp;
    }
  }
  // 然后反转二维矩阵的每一行
  for (int i = 0; i < matrixSize; ++i) {
    int l = 0;
    int r = matrixSize - 1;
    while (l < r) {
      int tmp = matrix[i][l];
      matrix[i][l] = matrix[i][r];
      matrix[i][r] = tmp;
      ++l;
      --r;
    }
  }
}
void rotate(int** matrix, int matrixSize, int* matrixColSize) {
  // print(matrix, matrixSize);
  // 先沿对角线镜像对称二维矩阵
  for (int i = 0; i < matrixSize; ++i) {
    for (int j = i; j < matrixSize; ++j) {
      int tmp = matrix[i][j];
      matrix[i][j] = matrix[j][i];
      matrix[j][i] = tmp;
    }
  }
  // print(matrix, matrixSize);
  // 然后反转二维矩阵的每一行
  for (int i = 0; i < matrixSize; ++i) {
    int l = 0;
    int r = matrixSize - 1;
    while (l < r) {
      int tmp = matrix[i][l];
      matrix[i][l] = matrix[i][r];
      matrix[i][r] = tmp;
      ++l;
      --r;
    }
  }
  // print(matrix, matrixSize);
}