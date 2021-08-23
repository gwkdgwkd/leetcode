/*
 * @lc app=leetcode.cn id=221 lang=c
 *
 * [221] 最大正方形
 */

// @lc code=start

int maximalSquare(char** matrix, int matrixSize, int* matrixColSize) {
  int max = 0;
  if (matrixSize == 0 || matrixColSize[0] == 0 || matrix == NULL) {
    return max;
  }
  int m = matrixSize;
  int n = matrixColSize[0];

  int dp[m][n];
  memset(dp, 0, sizeof(dp));
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (matrix[i][j] == '1') {
        if (j == 0 || i == 0) {
          dp[i][j] = 1;
        } else {
          dp[i][j] =
              fmin(dp[i - 1][j], fmin(dp[i - 1][j - 1], dp[i][j - 1])) + 1;
        }
        max = fmax(max, dp[i][j]);
      }
    }
  }

  return max * max;
}

// @lc code=end
