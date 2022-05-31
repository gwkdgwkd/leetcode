/*
一个机器人位于一个m x n网格的左上角。
机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角。
现在考虑网格中有障碍物。那么从左上角到右下角将会有多少条不同的路径？
网格中的障碍物和空位置分别用1和0来表示。

示例1：
输入：obstacleGrid = [[0,0,0],[0,1,0],[0,0,0]]
输出：2
解释：3x3网格的正中间有一个障碍物。
从左上角到右下角一共有2条不同的路径：
1.向右 -> 向右 -> 向下 -> 向下
2.向下 -> 向下 -> 向右 -> 向右

示例2：
输入：obstacleGrid = [[0,1],[0,0]]
输出：1

提示：
m == obstacleGrid.length
n == obstacleGrid[i].length
1 <= m, n <= 100
obstacleGrid[i][j]为0或1
*/

// 动态规划
int uniquePathsWithObstacles(int** obstacleGrid, int obstacleGridSize,
                             int* obstacleGridColSize) {
  if (obstacleGrid[0][0]) {
    return 0;
  }
  int m = obstacleGridSize;
  int n = *obstacleGridColSize;
  int dp[m][n];
  memset(dp, 0, sizeof(dp));
  for (int i = 0; i < m; ++i) {
    if (obstacleGrid[i][0] == 1) {
      break;
    }
    dp[i][0] = 1;
  }
  for (int i = 1; i < n; ++i) {
    if (obstacleGrid[0][i] == 1) {
      break;
    }
    dp[0][i] = 1;
  }

  for (int i = 1; i < m; ++i) {
    for (int j = 1; j < n; ++j) {
      if (obstacleGrid[i][j] == 1) {
        dp[i][j] = 0;
      } else {
        dp[i][j] = dp[i][j - 1] + dp[i - 1][j];
      }
    }
  }

  return dp[m - 1][n - 1];
}

int uniquePathsWithObstacles(int** obstacleGrid, int obstacleGridSize,
                             int* obstacleGridColSize) {
  int m = obstacleGridSize;
  int n = obstacleGridColSize[0];
  int dp[m][n];
  memset(dp, 0, sizeof(dp));
  for (int i = 0; i < m && obstacleGrid[i][0] == 0; i++) dp[i][0] = 1;
  for (int j = 0; j < n && obstacleGrid[0][j] == 0; j++) dp[0][j] = 1;
  for (int i = 1; i < m; i++) {
    for (int j = 1; j < n; j++) {
      if (obstacleGrid[i][j] == 1) continue;
      dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
    }
  }
  return dp[m - 1][n - 1];
}

// 官方题解
int uniquePathsWithObstacles(int** obstacleGrid, int obstacleGridSize,
                             int* obstacleGridColSize) {
  int n = obstacleGridSize, m = obstacleGridColSize[0];
  int f[m];
  memset(f, 0, sizeof(f));
  f[0] = (obstacleGrid[0][0] == 0);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (obstacleGrid[i][j] == 1) {
        f[j] = 0;
        continue;
      }
      if (j - 1 >= 0 && obstacleGrid[i][j - 1] == 0) {
        f[j] += f[j - 1];
      }
    }
  }

  return f[m - 1];
}

class Solution {
 public:
  int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    if (obstacleGrid[0][0]) {
      return 0;
    }
    int m = obstacleGrid.size();
    int n = obstacleGrid[0].size();
    vector<vector<int>> dp(m, vector<int>(n, 0));
    for (int i = 0; i < m; ++i) {
      if (obstacleGrid[i][0] == 1) break;
      dp[i][0] = 1;
    }
    for (int j = 1; j < n; ++j) {
      if (obstacleGrid[0][j] == 1) break;
      dp[0][j] = 1;
    }

    for (int i = 1; i < m; ++i) {
      for (int j = 1; j < n; ++j) {
        if (obstacleGrid[i][j] == 1) {
          dp[i][j] = 0;
        } else {
          dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
      }
    }

    return dp[m - 1][n - 1];
  }
};
