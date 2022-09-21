/*
给你一个nxn的方形整数数组matrix，
请你找出并返回通过matrix的下降路径的最小和。
下降路径可以从第一行中的任何元素开始，并从每一行中选择一个元素。
在下一行选择的元素和当前行所选元素最多相隔一列，
即位于正下方或者沿对角线向左或者向右的第一个元素。
具体来说，位置(row,col)的下一个元素应当是(row+1,col-1)、
(row+1,col)或者(row+1,col+1)。

示例1：
输入：matrix = [[2,1,3],[6,5,4],[7,8,9]]
输出：13

示例2：
输入：matrix = [[-19,57],[-40,-5]]
输出：-59

提示：
n == matrix.length == matrix[i].length
1 <= n <= 100
-100 <= matrix[i][j] <= 100
*/

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

class Solution {
 public:
  int minFallingPathSum(vector<vector<int>>& matrix) {
    int m = matrix.size();
    int n = matrix[0].size();

    vector<vector<int>> dp(m, vector<int>(n, 0));
    dp[0] = matrix[0];
    for (int i = 1; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        dp[i][j] = dp[i - 1][j];
        if (j > 0) {
          dp[i][j] = min(dp[i][j], dp[i - 1][j - 1]);
        }
        if (j < n - 1) {
          dp[i][j] = min(dp[i][j], dp[i - 1][j + 1]);
        }

        dp[i][j] += matrix[i][j];
      }
    }

    int ans = dp[m - 1][0];
    for (int j = 1; j < n; ++j) {
      ans = min(ans, dp[m - 1][j]);
    }
    return ans;
  }
};

class Solution {
 public:
  int minFallingPathSum(vector<vector<int>>& matrix) {
    int m = matrix.size();
    int n = matrix[0].size();

    // 滚动数组：
    vector<vector<int>> dp(2, vector<int>(n));
    dp[0] = matrix[0];
    for (int i = 1; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        int k1 = (i + 1) % 2;
        int k2 = i % 2;
        dp[k2][j] = dp[k1][j];
        if (j > 0) {
          dp[k2][j] = min(dp[k2][j], dp[k1][j - 1]);
        }
        if (j < n - 1) {
          dp[k2][j] = min(dp[k2][j], dp[k1][j + 1]);
        }
        dp[k2][j] += matrix[i][j];
      }
    }

    int k = (m - 1) % 2;
    int ans = dp[k][0];
    for (int j = 1; j < n; ++j) {
      ans = min(ans, dp[k][j]);
    }

    return ans;
  }
};
