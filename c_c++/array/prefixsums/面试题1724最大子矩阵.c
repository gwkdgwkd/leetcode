/*
给定一个正整数、负整数和0组成的N×M矩阵，编写代码找出元素总和最大的子矩阵。
返回一个数组[r1, c1, r2, c2]，
其中r1, c1分别代表子矩阵左上角的行号和列号，r2,c2分别代表右下角的行号和列号。
若有多个满足条件的子矩阵，返回任意一个均可。
注意：本题相对书上原题稍作改动

示例：
输入：
[
   [-1,0],
   [0,-1]
]
输出：[0,1,0,1]
解释：输入中标粗的元素即为输出所表示的矩阵

说明：1 <= matrix.length, matrix[0].length <= 200
*/

// i,j双指针遍历所有可能的的两个行对，即子矩阵的上下两条边，这决定了矩阵的高
// 将i-j之间的每一列（求出每一列的累计的和）看成一维数组中的一项，
// 在其中求最大子数组，即求出符合的子矩阵的宽
int* getMaxMatrix(int** matrix, int matrixSize, int* matrixColSize,
                  int* returnSize) {
  int m = matrixSize;
  int n = *matrixColSize;
  int preSum[m + 1][n];
  int max = matrix[0][0];
  int* res = (int*)calloc(4, sizeof(int));
  for (int i = 1; i < m + 1; i++) {
    for (int j = 0; j < n; j++) {
      preSum[i][j] = preSum[i - 1][j] + matrix[i - 1][j];
    }
  }

  for (int top = 0; top < m; top++) {
    for (int bottom = top; bottom < m; bottom++) {
      // 找到连续子数组的最大值
      int ints[n];
      for (int i = 0; i < n; i++) {
        ints[i] = preSum[bottom + 1][i] - preSum[top][i];
      }
      int start = 0;
      int sum = ints[0];
      for (int i = 1; i < n; i++) {
        if (sum > 0)
          sum += ints[i];
        else {
          sum = ints[i];
          start = i;
        }
        if (sum > max) {
          max = sum;
          res[0] = top;
          res[1] = start;
          res[2] = bottom;
          res[3] = i;
        }
      }
    }
  }
  *returnSize = 4;
  return res;
}