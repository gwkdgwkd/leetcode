/*
 * @lc app=leetcode.cn id=542 lang=c
 *
 * [542] 01 矩阵
 */

// @lc code=start

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
// 动态规划，运行出错
int** updateMatrix(int** mat, int matSize, int* matColSize, int* returnSize,
                   int** returnColumnSizes) {
  int m = returnSize[0] = matSize;
  int n = matColSize[0];
  // 初始化动态规划的数组，所有的距离值都设置为一个很大的数
  int** dp = calloc(sizeof(int*), matSize);
  *returnColumnSizes = calloc(sizeof(int), matSize);
  for (int i = 0; i < matSize; i++) {
    dp[i] = calloc(sizeof(int), (*matColSize));
    returnColumnSizes[0][i] = *matColSize;
  }

  // 如果 (i, j) 的元素为 0，那么距离为 0
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      dp[i][j] = INT_MAX;
      if (mat[i][j] == 0) {
        dp[i][j] = 0;
      }
    }
  }

  // 只有 水平向左移动 和 竖直向上移动，注意动态规划的计算顺序
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
  // 只有 水平向右移动 和 竖直向下移动，注意动态规划的计算顺序
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

// @lc code=end
