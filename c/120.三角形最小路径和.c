/*
 * @lc app=leetcode.cn id=120 lang=c
 *
 * [120] 三角形最小路径和
 */

// @lc code=start

// 动态规划
int minimumTotal(int** triangle, int triangleSize, int* triangleColSize) {
  if (triangleSize == 0) {
    return 0;
  }
  if (triangleSize == 1) {
    return triangle[0][0];
  }

  int m = triangleSize;
  int n = triangleColSize[triangleSize - 1];
  int dp[m][n];
  memset(dp, 0, sizeof(dp));
  dp[0][0] = triangle[0][0];
  for (int i = 1; i < m; ++i) {
    for (int j = 0; j < triangleColSize[i]; ++j) {
      if (j == 0) {
        dp[i][j] = dp[i - 1][j] + triangle[i][j];
      } else if (j == triangleColSize[i] - 1) {
        dp[i][j] = dp[i - 1][j - 1] + triangle[i][j];
      } else {
        dp[i][j] = fmin(dp[i - 1][j], dp[i - 1][j - 1]) + triangle[i][j];
      }
    }
  }

  int ret = dp[m - 1][0];
  for (int i = 1; i < n; ++i) {
    ret = fmin(ret, dp[m - 1][i]);
  }

  return ret;
}

/*
// 官方题解
int minimumTotal(int** triangle, int triangleSize, int* triangleColSize) {
  int f[2][triangleSize];
  memset(f, 0, sizeof(f));
  f[0][0] = triangle[0][0];
  for (int i = 1; i < triangleSize; ++i) {
    int curr = i % 2;
    int prev = 1 - curr;
    f[curr][0] = f[prev][0] + triangle[i][0];
    for (int j = 1; j < i; ++j) {
      f[curr][j] = fmin(f[prev][j - 1], f[prev][j]) + triangle[i][j];
    }
    f[curr][i] = f[prev][i - 1] + triangle[i][i];
  }
  int ret = f[(triangleSize - 1) % 2][0];
  for (int i = 1; i < triangleSize; i++)
    ret = fmin(ret, f[(triangleSize - 1) % 2][i]);
  return ret;
}
*/

// @lc code=end
