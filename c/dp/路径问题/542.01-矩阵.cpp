/*
给定一个由0和1组成的矩阵mat，请输出一个大小相同的矩阵，
其中每一个格子是mat中对应位置元素到最近的0的距离。
两个相邻元素间的距离为1。

示例1：
输入：mat = [[0,0,0],[0,1,0],[0,0,0]]
输出：[[0,0,0],[0,1,0],[0,0,0]]

示例2：
输入：mat = [[0,0,0],[0,1,0],[1,1,1]]
输出：[[0,0,0],[0,1,0],[1,2,1]]

提示：
m == mat.length
n == mat[i].length
1 <= m, n <= 10^4
1 <= m * n <= 10^4
mat[i][j] is either 0 or 1.
mat中至少有一个0
*/

// 剑指OfferII107矩阵中的距离

// 动态规划
int** updateMatrix(int** mat, int matSize, int* matColSize, int* returnSize,
                   int** returnColumnSizes) {
  int m = returnSize[0] = matSize;
  int n = matColSize[0];

  // 初始化动态规划的数组，所有的距离值都设置为一个很大的数
  unsigned int** dp = calloc(sizeof(unsigned int*), matSize);
  *returnColumnSizes = calloc(sizeof(int), matSize);
  for (int i = 0; i < matSize; i++) {
    dp[i] = calloc(sizeof(int), (*matColSize));
    returnColumnSizes[0][i] = *matColSize;
  }

  // 如果(i,j)的元素为0，那么距离为0
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (mat[i][j] == 0) {
        dp[i][j] = 0;
      } else {
        dp[i][j] = INT_MAX;
      }
    }
  }

  // 只有水平向左移动和竖直向上移动，注意动态规划的计算顺序
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i - 1 >= 0) {
        dp[i][j] = fmin(dp[i][j], dp[i - 1][j] + 1);
      }
      if (j - 1 >= 0) {
        dp[i][j] = fmin(dp[i][j], dp[i][j - 1] + 1);
      }
    }
  }
  // 只有水平向右移动和竖直向下移动，注意动态规划的计算顺序
  for (int i = m - 1; i >= 0; --i) {
    for (int j = n - 1; j >= 0; --j) {
      if (i + 1 < m) {
        dp[i][j] = fmin(dp[i][j], dp[i + 1][j] + 1);
      }
      if (j + 1 < n) {
        dp[i][j] = fmin(dp[i][j], dp[i][j + 1] + 1);
      }
    }
  }

  return dp;
}

class Solution {
 public:
  vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
    int m = mat.size();
    int n = mat[0].size();
    vector<vector<int>> dp(m, vector<int>(n, INT_MAX / 2));

    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (mat[i][j] == 0) {
          dp[i][j] = 0;
        }
      }
    }

    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (i - 1 >= 0) {
          dp[i][j] = min(dp[i][j], dp[i - 1][j] + 1);
        }
        if (j - 1 >= 0) {
          dp[i][j] = min(dp[i][j], dp[i][j - 1] + 1);
        }
      }
    }

    for (int i = m - 1; i >= 0; --i) {
      for (int j = n - 1; j >= 0; --j) {
        if (i + 1 < m) {
          dp[i][j] = min(dp[i][j], dp[i + 1][j] + 1);
        }
        if (j + 1 < n) {
          dp[i][j] = min(dp[i][j], dp[i][j + 1] + 1);
        }
      }
    }

    return dp;
  }
};
