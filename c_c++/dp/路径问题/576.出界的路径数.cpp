/*
给你一个大小为mxn的网格和一个球。
球的起始坐标为[startRow,startColumn]。
你可以将球移到在四个方向上相邻的单元格内，可以穿过网格边界到达网格之外。
你最多可以移动maxMove次球。
给你五个整数m、n、maxMove、startRow以及startColumn，
找出并返回可以将球移出边界的路径数量。
因为答案可能非常大，返回对10^9+7取余后的结果。

示例1：
输入：m = 2, n = 2, maxMove = 2, startRow = 0, startColumn = 0
输出：6

示例2：
输入：m = 1, n = 3, maxMove = 3, startRow = 0, startColumn = 1
输出：12

提示：
1 <= m, n <= 50
0 <= maxMove <= 50
0 <= startRow < m
0 <= startColumn < n
*/

// 官方题解，动态规划
int MOD = 1000000007;
int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
  int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
  int outCounts = 0;

  int dp[maxMove + 1][m][n];
  memset(dp, 0, sizeof(dp));
  dp[0][startRow][startColumn] = 1;
  for (int i = 0; i < maxMove; i++) {
    for (int j = 0; j < m; j++) {
      for (int k = 0; k < n; k++) {
        int count = dp[i][j][k];
        if (count > 0) {
          for (int s = 0; s < 4; s++) {
            int j1 = j + directions[s][0], k1 = k + directions[s][1];
            if (j1 >= 0 && j1 < m && k1 >= 0 && k1 < n) {
              dp[i + 1][j1][k1] = (dp[i + 1][j1][k1] + count) % MOD;
            } else {
              outCounts = (outCounts + count) % MOD;
            }
          }
        }
      }
    }
  }
  return outCounts;
}

class Solution {
 public:
  int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
    int MOD = 1000000007;
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int outCounts = 0;

    vector<vector<vector<int>>> dp(maxMove + 1,
                                   vector<vector<int>>(m, vector<int>(n, 0)));
    dp[0][startRow][startColumn] = 1;

    for (int i = 0; i < maxMove; i++) {
      for (int j = 0; j < m; j++) {
        for (int k = 0; k < n; k++) {
          int count = dp[i][j][k];
          if (count > 0) {
            for (int s = 0; s < 4; s++) {
              int j1 = j + directions[s][0], k1 = k + directions[s][1];
              if (j1 >= 0 && j1 < m && k1 >= 0 && k1 < n) {
                dp[i + 1][j1][k1] = (dp[i + 1][j1][k1] + count) % MOD;
              } else {
                outCounts = (outCounts + count) % MOD;
              }
            }
          }
        }
      }
    }
    return outCounts;
  }
};
