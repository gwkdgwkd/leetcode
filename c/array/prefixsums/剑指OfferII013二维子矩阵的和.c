/*
给定一个二维矩阵matrix，以下类型的多个请求：
计算其子矩形范围内元素的总和，该子矩阵的左上角为(row1,col1)，右下角为(row2,col2)。
实现NumMatrix类：
NumMatrix(int[][] matrix) 给定整数矩阵 matrix 进行初始化
int sumRegion(int row1, int col1, int row2, int col2) 
返回左上角(row1, col1) 、右下角(row2, col2)的子矩阵的元素总和。

示例1：
输入: 
["NumMatrix","sumRegion","sumRegion","sumRegion"]
[[[[3,0,1,4,2],[5,6,3,2,1],[1,2,0,1,5],[4,1,0,1,7],
[1,0,3,0,5]]],[2,1,4,3],[1,1,2,2],[1,2,2,4]]
输出: 
[null, 8, 11, 12]

解释:
NumMatrix numMatrix = new NumMatrix([[3,0,1,4,2],
[5,6,3,2,1],[1,2,0,1,5],[4,1,0,1,7],[1,0,3,0,5]]]);
numMatrix.sumRegion(2, 1, 4, 3); // return 8 (红色矩形框的元素总和)
numMatrix.sumRegion(1, 1, 2, 2); // return 11 (绿色矩形框的元素总和)
numMatrix.sumRegion(1, 2, 2, 4); // return 12 (蓝色矩形框的元素总和)

提示：
m == matrix.length
n == matrix[i].length
1 <= m, n <= 200
-10^5 <= matrix[i][j] <= 10^5
0 <= row1 <= row2 < m
0 <= col1 <= col2 < n
最多调用10^4次sumRegion方法

注意：本题与304题相同
*/

typedef struct {
  int** nums;
  int size;
} NumMatrix;
NumMatrix* numMatrixCreate(int** matrix, int matrixSize, int* matrixColSize) {
  NumMatrix* sums = (NumMatrix*)malloc(sizeof(NumMatrix));
  sums->nums = (int**)malloc(sizeof(int*) * matrixSize);
  for (int i = 0; i < matrixSize; ++i) {
    sums->nums[i] = (int*)malloc(sizeof(int) * (matrixColSize[0] + 1));
    sums->nums[i][0] = 0;
    for (int j = 0; j < matrixColSize[0]; ++j) {
      sums->nums[i][j + 1] = sums->nums[i][j] + matrix[i][j];
    }
  }
  sums->size = matrixSize;
  return sums;
}
int numMatrixSumRegion(NumMatrix* obj, int row1, int col1, int row2, int col2) {
  int sum = 0;
  for (int i = row1; i <= row2; ++i) {
    sum += obj->nums[i][col2 + 1] - obj->nums[i][col1];
  }
  return sum;
}
void numMatrixFree(NumMatrix* obj) {
  for (int i = 0; i < obj->size; i++) {
    free(obj->nums[i]);
  }
  free(obj->nums);
}