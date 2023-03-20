/*
在一个由'0'和'1'组成的二维矩阵内，找到只包含'1'的最大正方形，并返回其面积。

示例1：
输入：matrix = [["1","0","1","0","0"],
               ["1","0","1","1","1"],
               ["1","1","1","1","1"],
               ["1","0","0","1","0"]]
输出：4

示例2：
输入：matrix = [["0","1"],["1","0"]]
输出：1

示例3：
输入：matrix = [["0"]]
输出：0

提示：
m == matrix.length
n == matrix[i].length
1 <= m, n <= 300
matrix[i][j]为'0'或'1'
*/

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
        if (j == 0 || i == 0) {  // 特殊处理
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

int maximalSquare(char** matrix, int matrixSize, int* matrixColSize) {
  int m = matrixSize;
  int n = *matrixColSize;

  // dp具体定义：
  // dp[i+1][j+1]表示以第i行、第j列为右下角的正方形的最大边长
  // 为何不是dp[i][j]
  // 任何一个正方形，都依赖当前格左、上、左上三个方格的情况；
  // 但第一行的上层已经没有格子，第一列左边已经没有格子，需要做特殊if判断来处理；
  // 为了代码简洁，假设补充了多一行全'0'、多一列全'0'；
  int dp[m + 1][n + 1];
  memset(dp, 0, sizeof(dp));
  int max = 0;
  for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (matrix[i - 1][j - 1] == '1') {
        // 若某格子值为1，则以此为右下角的正方形的最大边长为：
        // 上面的正方形、左面的正方形或左上的正方形中，最小的那个，再加上此格。
        // 0 0 0 0 0 0
        // 0 0 1 1 1 0
        // 1 1 1 1 1 0
        // 1 1 1 1 1 0
        // 1 1 1 1 1 0
        // 0 0 0 0 0 0
        dp[i][j] = fmin(dp[i - 1][j], fmin(dp[i - 1][j - 1], dp[i][j - 1])) + 1;
        max = fmax(max, dp[i][j]);
      }
    }
  }

  return max * max;
}

class Solution {
 public:
  int maximalSquare(vector<vector<char>>& matrix) {
    int m = matrix.size();
    int n = matrix[0].size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    int max = 0;
    for (int i = 1; i <= m; ++i) {
      for (int j = 1; j <= n; ++j) {
        if (matrix[i - 1][j - 1] == '1') {
          dp[i][j] = min(dp[i][j - 1], min(dp[i - 1][j], dp[i - 1][j - 1])) + 1;
          max = std::max(max, dp[i][j]);
        }
      }
    }

    return max * max;
  }
};