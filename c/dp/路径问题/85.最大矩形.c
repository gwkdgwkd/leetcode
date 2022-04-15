/*
给定一个仅包含0和1 、大小为rows x cols的二维二进制矩阵，找出只包含1的最大矩形，并返回其面积。

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
        for (int k = j + 1; k < n; k++) {  // 找到右边比当前元素高的所有元素
          if (dp[i][k] < dp[i][j]) break;
          cnt++;
        }
        for (int k = j - 1; k >= 0; k--) {  // 找到左边比当前元素高的所有元素
          if (dp[i][k] < dp[i][j]) break;
          cnt++;
        }
        ans = fmax(ans, cnt * dp[i][j]);
      }
    }
  }

  return ans;
}