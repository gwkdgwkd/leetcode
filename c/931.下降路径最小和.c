/*
 * @lc app=leetcode.cn id=931 lang=c
 *
 * [931] 下降路径最小和
 */

// @lc code=start

#define MIN(a, b) ((a) < (b) ? (a) : (b))
int minFallingPathSum(int** matrix, int matrixSize, int* matrixColSize) {
  int dp[matrixSize][matrixSize];

  for (int i = 0; i < matrixSize; ++i) {
    dp[0][i] = matrix[0][i];
  }
  for (int i = 1; i < matrixSize; ++i) {
    for (int j = 0; j < matrixSize; ++j) {
      if (0 == j) {
        dp[i][j] = matrix[i][j] + MIN(dp[i - 1][j], dp[i - 1][j + 1]);
      } else if (matrixSize - 1 == j) {
        dp[i][j] = matrix[i][j] + MIN(dp[i - 1][j - 1], dp[i - 1][j]);
      } else {
        dp[i][j] = matrix[i][j] +
                   MIN(MIN(dp[i - 1][j - 1], dp[i - 1][j]), dp[i - 1][j + 1]);
      }
    }
  }

  int ret = dp[matrixSize - 1][0];
  for (int i = 1; i < matrixSize; ++i) {
    ret = MIN(ret, dp[matrixSize - 1][i]);
  }

  return ret;
}

/*
// 压缩dp，但效果不明显，可以压缩成一维数组么？
#define MIN(a, b) ((a) < (b) ? (a) : (b))
int minFallingPathSum(int** matrix, int matrixSize, int* matrixColSize) {
  int dp[2][matrixSize];
  int index = 0;

  for (int i = 0; i < matrixSize; ++i) {
    dp[0][i] = matrix[0][i];
  }
  for (int i = 1; i < matrixSize; ++i) {
    index = (index + 1) % 2;
    for (int j = 0; j < matrixSize; ++j) {
      if (0 == j) {
        dp[index][j] = matrix[i][j] +
                       MIN(dp[(index + 1) % 2][j], dp[(index + 1) % 2][j + 1]);
      } else if (matrixSize - 1 == j) {
        dp[index][j] = matrix[i][j] +
                       MIN(dp[(index + 1) % 2][j - 1], dp[(index + 1) % 2][j]);
      } else {
        dp[index][j] = matrix[i][j] + MIN(MIN(dp[(index + 1) % 2][j - 1],
                                              dp[(index + 1) % 2][j]),
                                          dp[(index + 1) % 2][j + 1]);
      }
    }
  }

  int ret = dp[index][0];
  for (int i = 1; i < matrixSize; ++i) {
    ret = MIN(ret, dp[index][i]);
  }

  return ret;
}
*/

// @lc code=end
