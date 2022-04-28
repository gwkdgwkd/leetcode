/*
给定一个仅包含0和1 、大小为rows x
cols的二维二进制矩阵，找出只包含1的最大矩形，并返回其面积。

示例1：
输入：matrix = [["1","0","1","0","0"],
               ["1","0","1","1","1"],
               ["1","1","1","1","1"],
               ["1","0","0","1","0"]]
输出：6

示例2：
输入：matrix = []
输出：0

示例3：
输入：matrix = [["0"]]
输出：0

示例4：
输入：matrix = [["1"]]
输出：1

示例5：
输入：matrix = [["0","0"]]
输出：0

提示：
rows == matrix.length
cols == matrix[0].length
1 <= row, cols <= 200
matrix[i][j]为'0'或'1'
*/

int maximalRectangle(char** matrix, int matrixSize, int* matrixColSize) {
  int m = matrixSize;
  if (m == 0) return 0;
  int n = matrixColSize[0];
  int dp[m][n];  // dp[i][j]表示元素向上连续1的个数
  memset(dp, 0, sizeof(dp));
  for (int j = 0; j < n; j++) {
    if (matrix[0][j] == '1') dp[0][j] = 1;
  }
  for (int i = 1; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (matrix[i][j] == '1') dp[i][j] = dp[i - 1][j] + 1;
    }
  }

  int ans = 0;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      // 当前高度乘以最大宽度都没有已知值大，那么跳过
      if (dp[i][j] * n <= ans) continue;
      if (dp[i][j] != 0) {
        int cnt = 1;
        // 找到右边连续比当前元素高的所有元素
        for (int k = j + 1; k < n; k++) {
          if (dp[i][k] < dp[i][j]) break;
          cnt++;
        }
        // 找到左边连续比当前元素高的所有元素
        for (int k = j - 1; k >= 0; k--) {
          if (dp[i][k] < dp[i][j]) break;
          cnt++;
        }
        ans = fmax(ans, cnt * dp[i][j]);
      }
    }
  }

  return ans;
}

// 剑指OfferII040矩阵中最大的矩形
int largestRectangleArea(int* heights, int heightsSize) {  // 84题解法
  int stack[heightsSize + 2];                              // 单调栈
  int top = 0;

  int data[heightsSize + 2];
  data[0] = data[heightsSize + 1] = 0;
  for (int i = 1; i <= heightsSize; ++i) {
    data[i] = heights[i - 1];
  }

  stack[top] = 0;
  int ret = 0;
  for (int i = 1; i < heightsSize + 2; ++i) {
    while (top > 0 && data[i] <= data[stack[top]]) {
      ret = fmax(ret, data[stack[top]] * (i - stack[top - 1] - 1));
      top--;
    }
    stack[++top] = i;
  }

  return ret;
}
int maximalRectangle(char** matrix, int matrixSize) {
  if (matrixSize == 0) return 0;

  int m = matrixSize;
  int n = strlen(matrix[0]);

  int dp[m][n];
  memset(dp, 0, sizeof(dp));

  for (int j = 0; j < n; j++) {
    if (matrix[0][j] == '1') dp[0][j] = 1;
  }
  for (int i = 1; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (matrix[i][j] == '1') dp[i][j] = dp[i - 1][j] + 1;
    }
  }

  int res = 0;
  for (int i = 0; i < m; ++i) {
    res = fmax(res, largestRectangleArea(dp[i], n));
  }

  return res;
}