/*
给定一个三角形triangle，找出自顶向下的最小路径和。
每一步只能移动到下一行中相邻的结点上。
相邻的结点在这里指的是下标与上一层结点下标相同或者等于上一层结点下标+1的两个结点。
也就是说，如果正位于当前行的下标i，那么下一步可以移动到下一行的下标i或i+1。

示例1：
输入：triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
输出：11
解释：
   2
  3 4
 6 5 7
4 1 8 3
自顶向下的最小路径和为11（即2 + 3 + 5 + 1 = 11）。

示例2：
输入：triangle = [[-10]]
输出：-10

提示：
1 <= triangle.length <= 200
triangle[0].length == 1
triangle[i].length == triangle[i - 1].length + 1
-10^4 <= triangle[i][j] <= 10^4

进阶：你可以只使用O(n)的额外空间（n为三角形的总行数）来解决这个问题吗？
*/

// 剑指OfferII100三角形中最小路径之和

// 动态规划
int minimumTotal(int** triangle, int triangleSize, int* triangleColSize) {
  int m = triangleSize;
  int n = triangleColSize[triangleSize - 1];
  int dp[m][n];
  dp[0][0] = triangle[0][0];
  for (int i = 1; i < m; ++i) {
    for (int j = 0; j < triangleColSize[i]; ++j) {
      if (j == 0) {  // 最左边的元素
        dp[i][j] = dp[i - 1][j] + triangle[i][j];
      } else if (j == triangleColSize[i] - 1) {  // 最右边的元素
        dp[i][j] = dp[i - 1][j - 1] + triangle[i][j];
      } else {  // 中间的元素
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

// 压缩数组
int minimumTotal(int** triangle, int triangleSize, int* triangleColSize) {
  int dp[triangleColSize[triangleSize - 1]];
  dp[0] = triangle[0][0];
  for (int i = 1; i < triangleSize; ++i) {
    for (int j = triangleColSize[i] - 1; j >= 0; --j) {
      if (j == 0) {
        dp[j] = dp[j] + triangle[i][j];
      } else if (j == triangleColSize[i] - 1) {
        dp[j] = dp[j - 1] + triangle[i][j];
      } else {
        dp[j] = fmin(dp[j], dp[j - 1]) + triangle[i][j];
      }
    }
  }

  int ret = dp[0];
  for (int i = 1; i < triangleColSize[triangleSize - 1]; ++i) {
    ret = fmin(ret, dp[i]);
  }

  return ret;
}

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

class Solution {
 public:
  int minimumTotal(vector<vector<int>>& triangle) {
    vector<vector<int>> dp = triangle;
    int m = triangle.size();

    for (int i = 1; i < m; ++i) {
      int n = triangle[i].size();
      dp[i].assign(n, 0);
      for (int j = 0; j < n; ++j) {
        if (j == 0) {
          dp[i][j] = dp[i - 1][j] + triangle[i][j];
        } else if (j == n - 1) {
          dp[i][j] = dp[i - 1][j - 1] + triangle[i][j];
        } else {
          dp[i][j] = min(dp[i - 1][j], dp[i - 1][j - 1]) + triangle[i][j];
        }
      }
    }

    int ans = dp[m - 1][0];
    for (int j = 1; j < triangle[m - 1].size(); ++j) {
      ans = min(ans, dp[m - 1][j]);
    }

    return ans;
  }
};
