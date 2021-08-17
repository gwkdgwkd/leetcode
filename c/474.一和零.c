/*
 * @lc app=leetcode.cn id=474 lang=c
 *
 * [474] 一和零
 */

// @lc code=start

/*
// 动态规划
int findMaxForm(char** strs, int strsSize, int m, int n) {
  int dp[strsSize + 1][m + 1][n + 1];
  memset(dp, 0, sizeof(dp));

  for (int i = 1; i <= strsSize; ++i) {
    int c0 = 0;
    int c1 = 0;
    for (int s = 0; s < strlen(strs[i - 1]); ++s) {
      if (strs[i - 1][s] - '0') {
        ++c1;
      } else {
        ++c0;
      }
    }
    for (int j = 0; j <= m; ++j) {
      for (int k = 0; k <= n; ++k) {
        dp[i][j][k] = dp[i - 1][j][k];
        if (j >= c0 && k >= c1) {
          dp[i][j][k] = fmax(dp[i][j][k], dp[i - 1][j - c0][k - c1] + 1);
        }
      }
    }
  }

  return dp[strsSize][m][n];
}
*/

// 压缩dp
int findMaxForm(char** strs, int strsSize, int m, int n) {
  int dp[m + 1][n + 1];
  memset(dp, 0, sizeof(dp));

  for (int i = 1; i <= strsSize; ++i) {
    int c0 = 0;
    int c1 = 0;
    for (int s = 0; s < strlen(strs[i - 1]); ++s) {
      if (strs[i - 1][s] - '0') {
        ++c1;
      } else {
        ++c0;
      }
    }
    for (int j = m; j >= 0; --j) {
      for (int k = n; k >= 0; --k) {
        if (j >= c0 && k >= c1) {
          dp[j][k] = fmax(dp[j][k], dp[j - c0][k - c1] + 1);
        }
      }
    }
  }

  return dp[m][n];
}

// @lc code=end
