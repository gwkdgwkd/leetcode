/*
给定一个二维矩阵matrix，以下类型的多个请求：
计算其子矩形范围内元素的总和，该子矩阵的左上角为(row1,col1)，右下角为(row2,col2)。
实现NumMatrix类：
NumMatrix(int[][] matrix)给定整数矩阵matrix进行初始化
int sumRegion(int row1, int col1, int row2, int col2)
返回左上角(row1,col1)到右下角(row2,col2)所描述的子矩阵的元素总和。

示例1：
输入:
["NumMatrix","sumRegion","sumRegion","sumRegion"]
[
[[[3,0,1,4,2],
  [5,6,3,2,1],
  [1,2,0,1,5],
  [4,1,0,1,7],
  [1,0,3,0,5]]],
  [2,1,4,3],
  [1,1,2,2],
  [1,2,2,4]
]
输出:
[null, 8, 11, 12]
解释:
NumMatrix numMatrix = new NumMatrix([[3,0,1,4,2],
                                     [5,6,3,2,1],
                                     [1,2,0,1,5],
                                     [4,1,0,1,7],
                                     [1,0,3,0,5]]);
numMatrix.sumRegion(2, 1, 4, 3); // return 8
numMatrix.sumRegion(1, 1, 2, 2); // return 11
numMatrix.sumRegion(1, 2, 2, 4); // return 12

提示：
m == matrix.length
n == matrix[i].length
1 <= m, n <= 200
-10^5 <= matrix[i][j] <= 10^5
0 <= row1 <= row2 < m
0 <= col1 <= col2 < n
最多调用10^4次sumRegion方法
*/

// 剑指OfferII013二维子矩阵的和

#include <stdio.h>
#include <stdlib.h>

// 前缀和
typedef struct {
  int** sums;
  int sumsSize;
} NumMatrix;
// NumMatrix* numMatrixCreate(int** matrix, int matrixSize, int* matrixColSize)
// {
NumMatrix* numMatrixCreate(int (*matrix)[5], int matrixSize,
                           int* matrixColSize) {
  NumMatrix* ret = (NumMatrix*)malloc(sizeof(NumMatrix));
  ret->sums = (int**)malloc(sizeof(int*) * matrixSize);
  ret->sumsSize = matrixSize;
  for (int i = 0; i < matrixSize; i++) {
    ret->sums[i] = (int*)malloc(sizeof(int) * (matrixColSize[i] + 1));
    ret->sums[i][0] = 0;
    for (int j = 0; j < matrixColSize[i]; j++) {
      ret->sums[i][j + 1] = ret->sums[i][j] + matrix[i][j];
    }
  }
  return ret;
}
int numMatrixSumRegion(NumMatrix* obj, int row1, int col1, int row2, int col2) {
  int sum = 0;
  for (int i = row1; i <= row2; i++) {
    sum += obj->sums[i][col2 + 1] - obj->sums[i][col1];
  }
  return sum;
}
void numMatrixFree(NumMatrix* obj) {
  for (int i = 0; i < obj->sumsSize; i++) {
    free(obj->sums[i]);
  }
  free(obj->sums);
}

#include <vector>
using namespace std;
class NumMatrix1 {
  vector<vector<int>> pre;

 public:
  NumMatrix1(vector<vector<int>>& matrix) {
    int m = matrix.size();
    int n = matrix[0].size();

    pre.assign(m, vector<int>(n + 1, 0));
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        pre[i][j + 1] = pre[i][j] + matrix[i][j];
      }
    }
  }
  int sumRegion(int row1, int col1, int row2, int col2) {
    int res = 0;
    for (int i = row1; i <= row2; ++i) {
      res += (pre[i][col2 + 1] - pre[i][col1]);
    }

    return res;
  }
};

int main() {
  int a[5][5] = {{3, 0, 1, 4, 2},
                 {5, 6, 3, 2, 1},
                 {1, 2, 0, 1, 5},
                 {4, 1, 0, 1, 7},
                 {1, 0, 3, 0, 5}};
  int* p = (int*)malloc(5 * sizeof(int));
  for (int i = 0; i < 5; ++i) {
    p[i] = 5;
  }
  NumMatrix* nm = numMatrixCreate(a, 5, p);
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 6; ++j) {
      printf("%2d ", nm->sums[i][j]);
    }
    printf("\n");
  }
  //  0  3  3  4  8 10
  //  0  5 11 14 16 17
  //  0  1  3  3  4  9
  //  0  4  5  5  6 13
  //  0  1  1  4  4  9

  printf("%d\n", numMatrixSumRegion(nm, 2, 1, 4, 3));  // 8
  printf("%d\n", numMatrixSumRegion(nm, 1, 1, 2, 2));  // 11
  printf("%d\n", numMatrixSumRegion(nm, 1, 2, 2, 4));  // 12
  numMatrixFree(nm);

  return 0;
}