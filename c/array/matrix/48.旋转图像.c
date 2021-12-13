void print(int** matrix, int matrixSize) {
  for (int i = 0; i < matrixSize; ++i) {
    for (int j = 0; j < matrixSize; ++j) {
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }
  printf("====================\n");
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